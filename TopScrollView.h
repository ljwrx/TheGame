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

	bool isDragging;//�Ƿ�����ק״̬

	float m_touchMoveDisplace;
	float lastX;//�ϸ�ͼ������x����
	float Vo;//����ʱ�ĳ��ٶ�
	float xvel;//��x���ϵ�˲ʱ�ٶ�
	float acceleration;//���ٶ�
	float f;//������
	double distance;//ÿ֡�ƶ�����
	float moveDistance;//update�����ƶ�λ��
	float F1;
	float F2;
	float F3;
	float m_moveDisplace;
	float layerLocationX;//layerĳһ֡���ں�����

	int maxX;//���x����
	int minX;//��Сx����
	int isPositive;

	Sprite *masterLayer;
	Sprite *spriteLayer;
	Sprite *propLayer;

};

#endif