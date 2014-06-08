#include "SpriteIntro.h"

USING_NS_CC;
USING_NS_CC_EXT;

//创建单例，要使用这个类，必须使用这个接口获得实例对象
SpriteIntro* SpriteIntro::create(void)
{
	SpriteIntro *si_Instant = new SpriteIntro();
	if (si_Instant && si_Instant->init())
	{
		si_Instant->setTouchEnabled(true);
		si_Instant->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(si_Instant);
	}

    return si_Instant;
}

bool SpriteIntro::initWithDoc(rapidjson::Document *doc)
{
	auto size = cocos2d::Director::sharedDirector()->getWinSize();
	rapidjson::Value* v = new rapidjson::Value;
	std::string name;
	std::string picurl;

	ScrollView *scrollView = ScrollView::create();
	Layer *layer = Layer::create();
	Sprite *sprite;
	for (unsigned int i = 1; i < doc->Size(); i++)
	{
		(*v)=(*doc)[i];
		name = (*v)[2].GetString();
		picurl = "ownimage/"+name+".png";
		sprite = Sprite::create(picurl.c_str());
		sprite->setScaleX(2.0);
		sprite->setScaleY(1.0);
		layer->addChild(sprite,1,i);
		sprite->setPosition(32+(i-1)%4*120,1536-((i-1)/4+1)*152);
	}
	layer->setAnchorPoint(CCPointZero);
	layer->setPosition(CCPointZero);

	scrollView->setPosition(CCPointZero);
	scrollView->setContentOffset(CCPointZero);
	layer->setContentSize(CCSizeMake(384,512*3));
	scrollView->setContentSize(CCSizeMake(384,512));
	scrollView->setContainer(layer);
	scrollView->setTouchEnabled(true);
	scrollView->setDelegate(this);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	this->addChild(scrollView);

	delete v;
	return true;
}

bool SpriteIntro::init()
{
    if ( !LayerColor::initWithColor(ccc4(255,255,255,255)) )
    {
        return false;
    }
    return true;
}

SpriteIntro::SpriteIntro()
{

}


SpriteIntro::~SpriteIntro()
{

}

void SpriteIntro::scrollViewDidScroll(ScrollView *view)
{

}

void SpriteIntro::scrollViewDidZoom(ScrollView *view)
{

}