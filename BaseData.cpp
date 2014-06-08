#include "BaseData.h"

BaseData::BaseData(int data)
{
	basedata = 0;
	basedata = data;
}

BaseData::~BaseData()
{
}

int BaseData::getAttackStyle()
{
	unsigned int attackstyle = 0;
	attackstyle = TOOL::GetDataFromSize(basedata,5,0);
	return attackstyle;
}

int BaseData::getBuffStyle()
{
	unsigned int buffstyle = 0;
	buffstyle = TOOL::GetDataFromSize(basedata,5,5);
	return buffstyle;
}

int BaseData::getAttackForce()
{
	unsigned int attackforce = 0;
	attackforce = TOOL::GetDataFromSize(basedata,8,10);
	return attackforce;
}

int BaseData::getAttackSpeed()
{
	unsigned int attackspeed = 0;
	attackspeed = TOOL::GetDataFromSize(basedata,3,18);
	return attackspeed;
}

int BaseData::getMaxHealth()
{
	unsigned int maxhealth = 0;
	maxhealth = TOOL::GetDataFromSize(basedata,8,21);
	return maxhealth;
}

int BaseData::getMoveSpeed()
{
	unsigned int movespeed = 0;
	movespeed = TOOL::GetDataFromSize(basedata,3,29);
	return movespeed;
}