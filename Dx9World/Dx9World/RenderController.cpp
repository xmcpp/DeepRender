#include "stdafx.h"
#include "RenderController.h"
#include "D3D9RenderSystem.h"
#include "Camera.h"

RenderController::RenderController(RenderController::RENDERTARGET type,D3D9RenderSystem * pRS)
:m_targetType(type),m_renderSystem(pRS),m_camera(NULL)
{

}

RenderController::~RenderController()
{

}

bool RenderController::render()
{
	m_renderSystem->clear();
	m_renderSystem->beginRender();
	m_renderSystem->endRender();
	m_renderSystem->present();

	return true;
}