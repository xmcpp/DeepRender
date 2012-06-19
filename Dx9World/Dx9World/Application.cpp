#include "stdafx.h"
#include "Application.h"
#include "Core.h"
#include "SceneGraph.h"
#include "SceneGraphNode.h"

bool Application::init( HWND hwnd )
{
	m_core = new Core();
	
	bool ret = m_core->init( hwnd );
	SimpleMesh * pMesh = m_core->createMesh( "TestMesh" , "a.mesh" );
	SceneGraph * pSG = m_core->createSceneGraph( "MainScene" );
	SceneGraphNode * pNode = pSG->getRootSceneNode();
	pNode->attachMesh( pMesh );

	return ret;
}


bool Application::update()
{
	m_core->update();
	return true;
}

bool Application::clear()
{
	return true;
}