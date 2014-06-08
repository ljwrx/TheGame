#include "scrollView.h"

USING_NS_CC;

#define SCROLLVIEW_WIDTH	1152
#define SCROLLVIEW_HEIGHT	1536
#define DIALOGMESSAGE_X		87
#define DIALOGMESSAGE_Y		1266
#define DIALOGY				242
#define DIALOGWIDTH			210
#define DIALOGHEIGHT		210
#define AVAILABLEUNITS_PATH	"save\\availableunits.txt"
#define ITEM_IMAGE_PATH		"%c\\item%d.png"
#define SPRITE_IMAGE_PATH	"%c\\saber%d.png"
#define MASTER_IMAGE_PATH	"%c\\master%d.png"

scrollView* scrollView::create(void)
{
	scrollView *sv = new scrollView();
	if (sv && sv->init())
	{
		sv->setTouchEnabled(true);
		sv->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sv);
	}

    return sv;
}

bool scrollView::init()
{
	if ( !LayerColor::initWithColor(ccc4(255,255,255,255),SCROLLVIEW_WIDTH,SCROLLVIEW_HEIGHT) )
    {
        return false;
    }

	isDialog = false;

	auto spritelistener = EventListenerTouchOneByOne::create();
	spritelistener->setSwallowTouches(true);
	spritelistener->onTouchBegan = CC_CALLBACK_2(scrollView::onSpriteTouchBegan,this);
	spritelistener->onTouchMoved = CC_CALLBACK_2(scrollView::onSpriteTouchMoved,this);
	spritelistener->onTouchEnded = CC_CALLBACK_2(scrollView::onSpriteTouchEnded,this);
	
	unsigned int availableMaster = 0;
	unsigned int availableSprite = 0;
	unsigned int availableItem = 0;
	String picUrl;

	String contentStr = FileUtils::getInstance()->getStringFromFile(AVAILABLEUNITS_PATH);
	availableMaster = ((String*)(contentStr.componentsSeparatedByString("-")->objectAtIndex(0)))->intValue();
	availableSprite = ((String*)(contentStr.componentsSeparatedByString("-")->objectAtIndex(1)))->intValue();
	availableItem = ((String*)(contentStr.componentsSeparatedByString("-")->objectAtIndex(2)))->intValue();

	int l = 32;
	int m = 18;
	int n = 9;
	int index;
	char picFrom;
	Sprite *sp;

	picFrom = 'm';
	sp = Sprite::create("m\\master1.png");
	this->addChild(sp,1,1);
	sp->setPosition(32,1436);//1536-100
	_eventDispatcher->addEventListenerWithSceneGraphPriority(spritelistener,this->getChildByTag(1));

	int count = 0;
	for (index = 2; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(availableMaster,index))
		{
			count++;
			picUrl.initWithFormat(MASTER_IMAGE_PATH, picFrom, index);
			sp = Sprite::create(picUrl.getCString());
			this->addChild(sp,1,index);
			sp->setPosition(32+(count)%4*85,1536-(count/4+1)*100);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(spritelistener->clone(),this->getChildByTag(index));
		}
	}
	count = 0;
	picFrom = 's';
	for (index = 1; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(availableSprite,index))
		{
			picUrl.initWithFormat(SPRITE_IMAGE_PATH, picFrom, index);
			sp = Sprite::create(picUrl.getCString());
			this->addChild(sp,1,index+32);
			sp->setPosition(416+(count)%4*85,1536-(count/4+1)*100);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(spritelistener->clone(),this->getChildByTag(index+32));
			count++;
		}
	}
	count = 0;
	picFrom = 'i';
	for (index = 1; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(availableItem,index))
		{
			picUrl.initWithFormat(ITEM_IMAGE_PATH, picFrom, index);
			sp = Sprite::create(picUrl.getCString());
			this->addChild(sp,1,index+64);
			sp->setPosition(800+(count)%4*85,1536-(count/4+1)*100);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(spritelistener->clone(),this->getChildByTag(index+64));
			count++;
		}
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(scrollView::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(scrollView::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(scrollView::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	xvel = 0.0f;
	acceleration = 0.0f;

    return true;
}

scrollView::scrollView()
{
}

scrollView::~scrollView()
{
}

void scrollView::update(float dt)
{
	if (!isDragging && m_moveInstancySpeed != 0)
	{
		layerLocationY = getPositionY();
		acceleration = isPositive*96*dt;
		xvel += acceleration;

		if ((m_moveInstancySpeed > 0 && xvel <= 0) || (m_moveInstancySpeed < 0 && xvel >= 0))
		{
			isDragging = true;
			acceleration = 0.0f;
			isPositive = 0;
			xvel = 0.0f;
			m_moveInstancySpeed = 0.0f;
			return;
		}

		layerLocationY += xvel*dt;

		if (layerLocationY < -1024)
		{
			layerLocationY = -1024;
			isDragging = true;
			acceleration = 0.0f;
			isPositive = 0;
			xvel = 0.0f;
			m_moveInstancySpeed = 0.0f;
		}
		else if (layerLocationY > 0)
		{
			layerLocationY = 0;
			isDragging = true;
			acceleration = 0.0f;
			isPositive = 0;
			xvel = 0.0f;
			m_moveInstancySpeed = 0.0f;
		}

		setPositionY(layerLocationY);
	}
}

bool scrollView::onTouchBegan(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		Point touchPosition = pTouch->getLocation();
		layerLocationX = getPositionX();

		switch (layerLocationX)
		{
		case -384: dialogX = 471;break;
		case 0: dialogX = 87;break;
		case -768: dialogX = 558;break;
		default: dialogX = 471; break;
		}

		Rect rect = Rect(dialogX,DIALOGY,DIALOGWIDTH,DIALOGHEIGHT);

		//点击范围判断检测
		if (!rect.containsPoint(touchPosition))
		{
			this->getChildByTag(0)->setOpacity(0);
			this->getChildByTag(0)->setZOrder(0);
			this->getChildByTag(0)->removeChildByTag(1);
			return true;
		}
		return false;
	}
	m_touchDownPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
	m_firstTouchPointX = m_touchDownPoint.x;
	m_firstTouchPointY = m_touchDownPoint.y;

	m_touchCurPoint = m_touchDownPoint;
	isClip = true;
	isDragging = true;
	isPositive = 0;
	xvel = 0.0f;
	acceleration = 0.0f;
	m_moveInstancySpeed = 0.0f;

	stopAllActions();
	return true;
}

void scrollView::onTouchMoved(Touch *pTouch,Event *pEvent)
{
	isClip = false;

	if (isDialog)
	{
		return;
	}

	touchPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());

	m_moveDisplaceY = touchPoint.y - m_touchCurPoint.y;

	if (m_moveDisplaceY > 0)
	{
		isMoveUp = false;
		isPositive = -1;
	}else
	{
		isMoveUp = true;
		isPositive = 1;
	}

	if (getPositionY() + m_moveDisplaceY < -1024)
	{
		setPosition(getPositionX(),-1024);
	}else if (getPositionY() + m_moveDisplaceY > 0)
	{
		setPosition(getPositionX(),0);
	}else
	{
		setPosition(getPositionX(),getPositionY() + m_moveDisplaceY);
	}
	
	m_moveInstancySpeed = m_moveDisplaceY * 60;
	xvel = m_moveInstancySpeed;

	m_touchCurPoint = touchPoint;
}

