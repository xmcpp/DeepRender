#pragma once

#include "Singleton.h"

class Camera : public Singleton<Camera>
{
public:
	Camera();
	~Camera();

public:
	//�ı��������λ��
	void setPosition( float x , float y , float z );
	
	//����������λ��
	const D3DXVECTOR3 & getPosition(){ return m_pos; }

	//����������ĳ���
	void setOrientation( const D3DXVECTOR3 & ori );

	//���������ĳ���
	const D3DXVECTOR3 & getOrientation() { return m_orient; }

	//�ƶ������(���λ�ã�����λ��ֱ�Ӳ���setPosition)������Ϊ�ƶ���ʸ��
	void moveRelative( D3DXVECTOR3 vec );

	void yaw( float angle );
	void pitch( float angle );
	void roll( float angle );
	
public:
	D3DXMATRIX & getViewMatrix( );
	D3DXMATRIX & getProjectMatrix( );

public:
	void setCameraMirrorByPlane( D3DXPLANE & plane ); //�����������plane���о�����
	void clearCamerMirror(); //�رվ�����
private:
	//������ת����������������
	void _updateOrient( const D3DXMATRIX & mat );
	
	//����ָ���ľ���ת����
	D3DXVECTOR3  _transPointByMatrix( const D3DXVECTOR3 & vec , const D3DXMATRIX & mat );
	
	//����ָ���ľ���ת������
	D3DXVECTOR3  _transVectorByMatrix( const D3DXVECTOR3 & vec , const D3DXMATRIX & mat );

private:
	D3DXVECTOR3 m_pos; //�������λ��
	D3DXVECTOR3 m_orient; //���������

	D3DXVECTOR3 m_up; //������Ϸ�
	

	D3DXMATRIX m_viewMat;
	D3DXMATRIX m_prjMat;

	D3DXMATRIX m_tmpMat; //��ʱ���󣬲��������м�����ƽʱ��Ҫʹ��
	
	D3DXPLANE m_mirrorPlane;//���ڴ������������
	bool m_mirrorEnable;
};