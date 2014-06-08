
#include "BaseActionSprite.h"

USING_NS_CC;

BaseActionSprite::BaseActionSprite(void)
{

}
BaseActionSprite::~BaseActionSprite(void)
{

}

bool BaseActionSprite::init(void)
{
	if (!Sprite::init())
		return false;

	_actionList.reserve(5);
	auto sfCache =  SpriteFrameCache::getInstance();
	sfCache->addSpriteFramesWithFile("res\\i\\1.plist");

	cocos2d::Action* action = nullptr;

	Vector<cocos2d::SpriteFrame*> walk;
	walk.pushBack(sfCache->getSpriteFrameByName("move1.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move2.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move3.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move4.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move5.png"));
	walk.pushBack(sfCache->getSpriteFrameByName("move6.png"));
	action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(walk, 0.1f)));
	_actionList.pushBack(action);

	Vector<cocos2d::SpriteFrame*> stand;
	stand.pushBack(sfCache->getSpriteFrameByName("stand1.png"));
	stand.pushBack(sfCache->getSpriteFrameByName("stand2.png"));
	action = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(stand, 0.1f)));
	_actionList.pushBack(action);

	Vector<cocos2d::SpriteFrame*> attack;
	attack.pushBack(sfCache->getSpriteFrameByName("attack1.png"));
	attack.pushBack(sfCache->getSpriteFrameByName("attack2.png"));
	attack.pushBack(sfCache->getSpriteFrameByName("attack3.png"));
	attack.pushBack(sfCache->getSpriteFrameByName("attack4.png"));
	action = Sequence::createWithTwoActions(Animate::create(Animation::createWithSpriteFrames(attack, 0.1f))
											, CallFunc::create([this](){this->setNowAction(BaseActionSprite::Action::Stand); }));
	_actionList.pushBack(action);


	Vector<cocos2d::SpriteFrame*> injure;
	injure.pushBack(sfCache->getSpriteFrameByName("injure1.png"));
	injure.pushBack(sfCache->getSpriteFrameByName("injure2.png"));
	action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(injure, 0.1f))
							, DelayTime::create(0.5f)
							, CallFunc::create([this](){this->setNowAction(BaseActionSprite::Action::Stand); })
							, nullptr);
	_actionList.pushBack(action);

	Vector<cocos2d::SpriteFrame*> death;
	death.pushBack(sfCache->getSpriteFrameByName("die1.png"));
	death.pushBack(sfCache->getSpriteFrameByName("die2.png"));
	death.pushBack(sfCache->getSpriteFrameByName("die3.png"));
	action = Sequence::createWithTwoActions(Spawn::createWithTwoActions(Animate::create(Animation::createWithSpriteFrames(death, 0.15f))
																		 ,FadeOut::create(0.45f))
											,CallFunc::create([this](){this->removeFromParent(); }));
	_actionList.pushBack(action);

	Vector<cocos2d::SpriteFrame*> remove;
	remove.pushBack(sfCache->getSpriteFrameByName("moveout1.png"));
	remove.pushBack(sfCache->getSpriteFrameByName("moveout2.png"));
	remove.pushBack(sfCache->getSpriteFrameByName("moveout3.png"));
	action = Sequence::createWithTwoActions(Spawn::createWithTwoActions(Animate::create(Animation::createWithSpriteFrames(remove, 0.1f))
											, FadeOut::create(0.3f))
											, CallFunc::create([this](){this->removeFromParent(); }));
	_actionList.pushBack(action);

	sfCache->removeSpriteFramesFromFile("res\\i\\1.plist");
	return true;
}

void BaseActionSprite::setNowAction(BaseActionSprite::Action action)
{
	if (_nowAction == action)
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