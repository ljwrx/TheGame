
#ifndef __SELECT__ITEM__CANDITATE__
#define __SELECT__ITEM__CANDITATE__

#include "cocos2d.h"

class SelectItemCanditate : public cocos2d::Sprite
{
public:
	enum ItemKind
	{
		S_CANDITATE = 1,
		I_CANDITATE = 2,
		CANDITATE	= 3,

		S_SELECTING = 4,
		I_SELECTING = 8,
		SELECTING	= 12
	};

public:
	SelectItemCanditate();
	~SelectItemCanditate();

	//触摸

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	//构造器

	//候选栏构造器
	bool init(ItemKind kind, cocos2d::Vector<cocos2d::Sprite*>& list);
	static SelectItemCanditate* create(ItemKind kind, cocos2d::Vector<cocos2d::Sprite*>& list);

	//选择栏构造器
	bool init(ItemKind kind, unsigned selectingMap);
	static SelectItemCanditate* create(ItemKind kind, unsigned selectingMap);


	inline bool isCountEnough(void){ return _kind&CANDITATE ? true : _count; }
	void addChildKind(cocos2d::Node* node);
	void removeChildKind(cocos2d::Node* node);


private:
	inline bool _onTouchBeganForCanditate(cocos2d::Touch* touch, cocos2d::Event* event)
	{
		_lastTouch = touch->getLocation();
		return this->getBoundingBox().containsPoint(this->getParent()->convertTouchToNodeSpace(touch)); 
	}

	bool _onTouchBeganForSelecting(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	ItemKind _kind;
	unsigned int _count;
	cocos2d::Point _lastTouch;
};


#endif