#include "stdafx.h"
#include "Camera.h"

Camera * Singleton<Camera>::ms_Singleton = NULL;

Camera::Camera()
{
	//设置默认位置
	m_pos.x = 0.0f;
	m_pos.y = 5.0f;
	m_pos.z = -5.0f;
	
	//设置摄像机上方
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;
	
	//设置默认朝向，从pos看向原点
	m_orient.x = 0.0f;
	m_orient.y = -5.0f;
	m_orient.z = 5.0f;

	D3DXVec3Normalize( &m_orient , &m_orient );

	//构造投影矩阵
	D3DXMatrixPerspectiveFovLH( &m_prjMat, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	
	m_mirrorEnable = false;

}

Camera::~Camera()
{

}

void Camera::setPosition( float x , float y , float z )
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Camera::setOrientation( const D3DXVECTOR3 & ori )
{
	D3DXVec3Normalize( &m_orient , &ori );
}

void Camera::moveRelative( D3DXVECTOR3 vec )
{
	m_pos+=vec;
}

void Camera::yaw( float angle )
{
	D3DXVECTOR3 rotateAxis;

	//构造旋转矩阵
	//根据up 和orient 计算出camer坐标系的正y向量,用于旋转操作
	//D3DXVec3Cross( &rotateAxis , &m_up  , &m_orient );
	//D3DXVec3Cross( &rotateAxis , &m_orient , &rotateAxis );
	//D3DXMatrixRotationAxis( &m_tmpMat , &rotateAxis , angle );
	D3DXMatrixRotationY( &m_tmpMat , angle );
	//更新摄像机朝向
	_updateOrient( m_tmpMat );
}

void Camera::pitch( float angle )
{
	D3DXVECTOR3 rotateAxis;

	//根据up 和orient 计算出camer坐标系的正x向量,用于旋转操作
	D3DXVec3Cross( &rotateAxis , &m_up  , &m_orient );
	D3DXMatrixRotationAxis( &m_tmpMat , &rotateAxis , angle );

	//更新摄像机朝向
	_updateOrient( m_tmpMat );
}

void Camera::roll( float angle )
{
	D3DXMatrixIdentity( &m_tmpMat );
	D3DXMatrixRotationZ( &m_tmpMat , angle );

	//更新摄像机朝向
	_updateOrient( m_tmpMat );
}

void Camera::_updateOrient( const D3DXMATRIX & mat )
{
	float ox , oy , oz;
	ox = m_orient.x * mat.m[0][0] + m_orient.y * mat.m[1][0] + m_orient.z * mat.m[2][0] + mat.m[3][0];
	oy = m_orient.x * mat.m[0][1] + m_orient.y * mat.m[1][1] + m_orient.z * mat.m[2][1] + mat.m[3][1];
	oz = m_orient.x * mat.m[0][2] + m_orient.y * mat.m[1][2] + m_orient.z * mat.m[2][2] + mat.m[3][2];
	
	m_orient.x = ox;
	m_orient.y = oy;
	m_orient.z = oz;

	D3DXVec3Normalize( &m_orient , &m_orient );
}

D3DXMATRIX & Camera::getViewMatrix( )
{
	//D3DXMatrixLookAtLH( &m_viewMat, &m_pos , &( m_pos + m_orient) , &m_up );
	//摄像机在世界坐标系中的位置为m_pos,朝向m_orient,首先推导将摄像机变换到此状态的世界投影矩阵。
	//这个矩阵由两个部分组成：旋转和平移，并且先旋转后平移。

	//我们要求视矩阵就是要从摄像机的角度看世界。所以要将摄像机从当前的位置变换回原点，于是使用同样
	//的变换矩阵，先平移后旋转。由于是变换回来所以先负平移原来的值，再乘以原旋转矩阵的逆完成反旋转。
	//于是求得最终的视矩阵。

	D3DXVECTOR3 camX , camY , camZ;
	

	D3DXMatrixIdentity( &m_viewMat );
	
	D3DXVec3Normalize( &m_orient , &m_orient );
	
	if( m_mirrorEnable )
	{
		D3DXMATRIX mat;
		D3DXMatrixReflect( &mat , &m_mirrorPlane );
		
		//旋转方向向量
		camZ = _transVectorByMatrix( m_orient , mat );
	}
	else
	//摄像机朝向就是视坐标系的正z方向
		camZ = m_orient;

	D3DXVec3Normalize( &camZ , &camZ );

    //!!!在构造视矩阵的时候需要将所有参与运算的向量转换为单位向量，否则会出现
    //无法预料的结果。因为给出的矩阵已经不是单位向量的转换矩阵将会得到错误的结果。

	//根据up 和orient 计算出camer坐标系的正x向量
	D3DXVec3Cross( &camX , &m_up , &camZ );
	D3DXVec3Normalize( &camX , &camX );

	//根据正z向量和正x向量计算视坐标系正y向量
	D3DXVec3Cross( &camY , &camZ , &camX );
	D3DXVec3Normalize( &camY , &camY );

	//用确定的三个新基向量构成视矩阵的旋转矩阵的逆矩阵，因为是正交的，所以就是转置
	D3DXMATRIX matRot;
	D3DXMatrixIdentity( &matRot );
	matRot.m[0][0] = camX.x;
	matRot.m[0][1] = camY.x;
	matRot.m[0][2] = camZ.x;

	matRot.m[1][0] = camX.y;
	matRot.m[1][1] = camY.y;
	matRot.m[1][2] = camZ.y;

	matRot.m[2][0] = camX.z;
	matRot.m[2][1] = camY.z;
	matRot.m[2][2] = camZ.z;
	
	D3DXMATRIX matMov;
	D3DXMatrixIdentity( &matMov );

	if( m_mirrorEnable )
	{
		D3DXMATRIX mat;
		D3DXMatrixReflect( &mat , &m_mirrorPlane );

		//转换摄像机位置
		D3DXVECTOR3 tmpPos = _transPointByMatrix( m_pos , mat );
		matMov.m[3][0] = -tmpPos.x;
		matMov.m[3][1] = -tmpPos.y;
		matMov.m[3][2] = -tmpPos.z;
	}
	else
	{
		//根据摄像机的位置构成视矩阵的平移矩阵
		matMov.m[3][0] = -m_pos.x;
		matMov.m[3][1] = -m_pos.y;
		matMov.m[3][2] = -m_pos.z;
	}
	
	//生成最终视矩阵(先旋转，后平移)
	m_viewMat = matMov * matRot;
	
	return m_viewMat;	
}

//根据指定的矩阵转换点
D3DXVECTOR3  Camera::_transPointByMatrix( const D3DXVECTOR3 & vec , const D3DXMATRIX & mat )
{
	D3DXVECTOR3 tmp;

	tmp.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0];
	tmp.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1];
	tmp.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2];
	
	return tmp;
}

//根据指定的矩阵转换向量
D3DXVECTOR3  Camera::_transVectorByMatrix( const D3DXVECTOR3 & vec , const D3DXMATRIX & mat )
{
	D3DXVECTOR3 vecStartPoint ,vecEndPoint;
	
	vecStartPoint = _transPointByMatrix( vec , mat );
	vecEndPoint = _transPointByMatrix( D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , mat );
	
	return vecStartPoint - vecEndPoint;
}

D3DXMATRIX & Camera::getProjectMatrix( )
{
	return m_prjMat;
}

void Camera::setCameraMirrorByPlane( D3DXPLANE & plane )
{
	m_mirrorEnable = true;
	m_mirrorPlane = plane;
}

void Camera::clearCamerMirror()
{
	m_mirrorEnable = false;
}