void scrollView::onTouchEnded(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		isDialog = false;
		return;
	}

	m_lastTouchPontX = Director::getInstance()->convertToGL(pTouch->getLocationInView()).x;
	m_lastTouchPontY = Director::getInstance()->convertToGL(pTouch->getLocationInView()).y;

	if (fabsf(m_lastTouchPontX-m_firstTouchPointX) >= fabsf(m_lastTouchPontY-m_firstTouchPointY))
	{
		m_moveInstancySpeed = 0;
		if (m_lastTouchPontX-m_firstTouchPointX >= 96 && getPositionX() != 0)
		{
			moveX = MoveTo::create(1.0f,Point::Point(getPositionX()+384,getPositionY()));
			runAction(moveX);
			return;
		}else if (m_lastTouchPontX-m_firstTouchPointX < -96 && getPositionX() != -768)
		{
			moveX = MoveTo::create(0.5f,Point::Point(getPositionX()-384,getPositionY()));
			runAction(moveX);
			return;
		}
	}

	isDragging = false;
}

void scrollView::onEnter()
{
	LayerColor::onEnter();
	scheduleUpdate();
	isMoveUp = false;
	isPositive = 1;
	isDragging = true;
	
	layerLocationX = -384;
	dialogX = 471;

	LayerColor *ObscurationLayer = LayerColor::create(ccc4(0,0,0,200),SCROLLVIEW_WIDTH,SCROLLVIEW_HEIGHT);
	ObscurationLayer->setOpacity(0);

	addChild(ObscurationLayer,0,0);
	ObscurationLayer->setPosition(CCPointZero);

}

void scrollView::onExit()
{
	unscheduleUpdate();
	removeAllChildrenWithCleanup(true);
	_eventDispatcher->removeAllEventListeners();
	LayerColor::onExit();
}

bool scrollView::onSpriteTouchBegan(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		return false;
	}

	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	//获取当前点击点所在的相对按钮的位置坐标
	Point locationInNode = target->convertToNodeSpace(pTouch->getLocation());
	Size s = target->getContentSize();

	Rect rect = Rect(0,0,s.width,s.height);

	//点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("success draw x = %f,y = %f",locationInNode.x,locationInNode.y);
		target->setOpacity(180);
		return true;
	}
	return false;
}

void scrollView::onSpriteTouchMoved(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		return;
	}

	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	//移动当前按钮精灵的坐标位置
	target->setPosition(target->getPosition() + pTouch->getDelta());
}

void scrollView::onSpriteTouchEnded(Touch *pTouch,Event *pEvent)
{
	if (isDialog)
	{
		return;
	}

	auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
	log("sprite onTouchesEnded.. ");
	target->setOpacity(255);

	DialogMessage *dm = DialogMessage::create();
	dm->initDialog("saber.png","saber");
	target->getParent()->getChildByTag(0)->addChild(dm,1,1);
	dm->setAnchorPoint(Point::ZERO);
	dm->setPosition(dm->getParent()->convertTouchToNodeSpace(pTouch));
	dm->setScale(0.01);
	FiniteTimeAction *action1 = ScaleBy::create(2, 100);
	FiniteTimeAction *action2 = FadeIn::create(2);
	FiniteTimeAction *action3 = MoveTo::create(2,ccp(DIALOGMESSAGE_X-getPositionX(),256-getPositionY()));
	dm->runAction(Spawn::create(action1,action2,action3,NULL));

	target->getParent()->getChildByTag(0)->setOpacity(180);
	target->getParent()->getChildByTag(0)->setZOrder(2);

	isDialog = true;

}
