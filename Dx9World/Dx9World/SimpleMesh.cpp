#include "stdafx.h"
#include "SimpleMesh.h"
#include "Core.h"
#include "D3D9RenderSystem.h"

SimpleMesh::SimpleMesh( const std::string & meshName )
:m_vertexData(NULL),m_indexData(NULL),m_isLoadedFromFile(false),m_isLoadedToGpu(false),m_name(meshName)
,m_vertexDataSize(0),m_indexDataSize(0)
{

}

SimpleMesh::~SimpleMesh()
{
	if( m_isLoadedFromFile )
	{
		unloadMesh();
	}
}

bool SimpleMesh::loadFromFile( const std::string & fileName )
{
	if( !m_reader.openMeshFile( fileName ) )
		return false;
	
	//如果已经加载,则卸载
	if( m_isLoadedFromFile )
		unloadMesh();

	m_indexType = m_reader.getIndexType();
	m_fvfVec = m_reader.getVertextType();
	m_matName = m_reader.getMaterialName();
	
	//加载顶点数据
	m_vertexDataSize = 0;
	for ( unsigned int i = 0 ; i < m_fvfVec.size() ; i++ )
	{
		m_vertexDataSize += getVertexTypeSize( m_fvfVec[i] );
	}
	m_vertexDataSize *= m_reader.getVertexCount();
	m_vertexData = new char[m_vertexDataSize];
	m_reader.getVertexData( m_vertexData );

	//加载索引数据
	m_indexDataSize = ((m_indexType == INDEX_16)?2:4)*m_reader.getIndexCount();
	m_indexData = new char[m_indexDataSize];
	m_reader.getIndexData( m_indexData );

	m_reader.closeMeshFile();

	m_isLoadedFromFile = true;
	return true;
}

bool SimpleMesh::unloadMesh()
{
	if ( !m_isLoadedFromFile )
		return true;

	if( m_isLoadedToGpu )
		unloadFromGpu();

	m_fvfVec.clear();
	m_matName = "";
	m_indexType = INDEX_16;
	m_indexDataSize = 0;
	m_vertexDataSize = 0;
	delete []m_vertexData;
	delete []m_indexData;

	m_vertexData = NULL;
	m_indexData = NULL;

	return !(m_isLoadedFromFile = false);
}

bool SimpleMesh::loadToGpu()
{
	if ( m_isLoadedToGpu )
		return true;
	D3D9RenderSystem * rs = Core::getSingleton().getRenderSystem();
	
	//加载顶点数据
	int vertexType = getD3dVertexType( m_fvfVec );
	IDirect3DVertexBuffer9 * vbuf = rs->createVertexBuffer( m_name , m_vertexDataSize , 0 , vertexType , D3DPOOL_DEFAULT );
	if ( !vbuf )
	{
		return false;
	}
	
	void * pData = NULL;
	vbuf->Lock( 0 , m_vertexDataSize , &pData , 0 );
	memcpy( pData , m_vertexData , m_vertexDataSize );
	vbuf->Unlock();
	
	//加载索引数据
	IDirect3DIndexBuffer9 * ibuf = rs->createIndexBuffer( m_name , m_indexDataSize , 0 , (m_indexType == INDEX_16)?D3DFMT_INDEX16:D3DFMT_INDEX32,D3DPOOL_DEFAULT);
	if( !ibuf )
		return false;

	ibuf->Lock( 0 , m_indexDataSize , &pData , 0 );
	memcpy( pData , m_indexData , m_indexDataSize );
	ibuf->Unlock();


	return true;
}

bool SimpleMesh::unloadFromGpu()
{
	if( !m_isLoadedToGpu )
		return true;

	D3D9RenderSystem * rs = Core::getSingleton().getRenderSystem();
	rs->destoryVertexBuffer( m_name );
	rs->destoryIndexBuffer( m_name );
	m_isLoadedToGpu = false;

	return true;
}