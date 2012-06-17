#ifndef __MESHFILEIO_H__
#define __MESHFILEIO_H__

#include <fstream>

enum INDEX_TYPE { INDEX_16 , INDEX_32 };
enum VERTEX_FORMAT_TYPE { 
	VT_POS_XYZ ,
	VT_POS_XYZW,
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

//计算顶点格式的尺寸
int getVertexTypeSize( VERTEX_FORMAT_TYPE type );
int getD3dVertexType( std::vector<VERTEX_FORMAT_TYPE> & vec );

class MeshFileReader
{
public:
public:
	bool openMeshFile( const std::string & filename );
	bool closeMeshFile();

	std::string getMaterialName();
	INDEX_TYPE getIndexType();
	long getIndexCount();
	void getIndexData( void * data );
	std::vector<VERTEX_FORMAT_TYPE> getVertextType();
	long getVertexCount();
	void getVertexData( void * data );
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
	void setIndexData( void * data , long count );
	void setVertexType( const std::vector<VERTEX_FORMAT_TYPE> &vec );
	void setVertexData( void * data , long count );
private:
	std::ofstream m_stream;
	std::string m_matName;
	INDEX_TYPE m_indexType;
	void * m_indexData;
	void * m_vertexData;
	long m_indexCount;
	long m_vertexCount;
	std::vector<VERTEX_FORMAT_TYPE> m_vertexType;
};

#endif //__MESHFILEIO_H__
