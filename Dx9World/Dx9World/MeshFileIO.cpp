#include "stdafx.h"
#include "MeshFileIO.h"

bool MeshFileReader::openMeshFile( const std::string & filename )
{
	m_stream.open( filename.c_str() , std::ios_base::in	| std::ios_base::binary | std::ios_base::_Nocreate);
	if ( !m_stream.is_open() )
	{
		return false;
	}
	
	m_stream.read( reinterpret_cast<char*>( &m_fileHead) , sizeof(MeshFileHead));
	std::string fileType(m_fileHead.head);
	if( fileType != "SimpleMesh" || m_fileHead.version != 1)
	{
		m_stream.close();
		return false;
	}
	
	m_stream.read( reinterpret_cast<char*>( &m_fileHeadInfo) , sizeof(MeshFileHeadInfo));
	return true;
}

bool MeshFileReader::closeMeshFile()
{
	if ( m_stream.is_open() )
	{
		m_stream.close();
	}
	
	return true;
}

std::string MeshFileReader::getMaterialName()
{
	char * str = new char[m_fileHeadInfo.matDataSize];
	m_stream.seekg(m_fileHeadInfo.matDataAddr,std::ios::beg);
	m_stream.read( str , m_fileHeadInfo.matDataSize );
	std::string matName(str);
	delete []str;
	return matName;
}

INDEX_TYPE MeshFileReader::getIndexType()
{
	if( m_fileHeadInfo.indexType == 0 )
	{
		return INDEX_16;
	}
	else
		return INDEX_32;
}

long MeshFileReader::getIndexCount()
{
	return m_fileHeadInfo.indexCount;
}

void MeshFileReader::getIndexData( void * data )
{
	m_stream.seekg(m_fileHeadInfo.indexDataAddr,std::ios::beg);
	m_stream.read( reinterpret_cast<char*>(data) , m_fileHeadInfo.indexDataSize );
}

std::vector<VERTEX_FORMAT_TYPE> MeshFileReader::getVertextType()
{
	std::vector<VERTEX_FORMAT_TYPE> ftVec;
	m_stream.seekg(m_fileHeadInfo.vertexTypeDataAddr,std::ios::beg);
	//枚举按4字节处理
	int v = 0;
	for ( int i = 0 ; i < m_fileHeadInfo.vertexTypeCount ; i++ )
	{
		m_stream.read((char*)&v,4);
		ftVec.push_back( ( VERTEX_FORMAT_TYPE)v );
	}
	
	return ftVec; 
}

long MeshFileReader::getVertexCount()
{
	return m_fileHeadInfo.vertexCount;
}

void MeshFileReader::getVertexData( void * data )
{
	m_stream.seekg(m_fileHeadInfo.vertexDataAddr,std::ios::beg);
	m_stream.read( reinterpret_cast<char*>(data) , m_fileHeadInfo.vertexDataSize );
}

///////////////////

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
	headInfo.matDataSize = m_matName.length() + 1; //多存储1个0
	
	//索引信息
	headInfo.indexType = (char)m_indexType;
	headInfo.indexDataAddr = headInfo.matDataAddr + headInfo.matDataSize;
	headInfo.indexCount = m_indexCount;
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
	headInfo.vertexTypeDataSize = headInfo.vertexTypeCount * 4; //枚举按4字节处理
	
	//顶点信息
	headInfo.vertexDataAddr = headInfo.vertexTypeDataAddr + headInfo.vertexTypeDataSize;
	headInfo.vertexDataSize = 0;
	for ( unsigned int i = 0 ; i < m_vertexType.size() ; i++ )
	{
		headInfo.vertexDataSize += getVertexTypeSize( m_vertexType[i] );
	}
	headInfo.vertexDataSize *= m_vertexCount;
	headInfo.vertexCount = m_vertexCount;

	//写文件头
	m_stream.write( reinterpret_cast<char*>(&head) , sizeof(head) );
	m_stream.write( reinterpret_cast<char*>(&headInfo) , sizeof(headInfo) );
	
	//写材质名称，多写1位，包括0
	m_stream.write( m_matName.c_str() , m_matName.length() + 1);

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

void MeshFileWriter::setIndexData( void * data , long count )
{
	m_indexData = data;
	m_indexCount = count;
}

void MeshFileWriter::setVertexType( const std::vector<VERTEX_FORMAT_TYPE> &vec )
{
	m_vertexType = vec;
}

void MeshFileWriter::setVertexData( void * data , long count )
{
	m_vertexData = data;
	m_vertexCount = count;
}

int getVertexTypeSize( VERTEX_FORMAT_TYPE type )
{
	int retVal = 0;
	switch ( type )
	{
	case VT_POS_XYZW:
	case VT_POS_RHW:
	case VT_NORMAL:
	case VT_DIFFUSE:
	case VT_SPECULAR:
		retVal = 16;
		break;
	case VT_POS_XYZ:
		retVal = 12;
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

int getD3dVertexType( std::vector<VERTEX_FORMAT_TYPE> & vec )
{
	int retVal = 0;
	for( size_t i = 0 ; i < vec.size() ; i++ )
	{
		switch ( vec[i] )
		{
		case VT_POS_XYZW:
			retVal |= D3DFVF_XYZW;
			break;
		case VT_POS_RHW:
			retVal |= D3DFVF_XYZRHW;
			break;
		case VT_NORMAL:
			retVal |= D3DFVF_NORMAL;
			break;
		case VT_DIFFUSE:
			retVal |= D3DFVF_DIFFUSE;
			break;
		case VT_SPECULAR:
			retVal |= D3DFVF_SPECULAR;
			break;
		case VT_POS_XYZ:
			retVal |= D3DFVF_XYZ;
			break;
		case VT_UV0:
			retVal |= D3DFVF_TEX0;
			break;
		case VT_UV1:
			retVal |= D3DFVF_TEX1;
			break;
		case VT_UV2:
			retVal |= D3DFVF_TEX2;
			break;
		case VT_UV3:
			retVal |= D3DFVF_TEX3;
			break;
		case VT_UV4:
			retVal |= D3DFVF_TEX4;
			break;
		case VT_UV5:
			retVal |= D3DFVF_TEX5;
			break;
		case VT_UV6:
			retVal |= D3DFVF_TEX6;
			break;
		case VT_UV7:
			retVal |= D3DFVF_TEX7;
			break;
		case VT_UV8:
			retVal |= D3DFVF_TEX8;
			break;
		}
	}
	
	return retVal;
}