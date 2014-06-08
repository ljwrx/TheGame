#pragma once
#ifndef __Table__Scroll__
#define __Table__Scroll__

#include "cocos2d.h"
//#include "CocosGUI.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "cocos-ext.h"

USING_NS_CC;

class tableScroll :
	public LayerColor , public cocos2d::extension::TableViewDelegate , public cocos2d::extension::TableViewDataSource
{
public:
	~tableScroll();

	virtual bool init();
	//CREATE_FUNC(tableScroll);

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView *view);
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView *view);

	virtual void tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell);
	virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
	virtual cocos2d::extension::TableViewCell *tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idz);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);

	static tableScroll *create();
	virtual bool initWithDoc(rapidjson::Document *doc);

private:
	tableScroll();
	bool done;
};

#endif