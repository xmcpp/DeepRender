#ifndef __MESHFILEIOTESTSUITE_H__
#define __MESHFILEIOTESTSUITE_H__

#include "MeshFileIO.h"

TEST(MeshFileIOTestSuite , WriteReadTest)
{
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
	ASSERT_TRUE( writer.saveToFile( "a.mesh" ) );
	

	MeshFileReader reader;
	ASSERT_TRUE(reader.openMeshFile("a.mesh"));
	EXPECT_EQ( "TestMat.mat", reader.getMaterialName() );

	std::vector<VERTEX_FORMAT_TYPE> ftVec2;
	ftVec2 = reader.getVertextType();
	int vertexSize = 0;

	INDEX_TYPE indexType = reader.getIndexType();
	EXPECT_EQ( INDEX_16, indexType );
	short * indexData16 = NULL;
	indexData16 = new short[reader.getIndexCount()];
	reader.getIndexData( indexData16 );
	
	EXPECT_EQ( 0, *indexData16++ );
	EXPECT_EQ( 1, *indexData16++ );
	EXPECT_EQ( 2, *indexData16++ );
	EXPECT_EQ( 1, *indexData16++ );
	EXPECT_EQ( 2, *indexData16++ );
	EXPECT_EQ( 3, *indexData16 );

	for ( unsigned int i = 0 ; i < ftVec2.size() ; i++ )
	{
		vertexSize += getVertexTypeSize( ftVec2[i] );
	}
	vertexSize = vertexSize / 4;
	EXPECT_EQ( 5, vertexSize );

	long count = vertexSize * reader.getVertexCount();
	float * vertexData2 = new float[count];
	reader.getVertexData( vertexData2 );

	for ( long i = 0 ; i < count ; i++)
	{
		EXPECT_EQ( vertexData[i], vertexData2[i] );
	}


}

#endif //__MESHFILEIOTESTSUITE_H__
