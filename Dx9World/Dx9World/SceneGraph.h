/********************************************************************
	created:	2012/06/17
	created:	17:6:2012   15:21
	filename: 	g:\work\projects\DeepRender\Dx9World\Dx9World\SceneGraph.h
	author:		–ÏÌµ
	
	purpose:	≥°æ∞π‹¿Ì∆˜
*********************************************************************/

#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

#include "MapManager.h"

class SceneGraphNode;
class SceneGraph : MapManager<SceneGraphNode>
{
public:
	SceneGraph( const std::string & name );
	~SceneGraph();
public:
	SceneGraphNode * createSceneGraphNode( const std::string & name );
	SceneGraphNode * getSceneGraphNode( const std::string & name );
	void destorySceneGraphNode( const std::string & name );
	void destoryAllSceneGraphNode();

	SceneGraphNode * getRootSceneNode() { return m_rootNode; }
private:
	std::string m_name;
	SceneGraphNode * m_rootNode;
};

#endif //__SCENEGRAPH_H__
