#include "stdafx.h"
#include "SceneGraphNode.h"

SceneGraphNode::SceneGraphNode( const std::string & name , SceneGraph * pSG )
:m_name(name),m_graph(pSG),m_attachedMesh(NULL),m_parentNode(NULL)
{
	m_pos.x = m_pos.y = m_pos.z = 0.0f;
	m_scale.x = m_scale.y = m_scale.z = 1.0f;
}

SceneGraphNode::~SceneGraphNode()
{
	//删除所有子结点
	removeAllChildNode();
	
	//从父结点上删除自己
	if( m_parentNode )
		m_parentNode->removeChildNode( this );
}

void SceneGraphNode::addChildNode( SceneGraphNode * node )
{
	if( node->m_parentNode )
	{
		node->m_parentNode->removeChildNode( node );
	}
	node->m_parentNode = this;
	m_childNodeVec.push_back( node );
}

bool SceneGraphNode::hasChild( SceneGraphNode * node )
{
	bool ret = false;
	size_t size = m_childNodeVec.size();
	for( size_t i = 0 ; i < size ; i++ )
	{
		if ( m_childNodeVec[i] == node )
		{
			ret = true;
			break;
		}
	}
	return ret;
}

void SceneGraphNode::removeChildNode( SceneGraphNode * node )
{
	for( childNodeVecItor it = m_childNodeVec.begin() ; it != m_childNodeVec.end() ; it++ )
	{
		if ( (*it) == node )
		{
			(*it)->m_parentNode = NULL;//将字节点的父结点设空
			m_childNodeVec.erase(it);
			break;
		}
	}
}

void SceneGraphNode::removeAllChildNode()
{
	size_t size = m_childNodeVec.size();
	for( size_t i = 0 ; i < size ; i++ )
	{
		m_childNodeVec[i]->m_parentNode = NULL;
	}
	m_childNodeVec.clear();
}

void SceneGraphNode::attachMesh( SimpleMesh * pMesh )
{
	m_attachedMesh = pMesh;
}

void SceneGraphNode::detachMesh()
{
	m_attachedMesh = NULL;
}