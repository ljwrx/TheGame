
#include "BaseActionSprite.h"
#include "../System/VectorManager.h"
USING_NS_CC;

#define ACTION_COUNT		6

#define WALK_ACTION_TIME	0.1f
#define STAND_ACTION_TIME	0.1f
#define ATTACK_ACTION_TIME	0.1f
#define INJURE_ACTION_TIME	0.1f
#define INJURE_DELAY_TIME	0.5f
#define DEATH_ACTION_TIME	0.15f
#define DEATH_FADEOUT_TIME	0.45f
#define REMOVE_ACTION_TIME	0.1f
#define REMOVE_FADEOUT_TIME	0.3f

#define ASPD_FOR_DELAY_TIME	25.5f

BaseActionSprite::BaseActionSprite(void)
{
	_isMove = false;
}
BaseActionSprite::~BaseActionSprite(void)
{

}

BaseActionSprite* BaseActionSprite::createWithIndex(int index, int id, int spd, int aspd, int hp, Kind kind, VectorManager* manager)
{
	BaseActionSprite* sp = new BaseActionSprite();
	if (sp && sp->init(index, id, spd, aspd, hp, kind, manager))
		sp->autorelease();
	else
	{
		if (sp)
			delete sp;
		sp = nullptr;
	}
	return sp;
}

bool BaseActionSprite::init(int index, int id, int spd, int aspd, int hp, Kind kind, VectorManager* manager)
{
	if (!Sprite::init())
		return false;

	_nowHp = hp;
	_kind = kind;
	_manager = manager;
	_dataIndex = index;
	

	_actionList.reserve(ACTION_COUNT);

	auto sfCache =  SpriteFrameCache::getInstance();

	if (kind & Kind::Soldier)
		sfCache->addSpriteFramesWithFile(String::createWithFormat("res\\s\\%d.plist", index)->getCString());
	else if (kind & Kind::Enemy)
		sfCache->addSpriteFramesWithFile(String::createWithFormat("res\\e\\%d.plist", index)->getCString());

	cocos2d::Action* action = nullptr;

	//加载行走动画
	Vector<cocos2d::SpriteFrame*> walk;
	walk.pushBack(sfCache->getSpriteFrameByName("move1.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move2.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move3.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move4.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move5.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move6.png"));
	action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(walk, WALK_ACTION_TIME)));
	_actionList.pushBack(action);


	//加载站立动画
	Vector<cocos2d::SpriteFrame*> stand;
	stand.pushBack(sfCache->getSpriteFrameByName("stand1.png"));
	stand.pushBack(sfCache->getSpriteFrameByName("stand2.png"));
	action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(stand, STAND_ACTION_TIME)));
	_actionList.pushBack(action);

	//加载等待动画
//	Vector<cocos2d::SpriteFrame*> stand;
//	stand.pushBack(sfCache->getSpriteFrameByName("stand1.png"));
//	stand.pushBack(sfCache->getSpriteFrameByName("stand2.png"));
	action = Spawn::createWithTwoActions((RepeatForever*)action,
										Sequence::createWithTwoActions(DelayTime::create(ASPD_FOR_DELAY_TIME / aspd)
																	, CallFunc::create(std::bind(&BaseActionSprite::_waitActionRecall,this))));
	_actionList.pushBack(action);

	//加载攻击动画
	Vector<cocos2d::SpriteFrame*> attack;
	attack.pushBack(sfCache->getSpriteFrameByName("attack1.png"));
	attack.pushBack(sfCache->getSpriteFrameByName("attack2.png"));
	attack.pushBack(sfCache->getSpriteFrameByName("attack3.png"));
	attack.pushBack(sfCache->getSpriteFrameByName("attack4.png"));
	action = Sequence::createWithTwoActions(Animate::create(Animation::createWithSpriteFrames(attack, ATTACK_ACTION_TIME))
										, CallFunc::create(std::bind(&BaseActionSprite::_attackActionRecall, this)));
	_actionList.pushBack(action);

	//加载受击动画
	Vector<cocos2d::SpriteFrame*> injure;
	injure.pushBack(sfCache->getSpriteFrameByName("injure1.png"));
	injure.pushBack(sfCache->getSpriteFrameByName("injure2.png"));
	action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(injure, INJURE_ACTION_TIME))
							, DelayTime::create(INJURE_DELAY_TIME)
							, CallFunc::create(std::bind(&BaseActionSprite::_injureActionRecall, this))
							, nullptr);
	_actionList.pushBack(action);

	//加载死亡动画
	Vector<cocos2d::SpriteFrame*> death;
	death.pushBack(sfCache->getSpriteFrameByName("die1.png"));
	death.pushBack(sfCache->getSpriteFrameByName("die2.png"));
	death.pushBack(sfCache->getSpriteFrameByName("die3.png"));
	action = Sequence::createWithTwoActions(Spawn::createWithTwoActions(Animate::create(Animation::createWithSpriteFrames(death, DEATH_ACTION_TIME))
																		 ,FadeOut::create(DEATH_FADEOUT_TIME))
											,CallFunc::create(std::bind(&BaseActionSprite::_deathActionRecall, this)));
	_actionList.pushBack(action);

	//加载铲除动画
	if (kind == Soldier)
	{
		Vector<cocos2d::SpriteFrame*> remove;
		remove.pushBack(sfCache->getSpriteFrameByName("moveout1.png"));
		remove.pushBack(sfCache->getSpriteFrameByName("moveout2.png"));
		remove.pushBack(sfCache->getSpriteFrameByName("moveout3.png"));
		action = Sequence::createWithTwoActions(Spawn::createWithTwoActions(Animate::create(Animation::createWithSpriteFrames(remove, REMOVE_ACTION_TIME))
																			,FadeOut::create(REMOVE_FADEOUT_TIME))
												,CallFunc::create(std::bind(&BaseActionSprite::_removeActionRecall, this)));
		_actionList.pushBack(action);
	}

	sfCache->removeSpriteFramesFromFile("res\\i\\1.plist");
	return true;
}

void BaseActionSprite::setNowAction(BaseActionSpriteAction action)
{
	if (_nowAction == action || (_kind == Kind::Enemy && action == BaseActionSpriteAction::Remove))
		return;
	else
	{
		this->stopAllActions();
		this->runAction(_actionList.at(action));
		_nowAction = action;
	}
}

void BaseActionSprite::onExit(void)
{
	stopAllActions();

	_nowAction = Walk;

	while (!_actionList.empty())
		_actionList.popBack();

	Sprite::onExit();
}

///////////////////////////////////////////////////////////////////////////////////
////////////////	Recall Fun ////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void BaseActionSprite::_walkActionRecall(void)
{

}

void BaseActionSprite::_waitActionRecall(void)
{
	if (_isMove)
		setNowAction(BaseActionSpriteAction::Walk);
	else
		setNowAction(BaseActionSpriteAction::Stand);
	if (_manager)
		_manager->pushToWaitList(this);
}

void BaseActionSprite::_standActionRecall(void)
{

}

void BaseActionSprite::_deathActionRecall(void)
{
	removeFromParent();
}

void BaseActionSprite::_attackActionRecall(void)
{
	setNowAction(BaseActionSpriteAction::Wait);
	if (_manager)
		_manager->pushToAttackList(this);
}

void BaseActionSprite::_removeActionRecall(void)
{
	removeFromParent();
}

void BaseActionSprite::_injureActionRecall(void)
{
	if (_isMove)
		setNowAction(BaseActionSpriteAction::Walk);
	else
		setNowAction(BaseActionSpriteAction::Stand);
}