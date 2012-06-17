/********************************************************************
	created:	2012/06/17
	created:	17:6:2012   15:21
	filename: 	g:\work\projects\DeepRender\Dx9World\Dx9World\SceneGraph.h
	author:		–ÏÌµ
	
	purpose:	≥°æ∞π‹¿Ì∆˜
*********************************************************************/

#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

class SceneGraphNode;
class SceneGraph : MapManager<SceneGraph>
{
public:
	SceneGraph( const std::string & name );
	~SceneGraph();
public:
	SceneGraphNode * createSceneGraphNode( const std::string & name );
	SceneGraphNode * getSceneGraphNode( const std::string & name );
private:
	std::string m_name;
};

#endif //__SCENEGRAPH_H__
