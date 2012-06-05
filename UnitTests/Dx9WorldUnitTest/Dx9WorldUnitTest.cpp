// Dx9WorldUnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GlobalInit.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//添加全局事件类
	testing::AddGlobalTestEnvironment( new Globalinit() );

	//初始化所有测试用例
	testing::InitGoogleTest( &argc , argv );

	return RUN_ALL_TESTS();
}

