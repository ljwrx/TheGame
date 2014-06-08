#include "TopScrollView.h"

USING_NS_CC;

TopScrollView* TopScrollView::create(void)
{
	TopScrollView *tsv = new TopScrollView();
	if (tsv && tsv->init())
	{
		tsv->setTouchEnabled(true);
		tsv->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(tsv);
	}

    return tsv;
}

bool TopScrollView::init()
{
	if (!LayerColor::initWithColor(ccc4(0,0,0,200),1152,108))
	{
		return false;
	}

	masterLayer = Sprite::create("topBackground.png");
	this->addChild(masterLayer,1,1);
	masterLayer->setPosition(192,0);
	masterLayer->setScale(2);

	spriteLayer = Sprite::create("topBackground.png");
	this->addChild(spriteLayer,1,2);
	spriteLayer->setPosition(576,0);
	spriteLayer->setScale(2);

	propLayer = Sprite::create("topBackground.png");
	this->addChild(propLayer,1,1);
	propLayer->setPosition(960,0);
	propLayer->setScale(2);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TopScrollView::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(TopScrollView::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(TopScrollView::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	isDragging = false;
	lastX = 0.0f;
	xvel = 0.0f;
	acceleration = 0.0f;
	f = 0.0f;

	maxX = 0;
	minX = -768;

	return true;
}

void TopScrollView::update(float dt)
{
	updateMove(dt);
}

void TopScrollView::updateMove(float dt)
{
	if (!isDragging)
	{
		F1 = 0.0f;
		F2 = 0.0f;
		F3 = 0.0f;
		layerLocationX = 0.0f;

		layerLocationX = getPositionX();

		if (layerLocationX > maxX)
		{
			F2 = maxX - layerLocationX;
		}else if (layerLocationX < minX)
		{
			F2 = minX - layerLocationX;
		}

		if (layerLocationX < -192 && layerLocationX > -576)
		{
			if (m_touchCurPoint.x >= 288)
			{
				distance = Vo*Vo*dt/(m_touchCurPoint.x-576)/2;//576为屏宽384的1/2+1/4结果乘2
			}
			else if (m_touchCurPoint.x > 192)
			{
				distance = Vo*Vo*dt/(m_touchCurPoint.x-192)/2;
			}
			else if (m_touchCurPoint.x >= 96)
			{
				distance = Vo*Vo*dt/(m_touchCurPoint.x-192)/2;
			}
			else
			{
				distance = Vo*Vo*dt/(m_touchCurPoint.x+192)/2;
			}
		}
		if (layerLocationX > -192 && layerLocationX < 0)
		{
			if (m_touchCurPoint.x < -288)
			{
				distance = Vo*Vo*dt/(m_touchCurPoint.x+576)/2;
			}
			else if (m_touchCurPoint.x < -192)
			{
				distance = Vo*Vo*dt/(192+m_touchCurPoint.x)/2;
			}
		}
		if (layerLocationX < -576 && layerLocationX > -768)
		{
			if (m_touchCurPoint.x > 672)
			{
				distance = Vo*Vo*dt/(m_touchCurPoint.x-960)/2;//-(768-m_touchCurPoint.x+192)
			}
			else if (m_touchCurPoint.x > 576)
			{
				distance = Vo*Vo*dt/(m_touchCurPoint.x-576)/2;
			}
		}

		F3 = distance;

		f = F1 + F2 + F3;
		acceleration = f;
		xvel += acceleration;

		if ((Vo > 0 && xvel <= 0) || (Vo < 0 && xvel >= 0))
		{
			isDragging = true;
			distance = 0;
			return;
		}

		layerLocationX += xvel*dt;
		setPositionX(layerLocationX);
	}
}

bool TopScrollView::onTouchBegan(Touch *pTouch,Event *pEvent)
{
	m_touchPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
	m_touchCurPoint = m_touchPoint;
	isDragging = true;
	Vo = 0.0f;
	xvel = 0.0f;
	distance = 0;
	return true;
}

void TopScrollView::onTouchMoved(Touch *pTouch,Event *pEvent)
{
	m_touchMovePoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());

	m_touchMoveDisplace = m_touchMovePoint.x - m_touchCurPoint.x;

	if (m_touchMoveDisplace > 0)
	{
		isPositive = 1;
	}else
	{
		isPositive = -1;
	}

	setPosition(getPositionX() + m_touchMoveDisplace,getPositionY());

	m_moveDisplace = m_touchMovePoint.x - m_touchCurPoint.x;
	isPositive = m_moveDisplace > 0 ? 1 : -1;

	m_touchCurPoint = m_touchMovePoint;

	if (m_touchCurPoint.x > 576 && m_touchCurPoint.x <= 672)
	{
		Vo = -m_moveDisplace * 60 * isPositive;
	}
	else if (m_touchCurPoint.x > 192 && m_touchCurPoint.x < 288)
	{
		Vo = -m_moveDisplace * 60 * isPositive;
	}
	else if (m_touchCurPoint.x >= 96 && m_touchCurPoint.x <= 192)
	{
		Vo = -m_moveDisplace * 60 * isPositive;
	} 
	else if (m_touchCurPoint.x < -192 && m_touchCurPoint.x > -288)
	{
		Vo = -m_moveDisplace * 60 * isPositive;
	}
	else
	{
		Vo = m_moveDisplace * 60 * isPositive;
	}
	xvel = Vo;
}

void TopScrollView::onTouchEnded(Touch *pTouch,Event *pEvent)
{
	isDragging = false;
}

void TopScrollView::onEnter()
{
	LayerColor::onEnter();
	scheduleUpdate();
	isDragging = true;
}

void TopScrollView::onExit()
{
	unscheduleUpdate();
	removeAllChildrenWithCleanup(true);
	_eventDispatcher->removeAllEventListeners();
	LayerColor::onExit();
}

TopScrollView::TopScrollView(void)
{
}

TopScrollView::~TopScrollView(void)
{
}
