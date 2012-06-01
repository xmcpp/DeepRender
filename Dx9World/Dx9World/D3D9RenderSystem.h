#ifndef __D3D9RENDERSYSTEM_H__
#define __D3D9RENDERSYSTEM_H__

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
private:
	//D3D…Ë±∏÷∏’Î
	IDirect3DDevice9 * m_p3d9Dev ;
	IDirect3D9 * m_d3d ;
	HWND m_hwnd;
};

#endif //__D3D9RENDERSYSTEM_H__
