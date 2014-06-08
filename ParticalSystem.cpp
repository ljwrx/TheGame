#include "ParticalSystem.h"

USING_NS_CC;

ParticalSys* ParticalSys::create(void)
{
	ParticalSys *ps = new ParticalSys();
	if (ps && ps->init())
	{
		ps->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ps);
	}
    return ps;
}

bool ParticalSys::init()
{
	if ( Node::init())
    {
		count = 1;
		return true;
    }

	return false;
}

Sprite *ParticalSys::particalFire(int attacktype, Point from, Point direction, double damage)
{
	//ParticleSystem *ptcsys;
	ParticalCircle *ptc;
	
	float realX = 0;
	float realY = 0;
	float realDuration = 0;

	switch (attacktype)
	{
	case 1: ptc = ParticalCircle::create(from,direction,damage,"");break;
	case 2: ptc = ParticalCircle::create(from,direction,damage,"leaf.png");break;
	default: break;
	}

	//ptcsys = ptc;

	Sprite *p = Sprite::create("white.png",Rect(0,0,44,40));
	p->addChild(ptc,0,1);
	ptc->setPosition(p->getContentSize().width/2+5,p->getContentSize().height/2);
	addChild(p,1,count);
	p->setPosition(from.x,from.y);

	realX = ptc->realX;
	realY = ptc->realY;
	realDuration = ptc->realDuration;

	MoveTo *move = MoveTo::create(realDuration,Point(realX,realY));
	CallFuncN *end = CallFuncN::create(CC_CALLBACK_1(ParticalSys::particalMoveFinished,this));
	Action *action = Sequence::create(move,end,NULL);
	p->runAction(action);

	count++;

	return p;
}

void ParticalSys::particalHit(Object* pSender, int status, Sprite *hitptc)
{
	if (status == 1)//击中直接0.3秒后消失
	{
		hitptc->stopAllActions();
		DelayTime *waitAction = DelayTime::create(0.3);
		CallFuncN *end2 = CallFuncN::create(CC_CALLBACK_1(ParticalSys::particalMoveFinished,this));
		Action *reaction = Sequence::create(waitAction,end2,NULL);
		hitptc->runAction(reaction);
	}
	else if (status == 2)//停止粒子
	{
		hitptc->stopAllActions();
	}
	else if (status == 3)//继续飞行
	{
		float nowX;
		float nowY;
		float realX2;
		float realY2;
		float realDuration2;
		nowX = hitptc->getPositionX();
		nowY = hitptc->getPositionY();
		realX2 = dynamic_cast<ParticalCircle *>(hitptc->getChildByTag(1))->realX;
		realY2 = dynamic_cast<ParticalCircle *>(hitptc->getChildByTag(1))->realY;
		realDuration2 = sqrt( (realX2 - nowX)*(realX2 - nowX) + (realY2 - nowY)*(realY2 - nowY) ) / 500;
		MoveTo *move2 = MoveTo::create(realDuration2,Point(realX2,realY2));
		CallFuncN *end2 = CallFuncN::create(CC_CALLBACK_1(ParticalSys::particalMoveFinished,this));
		Action *action2 = Sequence::create(move2,end2,NULL);
		hitptc->runAction(action2);
	}
}

double ParticalSys::getParticalDamage(Sprite *ptc)
{
	return dynamic_cast<ParticalCircle *>(ptc->getChildByTag(1))->damage;
}
	

void ParticalSys::particalMoveFinished(Object* pSender)
{
	Sprite *sprite = (Sprite *)pSender;
    this->removeChild(sprite);
}

ParticalSys::ParticalSys()
{
}

ParticalSys::~ParticalSys()
{
}