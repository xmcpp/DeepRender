#ifndef __CORE_H__
#define __CORE_H__

#include "Singleton.h"
#include "MapManager.h"

class D3D9RenderSystem;
class SimpleMesh;
class SimpleMaterial;
class RenderController;
class SceneGraph;
class Core : public Singleton<Core>
{
public:
	Core();
public:
	bool init( HWND hwnd );
	bool update();
	bool clear();
public:
	SimpleMesh * createMesh( const std::string & meshName , const std::string & path );
	SimpleMesh * getMesh( const std::string & meshName ){ return m_meshManager->getObject( meshName );}
	void destoryMesh( const std::string & meshName );
	D3D9RenderSystem * getRenderSystem(){ return m_renderSystem; }

	SceneGraph * createSceneGraph( const std::string & name );
	SceneGraph * getSceneGraph( const std::string & name ){ return m_sceneGraphManager->getObject(name);}
	void destorySceneGraph( const std::string & name );
private:
	D3D9RenderSystem * m_renderSystem;
	MapManager<SimpleMesh> * m_meshManager;
	MapManager<SimpleMaterial> * m_materialManager;
	MapManager<SceneGraph> * m_sceneGraphManager;

	std::vector<RenderController*> m_renderCtrlVec;
	typedef std::vector<RenderController*>::iterator renderCtrlVecItor;

	bool m_bInit;
};

#endif //__CORE_H__
