#ifndef __D3D9RENDERSYSTEM_H__
#define __D3D9RENDERSYSTEM_H__

#include "MapManager.h"

class D3D9RenderSystem
{
public:
	D3D9RenderSystem();
	~D3D9RenderSystem();
public:
	bool init( HWND hwnd );
	
	bool beginRender();
	bool endRender();
	bool present();
	bool clear();
public:
	IDirect3DVertexBuffer9 * createVertexBuffer( const std::string & name , unsigned int bufferSize , int usage , int vertexType , D3DPOOL poolType );
	IDirect3DIndexBuffer9 * createIndexBuffer( const std::string & name , unsigned int bufferSize , unsigned int usage , D3DFORMAT indexFormat , D3DPOOL poolType );
	IDirect3DVertexBuffer9 * getVertexBuffer( const std::string & name );
	IDirect3DIndexBuffer9 * getIndexBuffer( const std::string & name );
	void destoryVertexBuffer( const std::string & name );
	void destoryIndexBuffer(const std::string & name );
private:
	//D3D…Ë±∏÷∏’Î
	IDirect3DDevice9 * m_p3d9Dev ;
	IDirect3D9 * m_d3d ;

	MapManager<IDirect3DIndexBuffer9> m_indexBuffMap;
	MapManager<IDirect3DVertexBuffer9> m_vertexBuffMap;
	
	HWND m_hwnd;
};

#endif //__D3D9RENDERSYSTEM_H__
