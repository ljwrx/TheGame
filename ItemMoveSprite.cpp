#include "ItemMoveSprite.h"


ItemMoveSprite::ItemMoveSprite(void)
{
}


ItemMoveSprite::~ItemMoveSprite(void)
{
}

//菜单选项图标直线飞出
void ItemMoveSprite::iconMove(Sprite *icon,Point from,Point to,float dt,bool direction)
{
	icon->setFlippedX(direction);
	icon->setPosition(from);

	MoveTo *move = MoveTo::create(dt,to);
	CallFuncN *end = CallFuncN::create(this,callfuncN_selector(ItemMoveSprite::moveEnd));
	Action *action = Sequence::create(move,end,NULL);

	icon->runAction(action);
}

void ItemMoveSprite::menuIconMove(MenuItemSprite *icon,Point from,Point to,float dt,bool direction)
{
	//icon->setFlippedX(direction);
	icon->setPosition(from);

	MoveTo *move = MoveTo::create(dt,to);
	CallFuncN *end = CallFuncN::create(this,callfuncN_selector(ItemMoveSprite::moveEnd));
	Action *action = Sequence::create(move,end,NULL);
	
	icon->runAction(action);
}

void ItemMoveSprite::titleMove(Sprite *title,Point from,int acpoint1,int acpoint2,float dt,int orientation,bool direction)
{
	title->setAnchorPoint(ccp(acpoint1,acpoint2));
	title->setPosition(from);

	CCSize s = Director::sharedDirector()->getWinSize();

	title->setFlippedX(direction);
	
	ccBezierConfig b1;

	b1.controlPoint_1 = b1.controlPoint_2 = ccp(s.width/2 - s.width/4*orientation, s.height*4/5);
	b1.endPosition = ccp(s.width/2 - 2*orientation , s.height*4/5);

	FiniteTimeAction *move = Sequence::create(
		BezierTo::create(dt/2,b1),
		RotateTo::create(dt/6,15.0*orientation),
		RotateTo::create(dt/6,0),
		MoveTo::create(dt/6,Point(s.width/2-5*orientation,s.height*4/5)),
		NULL
		);

	CallFuncN *end = CallFuncN::create(this,callfuncN_selector(ItemMoveSprite::moveEnd));
	Action *action = Sequence::create(move,end,NULL);
	title->runAction(action);
}

void ItemMoveSprite::moveEnd(Node *sender)
{
	log("Title Move Successed");
}