#include "MainScene.h"
#include "BaseClass\BaseActionSprite.h"

using namespace cocos2d;

MainScene::MainScene()
{
	_sp = nullptr;
}

MainScene::~MainScene()
{
}

bool MainScene::init(void)
{
	if (!Scene::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	auto walk = MenuItemImage::create("test\\walk.png","test\\walk.png",CC_CALLBACK_0(MainScene::_buttonRecall, this, BaseActionSprite::Action::Walk));
	walk->setPosition(size.width*0.9, size.height*0.9);

	auto stand = MenuItemImage::create("test\\stand.png", "test\\stand.png", CC_CALLBACK_0(MainScene::_buttonRecall, this, BaseActionSprite::Action::Stand));
	stand->setPosition(size.width*0.9, size.height*0.8);

	auto attack = MenuItemImage::create("test\\attack.png", "test\\attack.png", CC_CALLBACK_0(MainScene::_buttonRecall, this, BaseActionSprite::Action::Attack));
	attack->setPosition(size.width*0.9, size.height*0.7);

	auto injure = MenuItemImage::create("test\\injure.png", "test\\injure.png", CC_CALLBACK_0(MainScene::_buttonRecall, this, BaseActionSprite::Action::Injure));
	injure->setPosition(size.width*0.9, size.height*0.6);

	auto death = MenuItemImage::create("test\\death.png", "test\\death.png", CC_CALLBACK_0(MainScene::_buttonRecall, this, BaseActionSprite::Action::Death));
	death->setPosition(size.width*0.9, size.height*0.5);

	auto remove = MenuItemImage::create("test\\remove.png", "test\\remove.png", CC_CALLBACK_0(MainScene::_buttonRecall, this, BaseActionSprite::Action::Remove));
	remove->setPosition(size.width*0.9, size.height*0.4);


	auto menu = Menu::create(walk, stand, attack, injure, death, remove, nullptr);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	this->addChild(Layer::create(), 5, 10);

	return true;
}

void MainScene::_checkSPisCreate()
{
	if (_sp)
		return;
	else
	{
		Size size = Director::getInstance()->getWinSize();
		_sp = BaseActionSprite::create();
		_sp->setPosition(size.width*0.5, size.height*0.5);
		this->getChildByTag(10)->addChild(_sp);
	}
}

void MainScene::_buttonRecall(int flag)
{
	_checkSPisCreate();
	((BaseActionSprite*)_sp)->setNowAction((BaseActionSprite::Action)flag);
	if (flag == BaseActionSprite::Action::Death || flag == BaseActionSprite::Action::Remove)
		_sp = nullptr;
}