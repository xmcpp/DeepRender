#include "stdafx.h"
#include "Core.h"
#include "D3D9RenderSystem.h"
#include "SimpleMesh.h"
#include "SimpleMaterial.h"

Core * Singleton<Core>::ms_Singleton = NULL;

Core::Core()
:m_bInit(false),m_renderSystem(NULL),m_meshManager(NULL),m_materialManager(NULL)
{

}

bool Core::init( HWND hwnd )
{
	m_renderSystem = new D3D9RenderSystem();
	m_renderSystem->init( hwnd );

	m_meshManager = new MapManager<SimpleMesh*>;
	m_materialManager = new MapManager<SimpleMaterial*>;
	
	m_bInit = true;
	return true;
}

bool Core::update()
{	
	if( !m_bInit ) return true;
	
	m_renderSystem->clear();
	m_renderSystem->beginRender();
	m_renderSystem->endRender();
	m_renderSystem->present();

	return true;
}

bool Core::clear()
{
	m_materialManager->removeAll( true );
	m_meshManager->removeAll( true );

	delete m_meshManager;
	m_meshManager = NULL;

	delete m_meshManager;
	m_materialManager = NULL;

	m_bInit = false;
	return true;
}