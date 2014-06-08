
#ifndef __SELECT__MAP__LAYER__
#define __SELECT__MAP__LAYER__

#include "cocos2d.h"

class SelectMapLayer : public cocos2d::Layer
{
public:
	~SelectMapLayer();


	//´¥ÃþÏà¹Ø
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	void onEnter(void);

	bool init(void);
	static SelectMapLayer* create(void);

private: 
	SelectMapLayer(void);
	void _showSmlGear(void);
	void _hideSmlGear(void);
	void _setSmlGearVisible(cocos2d::Node*, void* flag);

	void _hideMapCover(void);
	void _showMapCover(void);
	void _hideLevelCover(void);
	void _showLevelCover(void);
	void _changeLayerToNext(void);

	inline void _lockHide(void){ _isHide = true; };
	inline void _unLockHide(void){ _isHide = false; };

private:
	bool _isHide;
	int _selectingGear;
	cocos2d::Point _lastTouch;
	std::string _levelData;
};

#endif