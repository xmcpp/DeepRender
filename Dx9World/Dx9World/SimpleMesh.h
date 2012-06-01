#ifndef __SIMPLEMESH_H__
#define __SIMPLEMESH_H__

#include "MeshFileIO.h"
class SimpleMesh
{
public:
	

public:
	SimpleMesh();
	~SimpleMesh();
	bool loadFromFile( std::string & fileName );
	
private:
	std::vector<VERTEX_FORMAT_TYPE> m_fvfVec;
	std::string m_matName;
	INDEX_TYPE m_indexType;
	std::vector<short> m_index16Vec;
	std::vector<int> m_index32Vec;
	float * m_vertexData; //记录顶点数据
};

#endif //__SIMPLEMESH_H__
