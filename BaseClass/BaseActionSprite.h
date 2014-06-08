
#ifndef __BASE__ACTION__SPRITE__
#define __BASE__ACTION__SPRITE__

#include "cocos2d.h"
//#include "../System/VectorManager.h"

class VectorManager;

class BaseActionSprite : public cocos2d::Sprite
{
public:
	enum Action
	{
		Walk,
		Stand,
		Wait,
		Attack,
		Injure,
		Death,
		Remove,
		NONE = 0xffffffff
	};

	enum Kind
	{
		Fighter = 1,
		Range	= 2,
		Soldier	= 3,
		Enemy
	};

public:
	BaseActionSprite(void);
	~BaseActionSprite(void);

	inline void setNowHp(int nowHp){ _nowHp = nowHp; }
	void setNowAction(BaseActionSprite::Action action);

	inline int getNowHp(void){ return _nowHp; }
	inline Kind getKind(void){ return _kind; }
	inline int getDataIndex(void){ return _dataIndex; }
	inline Action getNowAction(void){ return _nowAction; }

	bool init(int index, int id, int spd, int aspd, int hp, Kind kind, VectorManager* manager);
	static BaseActionSprite* createWithIndex(int index, int id, int spd, int aspd, int hp, Kind kind, VectorManager* manager);

	void onExit(void);

protected:

	virtual void _walkActionRecall(void);
	virtual void _waitActionRecall(void);
	virtual void _standActionRecall(void);
	virtual void _deathActionRecall(void);
	virtual void _attackActionRecall(void);
	virtual void _removeActionRecall(void);
	virtual void _injureActionRecall(void);

protected:
	Kind _kind;
	char _nowHp;
	bool _isMove;
	char _dataIndex;
	Action _nowAction;
	VectorManager* _manager;
	cocos2d::Vector<cocos2d::Action*> _actionList;
};

typedef BaseActionSprite::Kind BaseActionSpriteKind;
typedef BaseActionSprite::Action BaseActionSpriteAction;

#endif