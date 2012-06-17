#include "stdafx.h"
#include "Core.h"
#include "D3D9RenderSystem.h"
#include "SimpleMesh.h"
#include "SimpleMaterial.h"
#include "RenderController.h"
#include "SceneGraph.h"

Core * Singleton<Core>::ms_Singleton = NULL;

Core::Core()
:m_bInit(false),m_renderSystem(NULL),m_meshManager(NULL),m_materialManager(NULL)
{

}

bool Core::init( HWND hwnd )
{
	m_renderSystem = new D3D9RenderSystem();
	m_renderSystem->init( hwnd );

	m_meshManager = new MapManager<SimpleMesh>;
	m_materialManager = new MapManager<SimpleMaterial>;
	
	//默认创建一个渲染控制，类型为窗口类型，作为默认的渲染目标
	RenderController * pCtrl = new RenderController( RenderController::RENDER_WINDOW , m_renderSystem );
	m_renderCtrlVec.push_back( pCtrl );

	m_bInit = true;
	return true;
}

bool Core::update()
{	
	if( !m_bInit ) return true;
	
	for( renderCtrlVecItor it = m_renderCtrlVec.begin() ; it != m_renderCtrlVec.end() ; it++ )
		(*it)->render();

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

SimpleMesh * Core::createMesh( const std::string & meshName , const std::string & path )
{
	SimpleMesh * pMesh = NULL;
	if(!( pMesh = m_meshManager->getObject( meshName ) ) )
	{
		pMesh = new SimpleMesh( meshName );
		if( !pMesh->loadFromFile( path ) )
		{
			delete pMesh; pMesh = NULL;
		}
		m_meshManager->addObject( meshName , pMesh );
	}
	
	return pMesh;
}

void Core::destoryMesh( const std::string & meshName )
{
	m_meshManager->remove( meshName , true );
}

SceneGraph * Core::createSceneGraph( const std::string & name )
{
	SceneGraph * pSG = NULL;
	if(!( pSG = m_sceneGraphManager->getObject( name ) ) )
	{
		pSG = new SceneGraph( name );
		m_sceneGraphManager->addObject( name , pSG );
	}

	return pSG;
}

void Core::destorySceneGraph( const std::string & name )
{
	m_sceneGraphManager->remove( name , true );
}