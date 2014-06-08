#pragma once
#ifndef __BaseData__
#define __BaseData__

#include "Tool.h"

class BaseData
{
public:
	~BaseData();

	BaseData(int data = 0);
	virtual inline int getDataId() {return 0;}

	virtual int getAttackStyle();
	virtual int getBuffStyle();
	virtual int getAttackForce();
	virtual int getAttackSpeed();
	virtual int getMaxHealth();
	virtual int getMoveSpeed();

private:
	int basedata;
};

#endif