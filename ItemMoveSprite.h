#pragma once


#ifndef __Item__SPRITE__NODE__
#define __Item__SPRITE__NODE__
#include "cocos2d.h"
USING_NS_CC;

class ItemMoveSprite :public cocos2d::Layer
{
public:
	ItemMoveSprite(void);
	~ItemMoveSprite(void);
	
	void iconMove(Sprite *icon,Point from,Point to,float dt,bool direction);
	void menuIconMove(MenuItemSprite *icon,Point from,Point to,float dt,bool direction);
	void titleMove(Sprite *title,Point from,int acpoint1,int acpoint2,float dt,int orientation,bool direction);
	void moveEnd(Node *sender);
};

#endif