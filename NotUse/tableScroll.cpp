#include "tableScroll.h"

USING_NS_CC;
USING_NS_CC_EXT;

tableScroll* tableScroll::create(void)
{
	tableScroll *ts = new tableScroll();
	if (ts && ts->init())
	{
		ts->setTouchEnabled(true);
		ts->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ts);
	}

    return ts;
}

bool tableScroll::initWithDoc(rapidjson::Document *doc)
{
	return true;
}

bool tableScroll::init()
{
    if ( !LayerColor::initWithColor(ccc4(255,255,255,255)) )
    {
        return false;
    }
	Size visibSize = Director::sharedDirector()->getVisibleSize();
	TableView *tableView = TableView::create(this,CCSizeMake(visibSize.width,visibSize.height));
	tableView->setDirection(TableView::Direction::VERTICAL);
	tableView->setPosition(CCPointZero);
	tableView->setAnchorPoint(CCPointZero);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView,1);
	tableView->reloadData();

    return true;
}

void tableScroll::tableCellTouched(TableView *table, TableViewCell *cell)
{
	log("cell touched at index: %i", cell->getIdx());
}
	
Size tableScroll::cellSizeForTable(TableView *table)
{
	return CCSizeMake(60,60);
}

TableViewCell* tableScroll::tableCellAtIndex(TableView *table,ssize_t idx)
{
	log("%d",idx);
	TableViewCell *cell = table->dequeueCell();

	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
		Sprite *bgSprite = Sprite::create("CloseNormal.png");
		bgSprite->setAnchorPoint(CCPointZero);
		bgSprite->setPosition(CCPointZero);
		bgSprite->setTag(123);
		cell->addChild(bgSprite);

		LabelTTF *introLabel = LabelTTF::create("saber","Arial",30.0);
		introLabel->setPosition(ccp(30,50));
		introLabel->setTag(456);
		introLabel->setAnchorPoint(CCPointZero);
		cell->addChild(introLabel);
	}
	else
	{
		Texture2D *tx = TextureCache::getInstance()->addImage("saber.png");
		Sprite *sprite = (Sprite *)cell->getChildByTag(123);
		sprite->setTexture(tx);

		LabelTTF *label = (LabelTTF *)cell->getChildByTag(456);
		label->setString("saber");
	}
	return cell;
}

ssize_t tableScroll::numberOfCellsInTableView(TableView *table)
{
	return 20;
}

void tableScroll::scrollViewDidScroll(ScrollView *view)
{

}

void tableScroll::scrollViewDidZoom(ScrollView *view)
{

}

tableScroll::tableScroll()
{

}


tableScroll::~tableScroll()
{

}