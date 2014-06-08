#pragma once
#ifndef __ParticalSys__
#define __ParticalSys__

#include "cocos2d.h"
#include "ParticalCircle.h"

USING_NS_CC;

class ParticalSys : public cocos2d::Node
{
public:
	//最多可有31种，可继续扩展
	enum AttributeCategory
	{
		InfantryNormal = 1,//近战普通
		InfantryActive = 2,//近战激活
		InfantryCritical = 3,//近战暴击，随机
		ArcherNormal = 4,//射手普通
		ArcherActive = 5,//射手激活
		WorlockNormal = 6,//术士普通
		WorlockSpecial1 = 7,//术士有多个技能
		WorlockSpecial2 = 8,
		WorlockSpecial3 = 9
	};

	~ParticalSys();
	static ParticalSys *create();
	virtual bool init();

	void particalMoveFinished(Object* pSender);

	virtual Sprite *particalFire(int attacktype, Point from, Point direction, double damage);
	virtual void particalHit(Object *pSender, int status, Sprite *hitptc);
	virtual double getParticalDamage(Sprite *ptc);

	String particalplist;

private:
	ParticalSys();
	int count;
};

#endif