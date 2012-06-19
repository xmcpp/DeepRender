#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class Core;
class Application
{
public:
	bool init( HWND hwnd );
	bool update();
	bool clear();
private:
	Core * m_core;
};

#endif //__APPLICATION_H__
