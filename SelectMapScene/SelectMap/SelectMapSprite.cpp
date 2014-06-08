#include "SelectMapSprite.h"
#include "UserData.h"
#include "Tool.h"

USING_NS_CC;

#define BIG_GEAR_IMAGE_NAME			"res\\SelectMapRec\\big_gear.png"
#define SML_GEAR_IMAGE_NAME			"res\\SelectMapRec\\sml_gear.png"

#define BIG_MAP_IMAGE_NAME_FORMAT	"res\\SelectMapRec\\Map\\%d.png"
#define SML_MAP_IMAGE_NAME_FORMAT	"res\\SelectMapRec\\Map-%d\\%d.png"

#define Deviation					10.0f
#define RotateSPD					0.5f

GearSprite::GearSprite()
{

}
GearSprite::~GearSprite()
{

}


////////////////////////////////////////////////////////////////
//////////////////		构造器		////////////////////////////
////////////////////////////////////////////////////////////////

bool GearSprite::initWithKind(void)
{
	String str;
	int count = 0;
	Sprite* temp = nullptr;
	unsigned int data = UserData::getInstance()->getMapData();

	for (int index = 1; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(data, index))
		{
			++count;
			str.initWithFormat(BIG_MAP_IMAGE_NAME_FORMAT, index);
			if (!(temp = Sprite::create(str.getCString())))
				return false;
			this->addChild(temp, count, count);
		}
	}
	resetChildPosition();
	return true;
}

bool GearSprite::initWithKind(unsigned int mapIndex)
{
	String str;
	int count = 0;
	Sprite* temp = nullptr;
	this->removeAllChildren();
	this->setRotation(0);
	unsigned int data = UserData::getInstance()->getLevelDataFromMapIndex(mapIndex);

	for (int index = 1; index <= 32; ++index)
	{
		if (TOOL::GetBinNum(data, index))
		{
			++count;
			str.initWithFormat(SML_MAP_IMAGE_NAME_FORMAT, mapIndex, index);
			if (!(temp = Sprite::create(str.getCString())))
				return false;
			this->addChild(temp, count, count);
		}
	}
	resetChildPosition();
	return true;
}

bool GearSprite::initWithKind(GearKind kind)
{
	tag = kind;
	switch (kind)
	{
	case BIG_GEAR:
		if (!Sprite::initWithFile(BIG_GEAR_IMAGE_NAME))
			return false;
		initWithKind();
		break;
	case SML_GEAR:
		if (!Sprite::initWithFile(SML_GEAR_IMAGE_NAME))
			return false;
		break;
	default:
		return false;
	}
	this->setCascadeOpacityEnabled(true);
	return true;
}

GearSprite* GearSprite::createWithKind(GearKind kind)
{
	GearSprite* p = new GearSprite();
	if (p && p->initWithKind(kind))
		p->autorelease();

	else
	{
		if (p)
			delete p;
		p = nullptr;
	}
	return p;
}


//////////////////////////////////////////////////////////////////////////////
/////////////////////////	触摸相关		//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

bool GearSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Point loc = this->convertToNodeSpaceAR(touch->getLocation());
	float Rr = this->getContentSize().width / 2 + Deviation;
	if (loc.x*loc.x + loc.y*loc.y <= Rr*Rr)
	{
		_stopAllActions();

		float lastRotation = this->getRotation();
		this->setRotation(0);
		_lastRotation = _getTouchRotation(touch);
		this->setRotation(lastRotation);

		return true;
	}
	return false;
}
void GearSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (this->getChildrenCount())
	{
		float da = InAngle360 / this->getChildrenCount(); //平均角度
		int index = this->getSelectingMapIndex();
		float deltaAngle = 0;
		
		if (this->getRotation() >= 0)
		{
			if (index == 0)
				deltaAngle = 0;
			else 
				deltaAngle = da*index;
		}
		else
		{
			if (index == 0)
				deltaAngle = 0;
			else
				deltaAngle = -da*index;
		}
		this->runAction(RotateTo::create(RotateSPD, deltaAngle));
		for (auto& child : _children)
			child->runAction(RotateTo::create(RotateSPD, -deltaAngle));
	}
}
void GearSprite::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}
void GearSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	float lastRotation = this->getRotation();
	this->setRotation(0);

	float touchRotation = _getTouchRotation(touch);
	float deltaRotation = touchRotation - _lastRotation;

	lastRotation += deltaRotation;
	if (lastRotation > InAngle360)
		lastRotation -= InAngle360;
	else if (lastRotation < -InAngle360)
		lastRotation += InAngle360;
	this->setRotation(lastRotation);

	lastRotation = -lastRotation;
	for (auto child : _children)
		child->setRotation(lastRotation);
	_lastRotation = touchRotation;

}

//////////////////////////////////////////////////////////////////////////////////
////////////////////	其他函数		//////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int GearSprite::getSelectingMapIndex(void)
{
	float nowRotation = this->getRotation();
	int index = abs(floorf(nowRotation / InAngle360 * this->getChildrenCount() + 0.5));
	return  index < this->getChildrenCount() ? index : index - this->getChildrenCount();
}

void GearSprite::resetChildPosition(void)
{
	int count = 0;
	Point pos = Point::ZERO;
	float R = this->getContentSize().width / 2;
	float da = InRadians360 / this->getChildrenCount(); //平均角度
	float dx = this->getContentSize().width / 2;
	float dy = this->getContentSize().height / 2;
	int flag = 0;
	switch (tag)
	{
	case BIG_GEAR:
		flag = 0;
		break;
	case SML_GEAR:
		flag = 1;
		break;
	default:
		break;
	}
	for (auto child : _children)
	{
		child->setPositionX(R*cos(flag*PI + da * count) + dx);
		child->setPositionY(R*sin(flag*PI + da * count) + dy);
		++count;
	}
}


void GearSprite::_stopAllActions(void)
{
	this->stopAllActions();
	for (auto child : _children)
		child->stopAllActions();
}

float GearSprite::_getTouchRotation(Touch* touch)
{
	Point touchPoint = this->convertTouchToNodeSpaceAR(touch);

	if (touchPoint.x == 0 && touchPoint.y == 0)
		return _lastRotation;
	else
		return -atan2f(touchPoint.y, touchPoint.x) / PI*InAngleHalf360;
}