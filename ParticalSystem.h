#pragma once
#ifndef __ParticalSys__
#define __ParticalSys__

#include "cocos2d.h"
#include "ParticalCircle.h"

USING_NS_CC;

class ParticalSys : public cocos2d::Node
{
public:
	//������31�֣��ɼ�����չ
	enum AttributeCategory
	{
		InfantryNormal = 1,//��ս��ͨ
		InfantryActive = 2,//��ս����
		InfantryCritical = 3,//��ս���������
		ArcherNormal = 4,//������ͨ
		ArcherActive = 5,//���ּ���
		WorlockNormal = 6,//��ʿ��ͨ
		WorlockSpecial1 = 7,//��ʿ�ж������
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