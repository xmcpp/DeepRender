#include "stdafx.h"
#include "MeshFileIO.h"

bool MeshFileReader::openMeshFile( const std::string & filename )
{
	m_stream.open( filename.c_str() , std::ios_base::in	| std::ios_base::binary std::ios_base::_Nocreate);
	if ( !m_stream.is_open() )
	{
		return false;
	}

	return true;
}

bool MeshFileReader::closeMeshFile()
{
	m_stream.close();
	return true;
}

bool MeshFileWriter::saveToFile( const std::string & filename )
{
	m_stream.open( filename.c_str() ,std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
	if ( !m_stream.is_open() )
		return false;


	const char * str = "SimpleMesh";
	MeshFileHead head;
	memcpy( head.head , str , 11 );
	head.version = 1;
	
	MeshFileHeadInfo headInfo;
	headInfo.matDataAddr = sizeof(MeshFileHead) + sizeof(MeshFileHeadInfo);
	headInfo.matDataSize = m_matName.length();
	
	//索引信息
	headInfo.indexType = (char)m_indexType;
	headInfo.indexDataAddr = headInfo.matDataAddr + headInfo.matDataSize;
	if ( m_indexType == INDEX_16 )
	{
		headInfo.indexDataSize = m_indexCount * 2;
	}
	else
	{
		headInfo.indexDataSize = m_indexCount * 4;
	}
	
	//顶点类型信息
	headInfo.vertexTypeCount = m_vertexType.size();
	headInfo.vertexTypeDataAddr = headInfo.indexDataAddr + headInfo.indexDataSize;
	headInfo.vertexTypeDataSize = headInfo.vertexTypeCount;
	
	//顶点信息
	headInfo.vertexDataAddr = headInfo.vertexTypeDataAddr + headInfo.vertexTypeDataSize;
	headInfo.vertexDataSize = 0;
	for ( unsigned int i = 0 ; i < m_vertexType.size() ; i++ )
	{
		headInfo.vertexDataSize += getVertexTypeSize( m_vertexType[i] );
	}
	headInfo.vertexDataSize *= m_vertexCount;
	
	//写文件头
	m_stream.write( reinterpret_cast<char*>(&head) , sizeof(head) );
	m_stream.write( reinterpret_cast<char*>(&headInfo) , sizeof(headInfo) );
	
	//写索引
	m_stream.write( reinterpret_cast<char*>(m_indexData) , headInfo.indexDataSize );

	//写顶点类型
	m_stream.write( reinterpret_cast<char*>(&m_vertexType[0]) , headInfo.vertexTypeDataSize );

	//写顶点数据
	m_stream.write( reinterpret_cast<char*>(m_vertexData) , headInfo.vertexDataSize );

	m_stream.close();

	return true;
}

void MeshFileWriter::setMaterialName( const std::string & materialName )
{
	m_matName = materialName;
}

void MeshFileWriter::setIndexType( INDEX_TYPE indexType )
{
	m_indexType = indexType;
}

void MeshFileWriter::setIndexData( int * data , long count )
{
	m_indexData = data;
	m_indexCount = count;
}

void MeshFileWriter::setVertexType( const std::vector<VERTEX_FORMAT_TYPE> &vec )
{
	m_vertexType = vec;
}

void MeshFileWriter::setVertexData( float * data , long count )
{
	m_vertexData = data;
	m_vertexCount = count;
}

int MeshFileWriter::getVertexTypeSize( VERTEX_FORMAT_TYPE type )
{
	int retVal = 0;
	switch ( type )
	{
	case VT_POS:
	case VT_POS_RHW:
	case VT_NORMAL:
	case VT_DIFFUSE:
	case VT_SPECULAR:
		retVal = 16;
		break;
	case VT_UV0:
		retVal = 0;
		break;
	case VT_UV1:
		retVal = 8;
		break;
	case VT_UV2:
		retVal = 16;
		break;
	case VT_UV3:
		retVal = 24;
		break;
	case VT_UV4:
		retVal = 32;
		break;
	case VT_UV5:
		retVal = 40;
		break;
	case VT_UV6:
		retVal = 48;
		break;
	case VT_UV7:
		retVal = 56;
		break;
	case VT_UV8:
		retVal = 64;
		break;
	}
	return retVal;
}