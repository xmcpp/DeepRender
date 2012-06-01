#pragma once

#include "Singleton.h"

class Camera : public Singleton<Camera>
{
public:
	Camera();
	~Camera();

public:
	//改变摄像机的位置
	void setPosition( float x , float y , float z );
	
	//获得摄像机的位置
	const D3DXVECTOR3 & getPosition(){ return m_pos; }

	//设置摄像机的朝向
	void setOrientation( const D3DXVECTOR3 & ori );

	//获得摄像机的朝向
	const D3DXVECTOR3 & getOrientation() { return m_orient; }

	//移动摄像机(相对位置，绝对位置直接采用setPosition)，参数为移动的矢量
	void moveRelative( D3DXVECTOR3 vec );

	void yaw( float angle );
	void pitch( float angle );
	void roll( float angle );
	
public:
	D3DXMATRIX & getViewMatrix( );
	D3DXMATRIX & getProjectMatrix( );

public:
	void setCameraMirrorByPlane( D3DXPLANE & plane ); //设置相机按照plane进行镜像处理
	void clearCamerMirror(); //关闭镜像功能
private:
	//根据旋转矩阵更新摄像机朝向
	void _updateOrient( const D3DXMATRIX & mat );
	
	//根据指定的矩阵转换点
	D3DXVECTOR3  _transPointByMatrix( const D3DXVECTOR3 & vec , const D3DXMATRIX & mat );
	
	//根据指定的矩阵转换向量
	D3DXVECTOR3  _transVectorByMatrix( const D3DXVECTOR3 & vec , const D3DXMATRIX & mat );

private:
	D3DXVECTOR3 m_pos; //摄像机的位置
	D3DXVECTOR3 m_orient; //摄像机朝向

	D3DXVECTOR3 m_up; //摄像机上方
	

	D3DXMATRIX m_viewMat;
	D3DXMATRIX m_prjMat;

	D3DXMATRIX m_tmpMat; //临时矩阵，参与计算的中间结果，平时不要使用
	
	D3DXPLANE m_mirrorPlane;//用于处理摄像机镜像
	bool m_mirrorEnable;
};