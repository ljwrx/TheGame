
#include "SelectItemCanditate.h"
#include "UserData.h"
#include "TOOL.h"

#define MAP_DATA_PATH			"data\\MAP%d\\%d.txt"
#define ITEM_IMAGE_PATH			"res\\%c\\icon\\%d.png"
#define BANNER_IMAGE			"res\\SelectMapRec\\banner.png"
#define SELECTING_IMAGE_PATH	"res\\SelectMapRec\\selecting_box.png"
#define NO_SELECTING_IMAGE_PATH	"res\\SelectMapRec\\selecting_cannot.png"

#define PARTITION				"-"
#define S_CAN_SELECT_INDEX		0
#define I_CAN_SELECT_INDEX		1


#define ACTION_TIME				0.5f

#define CAN_SELECT_MAX			10
#define PER_IMAG_SIZE			100
#define CIRCLE_R				230.0f
#define PER_ROTATION			0.628f
#define DOUBLE_CIRCLE_R			78400


#define LAYER_TAG				0

USING_NS_CC;

SelectItemCanditate::SelectItemCanditate()
{
}

SelectItemCanditate::~SelectItemCanditate()
{
}


////////////////////////////////////////////////////////////////////////
//////////////////		构造器		////////////////////////////////////
////////////////////////////////////////////////////////////////////////

SelectItemCanditate* SelectItemCanditate::create(ItemKind kind, cocos2d::Vector<cocos2d::Sprite*>& list)
{
	SelectItemCanditate* pRet = new SelectItemCanditate();
	if (pRet && pRet->init(kind, list))
		pRet->autorelease();
	else
	{
		if (pRet)
			delete pRet;
		pRet = nullptr;
	}
	return pRet;
}


bool SelectItemCanditate::init(ItemKind kind, cocos2d::Vector<cocos2d::Sprite*>& list)
{
	if (!Sprite::initWithFile(BANNER_IMAGE))
		return false;

	_count = 0;
	char itemKind = '\0';
	unsigned int canditateKind = 0;
	
	if (kind == ItemKind::S_CANDITATE)
	{
		itemKind = 's';
		canditateKind = UserData::getInstance()->getSSelData();
	}
	else if (kind == ItemKind::I_CANDITATE)
	{
		itemKind = 'i';
		canditateKind = UserData::getInstance()->getISelData();
	}
	else
		return false;

	String str;
	Sprite* sp = nullptr;
	Layer* layer = Layer::create();

	for (int index = 1; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(canditateKind, index))
		{
			str.initWithFormat(ITEM_IMAGE_PATH, itemKind, index);
			sp = Sprite::create(str.getCString());
			if (!sp)
				return false;
			sp->setPosition(sp->getContentSize().width*(_count * 0.5f + _count + 0.5), (sp->getContentSize().height)*0.5);
			layer->addChild(sp, _count, _count);
			list.pushBack(sp);
			++_count;
		}
	}

	this->addChild(layer, LAYER_TAG, LAYER_TAG);

	_kind = kind;
	return true;
}

bool SelectItemCanditate::init(ItemKind kind, unsigned selectingMap)
{
	if (!Sprite::init())
		return false;

	unsigned int selectMax = 0;

	String file;
	file.initWithFormat(MAP_DATA_PATH, TOOL::GetHigData(selectingMap), TOOL::GetLowData(selectingMap));
	String str = FileUtils::getInstance()->getStringFromFile(file.getCString());

	if (kind == ItemKind::S_SELECTING)
		selectMax = ((String*)(str.componentsSeparatedByString(PARTITION)->objectAtIndex(S_CAN_SELECT_INDEX)))->intValue();

	else if (kind == ItemKind::I_SELECTING)
		selectMax = ((String*)(str.componentsSeparatedByString(PARTITION)->objectAtIndex(I_CAN_SELECT_INDEX)))->intValue();

	else
		return false;

	Sprite* sp = nullptr;
	float R = PER_IMAG_SIZE * selectMax / PI;
	float da = InRadians360 / selectMax;

	for (int index = 0; index < CAN_SELECT_MAX; ++index)
	{
		if (index < selectMax)
			sp = Sprite::create(SELECTING_IMAGE_PATH);

		else
			sp = Sprite::create(NO_SELECTING_IMAGE_PATH);
		sp->setPosition(CIRCLE_R*sin(PER_ROTATION*index), CIRCLE_R*cos(PER_ROTATION*index));
		this->addChild(sp, index, index);
	}
	this->setCascadeOpacityEnabled(true);
	_count = selectMax;
	_kind = kind;
	return true;
}

SelectItemCanditate* SelectItemCanditate::create(ItemKind kind, unsigned selectingMap)
{
	SelectItemCanditate* pRet = new SelectItemCanditate();
	if (pRet && pRet->init(kind, selectingMap))
		pRet->autorelease();
	else
	{
		if (pRet)
			delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

/////////////////////////////////////////////////////////////////////
//////////////////////		触摸分发		/////////////////////////
/////////////////////////////////////////////////////////////////////

bool SelectItemCanditate::_onTouchBeganForSelecting(Touch* touch, Event* event)
{
	Point tou = this->convertTouchToNodeSpaceAR(touch);
	return DOUBLE_CIRCLE_R >= (tou.x*tou.x + tou.y*tou.y);
}

bool SelectItemCanditate::onTouchBegan(Touch* touch, Event* event)
{
	Point tou = touch->getLocation();
	if (_kind & CANDITATE)
		return _onTouchBeganForCanditate(touch, event);
	else if (_kind & SELECTING)
		return _onTouchBeganForSelecting(touch, event);

	return false;
}

void SelectItemCanditate::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void SelectItemCanditate::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void SelectItemCanditate::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (_kind & CANDITATE)
	{
		int dx = touch->getLocation().x - _lastTouch.x;
		Layer* layer = (Layer*)this->getChildByTag(LAYER_TAG);
		layer->setPositionX(layer->getPositionX() + dx);
		_lastTouch = touch->getLocation();
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////////

void SelectItemCanditate::addChildKind(cocos2d::Node* node)
{
	if (_kind & CANDITATE)
	{
		Layer* layer = (Layer*)this->getChildByTag(LAYER_TAG);
		node->setPosition(node->getContentSize().width*(_count * 0.5f + _count + 0.5), (node->getContentSize().height)*0.5);
		layer->addChild(node, 99);
		++_count;
	}

	else if (_kind & SELECTING)
	{
		Point pos = this->getChildByTag(--_count)->getPosition();
		node->setPosition(pos);
		this->addChild(node, 99);
	}
}
void SelectItemCanditate::removeChildKind(cocos2d::Node* node)
{
	if (_kind & CANDITATE)
	{
		bool isDel = false;
		Point point = node->getPosition();
		Layer* layer = (Layer*)this->getChildByTag(LAYER_TAG);
		int index = layer->getChildren().getIndex(node);
		layer->removeChild(node);
		--_count;

		for (; index < _count; ++index)
		{
			layer->getChildren().at(index)->stopAllActions();
			layer->getChildren().at(index)->runAction(MoveTo::create(ACTION_TIME, point));
			point = layer->getChildren().at(index)->getPosition();
		}
	}

	else if (_kind & SELECTING)
	{
		++_count;
		Point point = node->getPosition();
		int index = this->getChildren().getIndex(node);
		this->removeChild(node, true);
		int Max = _children.size();
		for (; index < Max; ++index)
		{
			this->getChildren().at(index)->setPosition(point);
			point = this->getChildren().at(index)->getPosition();
		}
	}
}