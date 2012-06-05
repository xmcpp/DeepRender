#include "stdafx.h"
#include "Application.h"
#include "Testcase.h"

bool Application::init( HWND hwnd )
{
	Testcase testcase;
	testcase.doTest();

	return true;
}


bool Application::update()
{
	return true;
}

bool Application::clear()
{
	return true;
}