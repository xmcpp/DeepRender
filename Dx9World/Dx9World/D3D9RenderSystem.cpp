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

	//��ʼ��dx9�豸
	m_d3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( !m_d3d ) return false;

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;  //4������ݣ����ú���Ҫ����Ⱦ״̬������
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP ;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//�����Զ���Ⱥ�ģ�建�����������������ʹ�øù��ܣ�����ͬʱ���û�������ʽ24λ��ȣ�8λģ��
	d3dpp.EnableAutoDepthStencil=TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	//����ֻ��ʹ��D3DCREATE_SOFTWARE_VERTEXPROCESSING��Ӳ���ķ�ʽ�ʼǱ����Բ���ʹ��
	if( FAILED( m_d3d->CreateDevice(  D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , m_hwnd , D3DCREATE_HARDWARE_VERTEXPROCESSING , &d3dpp , &m_p3d9Dev ) ) )
	{
		//����Ӳ�����㴦��ʧ���ˣ����Ի��ģʽ
		if( FAILED( m_d3d->CreateDevice(  D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , m_hwnd , D3DCREATE_MIXED_VERTEXPROCESSING , &d3dpp , &m_p3d9Dev ) ) )
		{
			//�������ģʽʧ���ˣ�������ģʽ
			if( FAILED( m_d3d->CreateDevice(  D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , m_hwnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING , &d3dpp , &m_p3d9Dev ) ) )
			{
				//MessageBox( m_hwnd , "�����豸d3d�豸ʧ�ܡ�" , "Error" , MB_OK );
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