
#include "SelectMapScene.h"
#include "SelectMap\SelectMapLayer.h"
#include "SelectItem\SelectItemLayer.h"

#define BUTTON_N				"res\\SelectMapRec\\button.png"
#define BUTTON_H				"res\\SelectMapRec\\button.png"

#define LAYER_TAG				0
#define BUTTON_TAG				1

USING_NS_CC;

SelectMapScene::SelectMapScene()
{

}
SelectMapScene::~SelectMapScene()
{

}

bool SelectMapScene::init()
{
	if (!Scene::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	this->addChild(SelectMapLayer::create());

	return true;
}

void SelectMapScene::onEnter()
{
	Scene::onEnter();
	_nowSel = Map;
}

void SelectMapScene::_changeSel(void)
{
	if (_nowSel == Map)
	{
		_nowSel = Item;
	}
	else if (_nowSel == Item)
	{
		_nowSel = Map;
	}
}