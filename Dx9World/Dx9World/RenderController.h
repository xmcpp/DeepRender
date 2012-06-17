/********************************************************************
	created:	2012/06/17
	created:	17:6:2012   13:52
	filename: 	g:\work\projects\DeepRender\Dx9World\Dx9World\RenderController.h
	author:		徐淼
	
	purpose:	负责主渲染流程的控制，具体功能由具体的对象完成
*********************************************************************/
#ifndef __RENDERCONTROLLER_H__
#define __RENDERCONTROLLER_H__

class Camera;
class D3D9RenderSystem;
class RenderController
{
public:
	enum RENDERTARGET { RENDER_WINDOW , RENDER_TEXTURE };
public:
	RenderController( RenderController::RENDERTARGET type , D3D9RenderSystem * pRS );
	~RenderController();

public:
	//设置渲染用的摄像机对象
	void setCamera( Camera * cam ){ m_camera = cam; }
	RENDERTARGET getTargetType(){ return m_targetType; }

	bool render();
private:
	RENDERTARGET m_targetType;
	D3D9RenderSystem * m_renderSystem;
	Camera * m_camera;
};

#endif //__RENDERCONTROLLER_H__
