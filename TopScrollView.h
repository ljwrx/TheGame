#pragma once
#ifndef __TopScrollView__
#define __TopScrollView__

#include "cocos2d.h"

USING_NS_CC;

class TopScrollView :
	public LayerColor
{
public:
	~TopScrollView();

	static TopScrollView *create();
	virtual bool init();

	virtual void update(float dt);
	virtual void updateMove(float dt);

	virtual bool onTouchBegan(Touch *pTouch,Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch,Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch,Event *pEvent);
	virtual void onEnter();
	virtual void onExit();

private:
	TopScrollView();
	Point m_touchPoint;
	Point m_touchCurPoint;
	Point m_touchMovePoint;

	bool isDragging;//是否在拖拽状态

	float m_touchMoveDisplace;
	float lastX;//上个图层内容x坐标
	float Vo;//松手时的初速度
	float xvel;//在x轴上的瞬时速度
	float acceleration;//加速度
	float f;//合外力
	double distance;//每帧移动距离
	float moveDistance;//update最终移动位置
	float F1;
	float F2;
	float F3;
	float m_moveDisplace;
	float layerLocationX;//layer某一帧所在横坐标

	int maxX;//最大x坐标
	int minX;//最小x坐标
	int isPositive;

	Sprite *masterLayer;
	Sprite *spriteLayer;
	Sprite *propLayer;

};

#endif