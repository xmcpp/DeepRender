// Dx9WorldUnitTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GlobalInit.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//����ȫ���¼���
	testing::AddGlobalTestEnvironment( new Globalinit() );

	//��ʼ�����в�������
	testing::InitGoogleTest( &argc , argv );

	return RUN_ALL_TESTS();
}
