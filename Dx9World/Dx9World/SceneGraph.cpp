#include "stdafx.h"
#include "SceneGraph.h"
#include "SceneGraphNode.h"

SceneGraph::SceneGraph( const std::string & name )
:m_name(name),m_rootNode(NULL)
{
	m_rootNode = new SceneGraphNode( "root" , this );
}

SceneGraph::~SceneGraph()
{
	destoryAllSceneGraphNode();
	delete m_rootNode;
	m_rootNode = NULL;
}

SceneGraphNode * SceneGraph::createSceneGraphNode( const std::string & name )
{
	SceneGraphNode * pNode = this->getObject( name );
	if( !pNode )
	{
		pNode = new SceneGraphNode( name , this );
		addObject( name , pNode );
	}
	return pNode;
}

SceneGraphNode * SceneGraph::getSceneGraphNode( const std::string & name )
{
	return this->getObject( name );
}

void SceneGraph::destorySceneGraphNode( const std::string & name )
{
	this->remove( name , true );
}

void SceneGraph::destoryAllSceneGraphNode()
{
	this->removeAll( true );
}