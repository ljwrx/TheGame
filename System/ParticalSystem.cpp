#include "ParticalSystem.h"
#include "ParticalCircle.h"
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
		//auto size = Director::getInstance()->getWinSize();
		//MenuItemImage *hit = MenuItemImage::create("left-round.png","right-round.png", CC_CALLBACK_1(ParticalSys::particalHit,this,1));
		//hit->setPosition(Point(size.width/2,size.height/2));
		//Menu *pStartMenu = Menu::create(hit,nullptr);
		//pStartMenu->setPosition(Point::ZERO);
		//addChild(pStartMenu,1);
		realX = 0;
		realY = 0;
		nowX = 0;
		nowY = 0;
		realLength = 0;
		realDuration = 0;calcX = 0;
	
		return true;
    }

	return false;
}

double ParticalSys::particalFire(int attacktype, Point from, Point direction, double damage)
{
	ParticleSystem *ptcsys;

	switch (attacktype)
	{
	case 1: ptcsys = ParticalCircle::create("");break;
	case 2: ptcsys = ParticalCircle::create("leaf.png");break;
	case 3: ptcsys = ParticalCircle::create();break;
	case 4: ptcsys = ParticalCircle::create();break;
	case 5: ptcsys = ParticalCircle::create();break;
	case 6: ptcsys = ParticalCircle::create();break;
	case 7: ptcsys = ParticalCircle::create();break;
	case 8: ptcsys = ParticalCircle::create();break;
	case 9: ptcsys = ParticalCircle::create();break;
	default: break;
	}

	p = Sprite::create("white.png",Rect(0,0,45,40));//"leaf.png",Rect(-50,-50,50,50)
	p->addChild(ptcsys,0,1);
	ptcsys->setPosition(p->getContentSize().width/2+5,p->getContentSize().height/2);
	addChild(p,1,1);
	p->setPosition(from.x,from.y);

	realLength = 0;

	if (direction.y <= 0)
	{
		damage = -1;
		return damage;
	}

	if (direction.x >= 0)
	{
		calcX = 384 + p->getContentSize().width/2 - from.x;
	}else
	{
		calcX = -p->getContentSize().width/2 - from.x;
	}

	if (calcX*direction.y/direction.x < (512 - from.y))
	{
		realX = calcX + from.x;
		realY = calcX*direction.y/direction.x;
		realLength = sqrt( (realX * realX) + (realY * realY) );
		realDuration = realLength / 500;
	}
	else {
		realX = 192 + (512 - from.y)*direction.x/direction.y;
		realY = 512;
		realLength = sqrt( (realX * realX) + (realY * realY) );
		realDuration = realLength / 500;
	}

	move = MoveTo::create(realDuration,Point(realX,realY));
	end = CallFuncN::create(CC_CALLBACK_1(ParticalSys::particalMoveFinished,this));
	action = Sequence::create(move,end,NULL);
	p->runAction(action);
	return damage;
}

void ParticalSys::particalHit(Object* pSender, int status)
{
	if (status == 1)//击中直接0.3秒后消失
	{
		getChildByTag(1)->stopAllActions();
		DelayTime *waitAction = DelayTime::create(0.3);
		CallFuncN *end2 = CallFuncN::create(CC_CALLBACK_1(ParticalSys::particalMoveFinished,this));
		Action *reaction = Sequence::create(waitAction,end2,NULL);
		getChildByTag(1)->runAction(reaction);
	}
	else if (status == 2)//停止粒子
	{
		getChildByTag(1)->stopAllActions();
	}
	else if (status == 3)//继续飞行
	{
		nowX = getChildByTag(1)->getPositionX();
		nowY = getChildByTag(1)->getPositionY();
		realDuration = sqrt( (realX - nowX)*(realX - nowX) + (realY - nowY)*(realY - nowY) ) / 500;
		move = MoveTo::create(realDuration,Point(realX,realY));
		end = CallFuncN::create(CC_CALLBACK_1(ParticalSys::particalMoveFinished,this));
		action = Sequence::create(move,end,NULL);
		getChildByTag(1)->runAction(action);
	}
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