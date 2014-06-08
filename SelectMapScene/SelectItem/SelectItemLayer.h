
#ifndef __SELECT__ITEM__LAYER__
#define __SELECT__ITEM__LAYER__
#include "cocos2d.h"


class SelectItemLayer : public cocos2d::Layer
{
public:
	enum NowSelect
	{
		Soilder,
		Item
	};
public:
	SelectItemLayer();
	~SelectItemLayer();

	//´¥ÃþÏà¹Ø
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);


	bool init(void);
	bool initWithMapData(unsigned int data);
	static SelectItemLayer* createWithMapData(unsigned int data);
	CREATE_FUNC(SelectItemLayer);

	virtual void onEnter(void);
	virtual void onExit(void);

	void _buttonReCallFun(cocos2d::Object* pSender);
private:
	int _getTouchItem(cocos2d::Touch* touch);
	void _changeLayerToLast(void);
private:
	cocos2d::Vector<cocos2d::Sprite*> _sList;
	cocos2d::Vector<cocos2d::Sprite*> _iList;
	unsigned int _nowSelect;
	unsigned int _nowKind;
};

#endif
