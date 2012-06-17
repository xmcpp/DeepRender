/********************************************************************
	created:	2012/06/17
	created:	17:6:2012   15:21
	filename: 	g:\work\projects\DeepRender\Dx9World\Dx9World\SceneGraphNode.h
	author:		���
	
	purpose:	�����������ڵ�
*********************************************************************/

#ifndef __SCENEGRAPHNODE_H__
#define __SCENEGRAPHNODE_H__
class SimpleMesh;
class SceneGraph;
class SceneGraphNode
{
public:
	SceneGraphNode( const std::string & name , SceneGraph * pSG );
	~SceneGraphNode();
public:
	const std::string & getName(){ return m_name; }
	void addChildNode( SceneGraphNode * node );
	bool hasChild( SceneGraphNode * node );
	int getChildCount() { return (int) m_childNodeVec.size(); }
	SceneGraphNode * getChildByIndex( int index ){ return m_childNodeVec[index]; }
	void removeChildNode( SceneGraphNode * node );
	void removeAllChildNode();
	void attachMesh( SimpleMesh * pMesh );
	void detachMesh();
	SceneGraphNode * getParentNode(){ return m_parentNode; }
	
	const D3DXVECTOR3 & getPosition(){ return m_pos; }
	void setPosition( const D3DXVECTOR3 & pos ) { m_pos = pos; }
private:
	std::string m_name;
	SceneGraph * m_graph;

	SceneGraphNode * m_parentNode;
	std::vector<SceneGraphNode*> m_childNodeVec;
	typedef std::vector<SceneGraphNode*>::iterator childNodeVecItor;

	D3DXVECTOR3 m_pos; //��Ը��ڵ��λ��
	D3DXVECTOR3 m_scale; //��Ը��ڵ������

	SimpleMesh * m_attachedMesh;
};

#endif //__SCENEGRAPHNODE_H__
