#include "stdafx.h"
#include "Testcase.h"

#include "MeshFileIO.h"

void Testcase::doTest()
{
	int i = sizeof(MeshFileHead);
	std::vector<VERTEX_FORMAT_TYPE> ftVec;
	ftVec.push_back(VT_POS_XYZ);
	ftVec.push_back(VT_UV1);

	float vertexData[20] = {
		0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,1.0f,1.0f,
		0.0f,1.0f,0.0f,0.0f,1.0f
	};

	short indexData[6] = {0,1,2,1,2,3};

	MeshFileWriter writer;
	writer.setMaterialName("TestMat.mat");
	writer.setVertexType( ftVec );
	writer.setVertexData(vertexData,4);
	writer.setIndexType(INDEX_16);
	writer.setIndexData(indexData,6);
	writer.saveToFile( "a.mesh" );

	

	MeshFileReader reader;
	reader.openMeshFile("a.mesh");
	std::string matName = reader.getMaterialName();

	std::vector<VERTEX_FORMAT_TYPE> ftVec2;
	ftVec2 = reader.getVertextType();
	int vertexSize = 0;

	INDEX_TYPE indexType = reader.getIndexType();
	short * indexData16 = NULL;
	int * indexData32 = NULL;
	if ( indexType == INDEX_16 )
	{
		indexData16 = new short[reader.getIndexCount()];
		reader.getIndexData( indexData16 );
	}
	else
	{
		indexData32 = new int[reader.getIndexCount()];
		reader.getIndexData( indexData32 );
	}
	
	for ( unsigned int i = 0 ; i < ftVec2.size() ; i++ )
	{
		vertexSize += getVertexTypeSize( ftVec2[i] );
	}
	vertexSize = vertexSize / 4;
	
	long count = vertexSize * reader.getVertexCount();
	float * vertexData2 = new float[count];
	reader.getVertexData( vertexData2 );
	
	for ( long i = 0 ; i < count ; i++)
	{
		float v = vertexData[i];
	}
}