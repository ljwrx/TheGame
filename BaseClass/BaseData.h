#pragma once
#ifndef __BaseData__
#define __BaseData__

#include "Tool.h"

class BaseData
{
public:
	BaseData(void);
	BaseData(int data);
	BaseData(const BaseData& basedata){ _basedata = basedata._basedata; }
	~BaseData();

	virtual inline int getDataId()		{ return 0; }
	virtual inline int getAttackStyle()	{ return TOOL::GetDataFromSize(_basedata, 3, 0); }
	virtual inline int getBuffStyle()	{ return TOOL::GetDataFromSize(_basedata, 3, 3); }
	virtual inline int getAttackForce()	{ return TOOL::GetDataFromSize(_basedata, 8, 6); }
	virtual inline int getAttackSpeed() { return TOOL::GetDataFromSize(_basedata, 5, 14); }
	virtual inline int getMaxHealth()	{ return TOOL::GetDataFromSize(_basedata, 8, 19); }
	virtual inline int getMoveSpeed()	{ return TOOL::GetDataFromSize(_basedata, 5, 27); }

private:
	int _basedata;
};

#endif