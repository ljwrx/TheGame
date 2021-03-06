
#ifndef __VECTOR__MANAGER__
#define __VECTOR__MANAGER__

#include "cocos2d.h"
#include "../BaseClass/BaseData.h"

class BaseActionSprite;
class ParticalSys;

class VectorManager : public cocos2d::Ref
{
public:
	VectorManager(void);
	~VectorManager(void);

	void setParicalSystem(ParticalSys* sys);

	void pushToWaitList(BaseActionSprite* bs);
	void pushToAttackList(BaseActionSprite* bs);

	BaseActionSprite* createCPUByIndex(int index);
	BaseActionSprite* createPlayerByIndex(int index);


	void updata(float dt);
	void onExit(void);

	bool init(int s_data, int i_data, int level);
	static VectorManager* createWithData(int s_data, int i_data, int level);

private:
	void _checkWaitList();
	void _checkAttackList();
	void _attackCheckAndHit(int attack, BaseActionSprite* attacker, Vector<BaseActionSprite*>*checkList);

private:
	ParticalSys* _particalSystem;

	cocos2d::Vector<BaseActionSprite*> _waitList;
	cocos2d::Vector<BaseActionSprite*> _attackList;

	cocos2d::Vector<cocos2d::Sprite*> _iList;
	cocos2d::Vector<BaseActionSprite*> _pList;
	cocos2d::Vector<BaseActionSprite*> _cList;

	std::vector<BaseData> _pDataList;
	std::vector<BaseData> _cDataList;

};


#endif