#ifndef __GLOBALINIT_H__
#define __GLOBALINIT_H__

class Globalinit : public testing::Environment
{
public:
	virtual void SetUp();
	virtual void TearDown();
};

#endif //__GLOBALINIT_H__
