#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <class T> 
class  Singleton
{
protected:
	static	T* ms_Singleton;
public:
	Singleton( void )
	{
		if( ms_Singleton )
			delete ms_Singleton;
		ms_Singleton = static_cast<T*>(this);
	}

	~Singleton( void )
	{   
		ms_Singleton = 0;  
	}

	static T& getSingleton( void )

	{   
		return ( *ms_Singleton );  
	}

	static T* getSingletonPtr( void)
	{
		return ( ms_Singleton );  
	}

};

#endif