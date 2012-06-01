#ifndef __CORE_H__
#define __CORE_H__

#include "Singleton.h"
#include "MapManager.h"

class D3D9RenderSystem;
class SimpleMesh;
class SimpleMaterial;

class Core : public Singleton<Core>
{
public:
	Core();
public:
	bool init( HWND hwnd );
	bool update();
	bool clear();
private:
	D3D9RenderSystem * m_renderSystem;
	MapManager<SimpleMesh*> * m_meshManager;
	MapManager<SimpleMaterial*> * m_materialManager;

	bool m_bInit;
};

#endif //__CORE_H__
