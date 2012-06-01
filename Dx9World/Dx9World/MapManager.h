/***********************************
基于map容器的各类管理器模板

Author: 苗琳

Date: 2009.6.3

Update: 2010.12.22 改进了迭代模式相关函数，并兼容旧版本  by 苗琳
************************************/

#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__


template<typename T >
class MapManager
{
public:
	typedef T* Tptr;		///对象指针类型声明
	typedef std::map<std::string, Tptr> ObjectMap;	///对象容器类型声明
	typedef typename ObjectMap::iterator ObjectIterator;	///对象容器迭代器
protected:
	ObjectMap m_ObjectMap;	///map容器
	ObjectIterator mCurrentObjectIterator; ///当前迭代器


public:
	/**构造函数*/
	MapManager(){}
	/**析构函数*/
	virtual 	~MapManager()
	{
		
	}
	
	/**添加对象
	@param name 对象名称
	@param object 对象指针
	@return 返回添加的对象指针,如果对象已经存在，返回null
			添加返回信息方便使用者可以嵌套调用这个方法
			比如 return addObject("aa" , new p() );
	*/
	Tptr addObject( const std::string& name , Tptr object )
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if( it != m_ObjectMap.end() ) return NULL;
		
		m_ObjectMap.insert(std::make_pair(name,object));
		return object;
	}


	/**获得对象
	@param name 对象名称
	@return 返回对象指针,如果对象不存在，返回null
	*/
	Tptr getObject(const std::string& name)
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if(it!=m_ObjectMap.end())
		{
			return it->second;
		}
		return NULL;
	}


	/**销毁一个对象
	@param name 对象名称
	@return 返回对象指针
	*/
	bool  remove(const std::string& name , bool bDelete = false )
	{
		ObjectIterator it = m_ObjectMap.find(name);
		if(it!=m_ObjectMap.end())
		{
			if( bDelete )
				delete it->second;
			m_ObjectMap.erase(it);
			return true;
		}

		return false;
	}

	/**销毁所有对象
	*/
	void  removeAll( bool bDelete = false )
	{
		if ( bDelete )
		{
			ObjectIterator	it = m_ObjectMap.begin();
			for(;it!=m_ObjectMap.end();++it)
			{
				delete it->second;
			}
		}
		
		m_ObjectMap.clear();
	}


	///////////////////////////////迭代模式///////////////////////////////////////////

//推荐的

	/*返回map开始位置的迭代器
	@remark 迭代器可以++操作
	*/
	ObjectIterator BeginObjectIterator()
	{
		return m_ObjectMap.begin();
	}
	/*返回map结束位置的迭代器
	@remark 用来判断是否到了末尾
	*/
	ObjectIterator EndObjectIterator()
	{
		return m_ObjectMap.end();
	}
	/*通过指定的迭代器删除物体
	@param iterator 要删除物体的位置迭代器
	*/
	ObjectIterator DestoryObjectByIterator(ObjectIterator iterator)
	{
		delete iterator->second;
		return m_ObjectMap.erase(iterator);
	}
};


#endif	//__MAPMANAGER_H__
