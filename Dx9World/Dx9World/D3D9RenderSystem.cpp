#include "stdafx.h"
#include "D3D9RenderSystem.h"

D3D9RenderSystem::D3D9RenderSystem()
{

}

D3D9RenderSystem::~D3D9RenderSystem()
{

}

bool D3D9RenderSystem::init( HWND hwnd )
{
	m_hwnd = hwnd;

	//初始化dx9设备
	m_d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( !m_d3d ) return false;

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;  //4倍抗锯齿，设置后还需要在渲染状态中启用
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP ;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//设置自动深度和模板缓冲区，如果不设置则不使用该功能，必须同时设置缓冲区格式24位深度，8位模板
	d3dpp.EnableAutoDepthStencil=TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//这里只能使用D3DCREATE_SOFTWARE_VERTEXPROCESSING，硬件的方式笔记本电脑不能使用
	if( FAILED( m_d3d->CreateDevice(  D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , m_hwnd , D3DCREATE_HARDWARE_VERTEXPROCESSING , &d3dpp , &m_p3d9Dev ) ) )
	{
		//创建硬件顶点处理失败了，尝试混合模式
		if( FAILED( m_d3d->CreateDevice(  D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , m_hwnd , D3DCREATE_MIXED_VERTEXPROCESSING , &d3dpp , &m_p3d9Dev ) ) )
		{
			//创建混合模式失败了，尝试软模式
			if( FAILED( m_d3d->CreateDevice(  D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , m_hwnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING , &d3dpp , &m_p3d9Dev ) ) )
			{
				//MessageBox( m_hwnd , "创建设备d3d设备失败。" , "Error" , MB_OK );
				return false;
			}
		}
	}
	return true;
}

bool D3D9RenderSystem::beginRender()
{
	return !FAILED( m_p3d9Dev->BeginScene() );
}

bool D3D9RenderSystem::endRender()
{
	return !FAILED( m_p3d9Dev->EndScene() );;
}

bool D3D9RenderSystem::present()
{
	m_p3d9Dev->Present( NULL , NULL , NULL , NULL );
	return true;
}

bool D3D9RenderSystem::clear()
{
	m_p3d9Dev->Clear( 0, NULL, D3DCLEAR_TARGET| D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_RGBA(0,0,0,0), 1.0f, 0 );
	return true;
}