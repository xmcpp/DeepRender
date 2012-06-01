#include "stdafx.h"
#include "Camera.h"

Camera * Singleton<Camera>::ms_Singleton = NULL;

Camera::Camera()
{
	//����Ĭ��λ��
	m_pos.x = 0.0f;
	m_pos.y = 5.0f;
	m_pos.z = -5.0f;
	
	//����������Ϸ�
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;
	
	//����Ĭ�ϳ��򣬴�pos����ԭ��
	m_orient.x = 0.0f;
	m_orient.y = -5.0f;
	m_orient.z = 5.0f;

	D3DXVec3Normalize( &m_orient , &m_orient );

	//����ͶӰ����
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

	//������ת����
	//����up ��orient �����camer����ϵ����y����,������ת����
	//D3DXVec3Cross( &rotateAxis , &m_up  , &m_orient );
	//D3DXVec3Cross( &rotateAxis , &m_orient , &rotateAxis );
	//D3DXMatrixRotationAxis( &m_tmpMat , &rotateAxis , angle );
	D3DXMatrixRotationY( &m_tmpMat , angle );
	//�������������
	_updateOrient( m_tmpMat );
}

void Camera::pitch( float angle )
{
	D3DXVECTOR3 rotateAxis;

	//����up ��orient �����camer����ϵ����x����,������ת����
	D3DXVec3Cross( &rotateAxis , &m_up  , &m_orient );
	D3DXMatrixRotationAxis( &m_tmpMat , &rotateAxis , angle );

	//�������������
	_updateOrient( m_tmpMat );
}

void Camera::roll( float angle )
{
	D3DXMatrixIdentity( &m_tmpMat );
	D3DXMatrixRotationZ( &m_tmpMat , angle );

	//�������������
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
	//���������������ϵ�е�λ��Ϊm_pos,����m_orient,�����Ƶ���������任����״̬������ͶӰ����
	//�������������������ɣ���ת��ƽ�ƣ���������ת��ƽ�ơ�

	//����Ҫ���Ӿ������Ҫ��������ĽǶȿ����硣����Ҫ��������ӵ�ǰ��λ�ñ任��ԭ�㣬����ʹ��ͬ��
	//�ı任������ƽ�ƺ���ת�������Ǳ任���������ȸ�ƽ��ԭ����ֵ���ٳ���ԭ��ת���������ɷ���ת��
	//����������յ��Ӿ���

	D3DXVECTOR3 camX , camY , camZ;
	

	D3DXMatrixIdentity( &m_viewMat );
	
	D3DXVec3Normalize( &m_orient , &m_orient );
	
	if( m_mirrorEnable )
	{
		D3DXMATRIX mat;
		D3DXMatrixReflect( &mat , &m_mirrorPlane );
		
		//��ת��������
		camZ = _transVectorByMatrix( m_orient , mat );
	}
	else
	//������������������ϵ����z����
		camZ = m_orient;

	D3DXVec3Normalize( &camZ , &camZ );

    //!!!�ڹ����Ӿ����ʱ����Ҫ�����в������������ת��Ϊ��λ��������������
    //�޷�Ԥ�ϵĽ������Ϊ�����ľ����Ѿ����ǵ�λ������ת�����󽫻�õ�����Ľ����

	//����up ��orient �����camer����ϵ����x����
	D3DXVec3Cross( &camX , &m_up , &camZ );
	D3DXVec3Normalize( &camX , &camX );

	//������z��������x��������������ϵ��y����
	D3DXVec3Cross( &camY , &camZ , &camX );
	D3DXVec3Normalize( &camY , &camY );

	//��ȷ���������»����������Ӿ������ת������������Ϊ�������ģ����Ծ���ת��
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

		//ת�������λ��
		D3DXVECTOR3 tmpPos = _transPointByMatrix( m_pos , mat );
		matMov.m[3][0] = -tmpPos.x;
		matMov.m[3][1] = -tmpPos.y;
		matMov.m[3][2] = -tmpPos.z;
	}
	else
	{
		//�����������λ�ù����Ӿ����ƽ�ƾ���
		matMov.m[3][0] = -m_pos.x;
		matMov.m[3][1] = -m_pos.y;
		matMov.m[3][2] = -m_pos.z;
	}
	
	//���������Ӿ���(����ת����ƽ��)
	m_viewMat = matMov * matRot;
	
	return m_viewMat;	
}

//����ָ���ľ���ת����
D3DXVECTOR3  Camera::_transPointByMatrix( const D3DXVECTOR3 & vec , const D3DXMATRIX & mat )
{
	D3DXVECTOR3 tmp;

	tmp.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0];
	tmp.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1];
	tmp.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2];
	
	return tmp;
}

//����ָ���ľ���ת������
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