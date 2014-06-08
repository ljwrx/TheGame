#pragma once
#ifndef __Sprite__Introduce__Popup__
#define __Sprite__Introduce__Popup__

#include "cocos2d.h"
//#include "CocosGUI.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "cocos-ext.h"

USING_NS_CC;
//using namespace cocos2d::extension;

class SpriteIntro :
	public cocos2d::LayerColor , public cocos2d::extension::ScrollViewDelegate
{
public:
	~SpriteIntro();
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView *view);
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView *view);

	static SpriteIntro* create();

	virtual bool init();
	virtual bool initWithDoc(rapidjson::Document *doc);

	//virtual bool onTouchBegan(Touch *pTouch,Event *pEvent);
	//virtual void onTouchMoved(Touch *pTouch,Event *pEvent);
	//virtual void onTouchEnded(Touch *pTouch,Event *pEvent);
	//virtual void onTouchCancelled(Touch *pTouch,Event *pEvent);

	//virtual void onEnter();
	//virtual void onExit();
private:
	SpriteIntro();
	bool addAllEnd;//是否已全部载入精灵介绍
};

#endif