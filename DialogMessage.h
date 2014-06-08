#pragma once
#ifndef __DialogMessage__
#define __DialogMessage__

#include "cocos2d.h"

USING_NS_CC;

class DialogMessage :
	public cocos2d::LayerColor
{
public:
	~DialogMessage();

	static DialogMessage* create();

	virtual bool init();
	virtual bool initDialog(std::string spriteUrl, std::string spriteDetail);

	//virtual void onEnter();
	//virtual void onExit();
private:
	DialogMessage();
	bool addAllEnd;//是否已全部载入精灵介绍
	bool isClip;
};

#endif