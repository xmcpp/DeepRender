#ifndef __MESHFILEIO_H__
#define __MESHFILEIO_H__

#include <fstream>

enum INDEX_TYPE { INDEX_16 , INDEX_32 };
enum VERTEX_FORMAT_TYPE { 
	VT_POS ,
	VT_POS_RHW , 
	VT_NORMAL , 
	VT_DIFFUSE , 
	VT_SPECULAR,
	VT_UV0,
	VT_UV1,
	VT_UV2,
	VT_UV3,
	VT_UV4,
	VT_UV5,
	VT_UV6,
	VT_UV7,
	VT_UV8,
};

typedef struct tagMeshFileHead
{
	char head[11]; //"SimpleMesh"
	short version;
}MeshFileHead;

typedef struct tagMeshFileHeadInfo
{
	long matDataAddr;
	long matDataSize;

	char indexType;
	long indexCount;
	long indexDataAddr;
	long indexDataSize;
	
	short vertexTypeCount;
	long vertexTypeDataAddr;
	long vertexTypeDataSize;

	long vertexCount;
	long vertexDataAddr;
	long vertexDataSize;


}MeshFileHeadInfo;


class MeshFileReader
{
public:
public:
	bool openMeshFile( const std::string & filename );
	bool closeMeshFile();
private:
	std::ifstream m_stream;
	MeshFileHead m_fileHead;
	MeshFileHeadInfo m_fileHeadInfo;
};

class MeshFileWriter
{
public:
	bool saveToFile( const std::string & filename );

	void setMaterialName( const std::string & materialName );
	void setIndexType( INDEX_TYPE indexType );
	void setIndexData( int * data , long count );
	void setVertexType( const std::vector<VERTEX_FORMAT_TYPE> &vec );
	void setVertexData( float * data , long count );
private:
	int getVertexTypeSize( VERTEX_FORMAT_TYPE type );
private:
	std::ofstream m_stream;
	std::string m_matName;
	INDEX_TYPE m_indexType;
	int * m_indexData;
	float * m_vertexData;
	long m_indexCount;
	long m_vertexCount;
	std::vector<VERTEX_FORMAT_TYPE> m_vertexType;
};

#endif //__MESHFILEIO_H__
