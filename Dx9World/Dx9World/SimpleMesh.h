#ifndef __SIMPLEMESH_H__
#define __SIMPLEMESH_H__

#include "MeshFileIO.h"
class SimpleMesh
{
public:
	SimpleMesh( const std::string & meshName );
	~SimpleMesh();
public:
	
	bool loadFromFile( const std::string & fileName );
	bool unloadMesh();
	bool loadToGpu();
	bool unloadFromGpu();
public:
	const std::vector<VERTEX_FORMAT_TYPE> & getVertexType() { return m_fvfVec;}
	const std::string getMatName() { return m_matName;}
	INDEX_TYPE getIndexType() { return m_indexType; }
	int getIndexCount() { return m_reader.getIndexCount(); }
	int getVertexCount() { return m_reader.getVertexCount(); }
	char * getIndexData () { return m_indexData; }
	char * getVertexData() { return m_vertexData; }
private:
	std::string m_name;
	std::vector<VERTEX_FORMAT_TYPE> m_fvfVec;
	std::string m_matName;
	INDEX_TYPE m_indexType;
	char * m_vertexData; //记录顶点数据
	char * m_indexData; //记录索引数据
	MeshFileReader m_reader;
	
	int m_vertexDataSize; //顶点数据大小(字节)
	int m_indexDataSize;//索引数据大小(字节)
	bool m_isLoadedFromFile;
	bool m_isLoadedToGpu;
};

#endif //__SIMPLEMESH_H__
