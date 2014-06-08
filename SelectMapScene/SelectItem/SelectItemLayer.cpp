#include "SelectItemLayer.h"
#include "SelectItemCanditate.h"
#include "..\SelectMap\SelectMapLayer.h"
#include "Tool.h"

USING_NS_CC;

#ifndef ACTION_TIME
#define ACTION_TIME		1.0f
#endif

#define S_CANDITATE_TAG		0
#define I_CANDITATE_TAG		1
#define S_SELECTING_TAG		2
#define I_SELECTING_TAG		3
#define BUTTON_TAG			4

#define UP_ZORDER		5
#define DOWN_ZORDER		6

#define BUTTON_N_IMAGE	"res\\SelectMapRec\\button.png"
#define BUTTON_H_IMAGE	"res\\SelectMapRec\\button.png"
#define CHANGE_N_IMAGE	"res\\SelectMapRec\\change_button_item.png"
#define CHANGE_H_IMAGE	"res\\SelectMapRec\\change_button_item.png"

#define S_SELECTING_X	0.45
#define S_SELECTING_Y	0.6
#define I_SELECTING_X	0.55
#define I_SELECTING_Y	0.55
#define BUTTON_FOR_X	0.1
#define BUTTON_FOR_Y	0.20
#define CHANGE_FOR_X	0.3
#define CHANGE_FOR_Y	0.20

#define POINT_NOT_IN_SPRITE	0
#define SET_INDEX(__index__) ++__index__
#define GET_INDEX(__index__) --__index__


SelectItemLayer::SelectItemLayer()
{
}

SelectItemLayer::~SelectItemLayer()
{
}

bool SelectItemLayer::init(void)
{
	if (!Layer::init())
		return false;

	_nowKind = Soilder;
	_nowSelect = 0;

	Size size = Director::getInstance()->getWinSize();

	Sprite* bg = Sprite::create("res\\SelectMapRec\\BG.png");
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(Point::ZERO);

	this->addChild(bg, 0, 99);

	Sprite* sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::S_CANDITATE, _sList);
	sp->setAnchorPoint(Point::ZERO);
	sp->setTag(S_CANDITATE_TAG);
	this->addChild(sp);

	sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::I_CANDITATE, _iList);
	sp->setAnchorPoint(Point::ZERO);
	sp->setTag(I_CANDITATE_TAG);
	this->addChild(sp);

	sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::I_SELECTING, 0);
	sp->setTag(I_SELECTING_TAG);
	sp->setOpacity(30);
	this->addChild(sp);

	sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::S_SELECTING, 0);
	sp->setTag(S_SELECTING_TAG);
	this->addChild(sp);


	MenuItemImage* mi = MenuItemImage::create(BUTTON_N_IMAGE,
											BUTTON_H_IMAGE,
											CC_CALLBACK_1(SelectItemLayer::_buttonReCallFun, this));
	mi->setPosition(size.width*BUTTON_FOR_X, size.height*BUTTON_FOR_Y);
	mi->setTag(0);

	MenuItemImage* ch = MenuItemImage::create(CHANGE_N_IMAGE,
											CHANGE_H_IMAGE,
											CC_CALLBACK_1(SelectItemLayer::_buttonReCallFun, this));
	ch->setPosition(size.width*CHANGE_FOR_X, size.height*CHANGE_FOR_Y);
	ch->setTag(1);
	
	Menu* menu = Menu::create(mi, ch, nullptr);
	menu->setPosition(Point::ZERO);
	menu->setTag(BUTTON_TAG);
	menu->setEnabled(false);

	this->addChild(menu);


	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;

}

bool SelectItemLayer::initWithMapData(unsigned int data)
{
	if (!Layer::init())
		return false;

	_nowKind = Soilder;
	_nowSelect = 0;

	Size size = Director::getInstance()->getWinSize();

	Sprite* bg = Sprite::create("res\\SelectMapRec\\BG.png");
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(Point::ZERO);

	this->addChild(bg);

	Sprite* sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::S_CANDITATE, _sList);
	sp->setAnchorPoint(Point::ZERO);
	sp->setTag(S_CANDITATE_TAG);
	this->addChild(sp);

	sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::I_CANDITATE, _iList);
	sp->setAnchorPoint(Point::ZERO);
	sp->setTag(I_CANDITATE_TAG);
	this->addChild(sp);

	sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::I_SELECTING, data);
	sp->setTag(I_SELECTING_TAG);
	sp->setOpacity(30);
	this->addChild(sp);

	sp = SelectItemCanditate::create(SelectItemCanditate::ItemKind::S_SELECTING, data);
	sp->setTag(S_SELECTING_TAG);
	this->addChild(sp);

	MenuItemImage* mi = MenuItemImage::create(BUTTON_N_IMAGE,
												BUTTON_H_IMAGE,
												CC_CALLBACK_1(SelectItemLayer::_buttonReCallFun, this));
	mi->setPosition(size.width*BUTTON_FOR_X, size.height*BUTTON_FOR_Y);
	mi->setTag(0);

	MenuItemImage* ch = MenuItemImage::create(CHANGE_N_IMAGE,
												CHANGE_H_IMAGE,
												CC_CALLBACK_0(SelectItemLayer::_changeLayerToLast, this));
	ch->setPosition(size.width*CHANGE_FOR_X, size.height*CHANGE_FOR_Y);
	ch->setTag(1);

	Menu* menu = Menu::create(mi, ch, nullptr);
	menu->setPosition(Point::ZERO);
	menu->setTag(BUTTON_TAG);
	menu->setEnabled(false);
	this->addChild(menu);

	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	this->setVisible(false);
	return true;
}

