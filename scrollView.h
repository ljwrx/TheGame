#pragma once
#ifndef __ScrollView__
#define __ScrollView__

#include "cocos2d.h"
#include "DialogMessage.h"
#include "Tool.h"

USING_NS_CC;

#define WINDOW_WIDTH	1136.0f;
#define WINDOW_HEIGHT	640.0f;
#define TOUCH_DELTA		20;

class scrollView :
	public LayerColor
{
public:
	~scrollView();
	static scrollView *create();
	virtual bool init();
	//CREATE_FUNC(scrollView);
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch *pTouch,Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch,Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch,Event *pEvent);
	virtual void onEnter();
	virtual void onExit();

	virtual bool onSpriteTouchBegan(Touch *pTouch,Event *pEvent);
	virtual void onSpriteTouchMoved(Touch *pTouch,Event *pEvent);
	virtual void onSpriteTouchEnded(Touch *pTouch,Event *pEvent);

private:
	MoveTo *moveY;
	MoveTo *moveX;

	bool isDone;
	bool isMoveUp;
	bool isClip;
	bool isDialog;
	bool isDragging;
	bool isVertical;
	bool isHorizontal;

	int isPositive;
	int dialogX;
	int layerLocationX;

	float m_firstTouchPointX;
	float m_lastTouchPontX;
	float m_firstTouchPointY;
	float m_lastTouchPontY;
	float m_moveInstancySpeed;
	float m_moveToStopTime;
	float m_moveDisplaceY;
	float m_moveToStopDisplace;
	float xvel;
	float acceleration;
	float layerLocationY;

	Point touchPoint;
	Point posPoint;
	Point m_touchDownPoint;
	Point m_touchUpPoint;
	Point m_touchCurPoint;
	Point m_touchEndPoint;
	scrollView();
};

#endif