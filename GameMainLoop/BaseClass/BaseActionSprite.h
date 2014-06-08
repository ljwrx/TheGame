
#include "cocos2d.h"

class BaseActionSprite : public cocos2d::Sprite
{
public:
	enum Action
	{
		Walk,
		Stand,
		Attack,
		Injure,
		Death,
		Remove
	};

	enum Kind
	{
		Soldier,
		Enemy
	};

public:
	BaseActionSprite(void);
	~BaseActionSprite(void);


	inline int getDataIndex(void){ return _dataIndex; }
	inline Action getNowAction(void){ return _nowAction; }
	void setNowAction(BaseActionSprite::Action action);

	bool init(void);
	CREATE_FUNC(BaseActionSprite);

	void onExit(void);

protected:
	char _dataIndex;
	Action _nowAction;
	cocos2d::Vector<cocos2d::Action*> _actionList;
};