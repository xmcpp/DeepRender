#include "stdafx.h"
#include "Application.h"
#include "Core.h"

bool Application::init( HWND hwnd )
{
	new Core();
	
	bool ret = Core::getSingleton().init( hwnd );
	SimpleMesh * pMesh = Core::getSingleton().createMesh( "TestMesh" , "a.mesh" );
	
	return ret;
}


bool Application::update()
{
	return true;
}

bool Application::clear()
{
	return true;
}