SelectItemLayer* SelectItemLayer::createWithMapData(unsigned int data)
{
	SelectItemLayer* pRet = new SelectItemLayer();
	if (pRet && pRet->initWithMapData(data))
		pRet->autorelease();
	else
	{
		if (pRet)
			delete pRet;
		pRet = nullptr;
	}
	return pRet;
}


void SelectItemLayer::onEnter(void)
{
	Layer::onEnter();

	Node* node = nullptr;
	Size size = Director::getInstance()->getWinSize();

	node = this->getChildByTag(S_CANDITATE_TAG);
	node->setPosition(0, -node->getContentSize().height);
	node->runAction(Sequence::create(MoveTo::create(ACTION_TIME, Point::ZERO), CallFunc::create([&](){this->setTouchEnabled(true); }), nullptr));

	this->getChildByTag(I_CANDITATE_TAG)->setPosition(0, -this->getChildByTag(I_CANDITATE_TAG)->getContentSize().height);

	node = this->getChildByTag(S_SELECTING_TAG);
	node->setOpacity(0);
	node->setPosition(0, size.height);
	node->runAction(Spawn::createWithTwoActions(MoveTo::create(ACTION_TIME, Point(size.width*S_SELECTING_X, size.height*S_SELECTING_Y))
												, FadeTo::create(ACTION_TIME, 255)));
	node = this->getChildByTag(I_SELECTING_TAG);
	node->setOpacity(0);
	node->setPosition(size.width, 0);
	node->runAction(Spawn::createWithTwoActions(MoveTo::create(ACTION_TIME, Point(size.width*I_SELECTING_X, size.height*I_SELECTING_Y))
												, FadeTo::create(ACTION_TIME, 30)));

	node = this->getChildByTag(BUTTON_TAG)->getChildByTag(0);
	node->setOpacity(0);
	node->runAction(Sequence::create(FadeIn::create(ACTION_TIME), CallFunc::create([&](){((Menu*)this->getChildByTag(BUTTON_TAG))->setEnabled(true); }), nullptr));

	node = this->getChildByTag(BUTTON_TAG)->getChildByTag(1);
	node->setOpacity(0);
	node->runAction(FadeIn::create(ACTION_TIME));

	node = nullptr;
	this->setVisible(true);
}

void SelectItemLayer::onExit(void)
{
	removeAllChildren();
	this->setTouchEnabled(false);
}

bool SelectItemLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point tou = touch->getLocation();
	if (_nowKind == NowSelect::Soilder)
	{
		if (((SelectItemCanditate*)this->getChildByTag(S_CANDITATE_TAG))->onTouchBegan(touch, event))
		{
			TOOL::SetHigData(_nowSelect, S_CANDITATE_TAG);
			return true;
		}
		
		if (((SelectItemCanditate*)this->getChildByTag(S_SELECTING_TAG))->onTouchBegan(touch, event))
		{
			TOOL::SetHigData(_nowSelect, S_SELECTING_TAG);
			return true;
		}
	}

	else if (_nowKind == NowSelect::Item)
	{
		if (((SelectItemCanditate*)this->getChildByTag(I_CANDITATE_TAG))->onTouchBegan(touch, event))
		{
			TOOL::SetHigData(_nowSelect, I_CANDITATE_TAG);
			return true;
		}

		if (((SelectItemCanditate*)this->getChildByTag(I_SELECTING_TAG))->onTouchBegan(touch, event))
		{
			TOOL::SetHigData(_nowSelect, I_SELECTING_TAG);
			return true;
		}
	}

	return false;
}

void SelectItemLayer::onTouchEnded(Touch* touch, Event* event)
{
	int index = _getTouchItem(touch);

	if (!index)
		TOOL::SetLowData(_nowSelect, index);
	else if (index != TOOL::GetLowData(_nowSelect))
		TOOL::SetLowData(_nowSelect, index);
	else
	{
		int d = 2;
		int SelectLayerIndex = TOOL::GetHigData(_nowSelect);
		if (SelectLayerIndex == S_CANDITATE_TAG || SelectLayerIndex == I_CANDITATE_TAG)
			d = 0;
		Sprite* node = nullptr;
		SelectItemCanditate* moveToLayer = nullptr;
		SelectItemCanditate* selectLayer = (SelectItemCanditate*)this->getChildByTag(SelectLayerIndex);
		if (_nowKind == Soilder)
		{
			node = _sList.at(TOOL::GetLowData(GET_INDEX(index)));
			moveToLayer = (SelectItemCanditate*)this->getChildByTag(S_SELECTING_TAG - d);
		}
		else if (_nowKind == Item)
		{
			node = _iList.at(TOOL::GetLowData(GET_INDEX(index)));
			moveToLayer = (SelectItemCanditate*)this->getChildByTag(I_SELECTING_TAG - d);
		}

		if (moveToLayer->isCountEnough())
		{
			selectLayer->removeChildKind(node);
			moveToLayer->addChildKind(node);
		}
		_nowSelect = 0;
	}
}

void SelectItemLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void SelectItemLayer::onTouchMoved(Touch* touch, Event* event)
{
	TOOL::SetLowData(_nowSelect, POINT_NOT_IN_SPRITE);
	((SelectItemCanditate*)this->getChildByTag(TOOL::GetHigData(_nowSelect)))->onTouchMoved(touch, event);
}

int SelectItemLayer::_getTouchItem(cocos2d::Touch* touch)
{
	int index = 0;
	if (_nowKind == Soilder)
	{
		for (auto child : _sList)
		if (child->getBoundingBox().containsPoint(child->getParent()->convertTouchToNodeSpace(touch)))
		{
			index = child->getTag();
			return SET_INDEX(index);
		}
	}

	else if (_nowKind == Item)
	{
		for (auto child : _iList)
		if (child->getBoundingBox().containsPoint(child->getParent()->convertTouchToNodeSpace(touch)))
		{
			index = child->getTag();
			return SET_INDEX(index);
		}
	}
	return POINT_NOT_IN_SPRITE;

}

void SelectItemLayer::_buttonReCallFun(Object* pSender)
{
	unsigned int UP_CANDITATE = 0;
	unsigned int UP_SELECTING = 0;
	unsigned int DOWN_CANDIATE = 0;
	unsigned int DOWN_SELECTING = 0;
	
	Point upSelectingMove = Point::ZERO;
	Point downSelectingMove = Point::ZERO;
	Size size = Director::getInstance()->getWinSize();

	if (_nowKind == Soilder)
	{
		UP_CANDITATE = I_CANDITATE_TAG;
		UP_SELECTING = I_SELECTING_TAG;
		DOWN_CANDIATE = S_CANDITATE_TAG;
		DOWN_SELECTING = S_SELECTING_TAG;
		upSelectingMove.setPoint(size.width, 0);
		downSelectingMove.setPoint(0, size.height);
		_nowKind = Item;
	}

	else if (_nowKind == Item)
	{
		UP_CANDITATE = S_CANDITATE_TAG;
		UP_SELECTING = S_SELECTING_TAG;
		DOWN_CANDIATE = I_CANDITATE_TAG;
		DOWN_SELECTING = I_SELECTING_TAG;
		upSelectingMove.setPoint(0, size.height);
		downSelectingMove.setPoint(size.width, 0);
		_nowKind = Soilder;
	}

	this->setTouchEnabled(false);
	((Menu*)this->getChildByTag(BUTTON_TAG))->setEnabled(false);
	this->getChildByTag(DOWN_CANDIATE)->runAction(MoveTo::create(ACTION_TIME, Point(0, -this->getChildByTag(DOWN_CANDIATE)->getContentSize().height)));
	this->getChildByTag(UP_CANDITATE)->runAction(Sequence::create(MoveTo::create(ACTION_TIME, Point::ZERO), CallFunc::create([&](){this->setTouchEnabled(true); ((Menu*)this->getChildByTag(BUTTON_TAG))->setEnabled(true); }), nullptr));
	this->getChildByTag(DOWN_SELECTING)->runAction(Spawn::createWithTwoActions(
		Sequence::create(MoveTo::create(ACTION_TIME / 2, downSelectingMove)
						, CallFunc::create([this, DOWN_SELECTING](){this->getChildByTag(DOWN_SELECTING)->setZOrder(UP_ZORDER); })
						, MoveTo::create(ACTION_TIME / 2, this->getChildByTag(DOWN_SELECTING)->getPosition())
						, nullptr)
		, Sequence::createWithTwoActions(FadeOut::create(ACTION_TIME / 2), FadeTo::create(ACTION_TIME / 2, 30))));

	this->getChildByTag(UP_SELECTING)->runAction(Spawn::createWithTwoActions(
		Sequence::create(MoveTo::create(ACTION_TIME / 2, upSelectingMove)
		, CallFunc::create([this, UP_SELECTING](){this->getChildByTag(UP_SELECTING)->setZOrder(DOWN_ZORDER); })
		, MoveTo::create(ACTION_TIME / 2, this->getChildByTag(UP_SELECTING)->getPosition())
		, nullptr)
		, Sequence::createWithTwoActions(FadeTo::create(ACTION_TIME / 2, 0), FadeTo::create(ACTION_TIME / 2, 255))));
}

void SelectItemLayer::_changeLayerToLast(void)
{
	this->setTouchEnabled(false);
	((Menu*)this->getChildByTag(BUTTON_TAG))->setEnabled(false);

	Node* node = nullptr;
	this->getParent()->addChild(SelectMapLayer::create());
	this->getParent()->removeChild(this);
}