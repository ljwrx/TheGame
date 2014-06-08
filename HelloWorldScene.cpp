#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(ccc4(255,255,255,255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
	
	auto size = Director::getInstance()->getWinSize();

	//动态载入标题文字图片

	Sprite *startGameIconNormal = Sprite::create("StartGameNormal.png");
	Sprite *startGameIconSelected = Sprite::create("StartGameSelected.png");
	Sprite *optionIconNormal = Sprite::create("OptionNormal.png");
	Sprite *optionIconSelected = Sprite::create("OptionSelected.png");
	Sprite *exitGameIcon = Sprite::create("ExitGameNormal.png");
	Sprite *exitGameIconSelected = Sprite::create("ExitGameSelected.png");

	Sprite *title1 = Sprite::create("StartGameNormal.png");
	this->addChild(title1,1);
	Sprite *title2 = Sprite::create("StartGameNormal.png");
	this->addChild(title2,1);

	ItemMoveSprite *im = new ItemMoveSprite();
	im->titleMove(title1,Point(0,size.height),1.0,1.0,3.0,1,0);
	im->titleMove(title2,Point(size.width,size.height),0,1.0,3.0,-1,0);

	MenuItemSprite *Start = MenuItemSprite::create(startGameIconNormal,startGameIconSelected,(Object*)this,menu_selector(HelloWorld::touchScroll));
	im->menuIconMove(Start,Point(0,size.height*2/3),Point(size.width/2,size.height*2/3),1.5,0);
	MenuItemSprite *Option = MenuItemSprite::create(optionIconNormal,optionIconSelected,(Object*)this,menu_selector(HelloWorld::particalsystem));
	im->menuIconMove(Option,Point(size.width,size.height/2),Point(size.width/2,size.height/2),1.5,0);
	MenuItemSprite *Exit = MenuItemSprite::create(exitGameIcon,exitGameIconSelected,(Object*)this,menu_selector(HelloWorld::touchScroll));
	im->menuIconMove(Exit,Point(size.width/2,0),Point(size.width/2,size.height/3),1.5,0);

	Menu *pStartMenu = Menu::create(Start,Option,Exit,nullptr);
	pStartMenu->setPosition(Point::ZERO);
	this->addChild(pStartMenu,1);
	//this->addChild(start,3);
	im->autorelease();

	//添加背景 
    auto sprite = Sprite::create("HelloWorld.png"); 
    addChild(sprite, 0); 
    sprite->setPosition(Point(size.width / 2, size.height / 2)); 
    
	return true;
} 

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::particalsystem(Object* pSender)
{
	auto size = Director::getInstance()->getWinSize();
	Scene *thirdScene = Scene::create();
	Layer *thirdLayer = Layer::create();
	ParticalSys *ps = ParticalSys::create();
	Sprite *pyc = ps->particalFire(2,Point(size.width/2,size.height/8),Point(0.2,0.7),30);
	thirdLayer->addChild(ps,1);

	MenuItemImage *hit = MenuItemImage::create("left-round.png","right-round.png", CC_CALLBACK_1(ParticalSys::particalHit,ps,2,pyc));
	hit->setPosition(Point(size.width/2,size.height/2));
	MenuItemImage *restart = MenuItemImage::create("left-round.png","right-round.png", CC_CALLBACK_1(ParticalSys::particalHit,ps,3,pyc));
	restart->setPosition(Point(size.width/2,size.height/3));
	Menu *pStartMenu = Menu::create(hit,restart,nullptr);
	pStartMenu->setPosition(Point::ZERO);
	thirdLayer->addChild(pStartMenu,1);

	thirdScene->addChild(thirdLayer,1);
	Director::getInstance()->replaceScene(thirdScene);
}

//void HelloWorld::topScroll(Object* pSender)
//{
//	Scene *thirdScene = Scene::create();
//	TopScrollView *tsv = TopScrollView::create();
//	thirdScene->addChild(tsv,1);
//	tsv->setAnchorPoint(CCPointZero);
//	tsv->setPosition(Point(-384,404));
//	Director::sharedDirector()->replaceScene(thirdScene);
//}

void HelloWorld::touchScroll(Object* pSender)
{
	Scene *scrollScene = Scene::create();
	scrollView *sv = scrollView::create();
	scrollScene->addChild(sv,1);
	sv->setPosition(Point(-384,-1024));
	//TransitionFadeTR::create(2,scrollScene)
	Director::getInstance()->replaceScene(scrollScene);
}

void HelloWorld::sceneChange(Object* pSender)
{
	Scene *secondScene = Scene::create();
	Layer *secondLayer = Layer::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	rapidjson::Document* doc = new rapidjson::Document();
	doc = HelloWorld::getJsonAll(doc,"ownsprite_json.json");

	//SpriteIntro *si = SpriteIntro::create();
	//si->initWithDoc(doc);
	//secondLayer->addChild(si);

	//tableScroll *ts = tableScroll::create();
	//secondScene->addChild(ts,1);
//////////////////////////////////////////////////////////////////////////////DialogMessage
	//DialogMessage *dm = DialogMessage::create();
	//dm->initDialog("saber.png","saber");
	//secondScene->addChild(dm,1);
	//dm->setPosition(visibleSize.width/4,visibleSize.height/4);
	//dm->setScale(0.01);
	//FiniteTimeAction *action1 = ScaleBy::create(2, 100);
	//FiniteTimeAction *action2 = RotateBy::create(2,360);
	//dm->runAction(Spawn::createWithTwoActions(action1,action2));
//////////////////////////////////////////////////////////////////////////////
	//rapidjson::Value* v = new rapidjson::Value;
	//int p = 1;
	//v = HelloWorld::getJsonOne(v,doc,p);
	////rapidjson::Value* v = HelloWorld::getJsonAll(doc,"ownsprite_json.json");
	//name = (*v)[2].GetString();
	//std::string rs = "ownimage/"+name+".png";


	//m_layout = dynamic_cast<Layout *>(cocostudio::GUIReader::shareReader()->widgetFromJsonFile("D:/CCxGame/Resources/ChangeUI/ChangeUI.ExportJson"));

	//secondScene->addChild(m_layout,1);

	//MenuItemImage *normalpic = MenuItemImage::create(rs,NULL,NULL,(Object *)this,menu_selector(HelloWorld::sceneChange));

	//Button *exitbutton = dynamic_cast<Button *>(m_layout->getChildByTag(UI_EXITBUTTON));
	//exitbutton->addTouchEventListener(this,toucheventselector(HelloWorld::touchButton));


	//DialogMessage *dMsg = DialogMessage::sharedDialogMessage();
	//secondLayer->addChild(dMsg);

	//secondScene->addChild(secondLayer,1);

	Director::sharedDirector()->replaceScene(TransitionFadeTR::create(2,secondScene));
	delete doc;
	//delete v;
}
 
void HelloWorld::touchButton(Object *obj,TouchEventType evenType)
{
	auto button = dynamic_cast<Button *>(obj);
	int tag = button->getTag();
	switch (evenType)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
		if (tag == UI_EXITBUTTON)
		{
			Director::sharedDirector()->end();
			exit(0);
		}
	default:
		break;
	}
}

rapidjson::Document* HelloWorld::getJsonAll(rapidjson::Document* doc,std::string filename)
{
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		log("json file is not exit [%s]",filename);
		return nullptr;
	}
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc->Parse<rapidjson::kParseDefaultFlags>(data.c_str());

	if (doc->HasParseError() || !doc->IsArray())
	{
		log("get json data err!");
		return nullptr;
	}

	return doc;
}

rapidjson::Value* HelloWorld::getJsonOne(rapidjson::Value* v,rapidjson::Document* doc,int id)
{
	
	for(unsigned int i=1;i<doc->Size();i++)
    {
        (*v)=(*doc)[i];

        int vid;//ID
  
		//按下标提取  
        int a=0;  
        vid=(*v)[a++].GetInt();
		if (vid == id)
		{
			break;
		}
    }

    return v;
}

//rapidjson::Value* HelloWorld::getJsonAll(rapidjson::Document* doc,std::string filename)
//{
//	if (!FileUtils::getInstance()->isFileExist(filename))
//	{
//		log("json file is not exit [%s]",filename);
//		return nullptr;
//	}
//	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
//	doc->Parse<rapidjson::kParseDefaultFlags>(data.c_str());
//
//	if (doc->HasParseError() || !doc->IsArray())
//	{
//		log("get json data err!");
//		return nullptr;
//	}
//	rapidjson::Value* v = new rapidjson::Value;
//	for(unsigned int i=1;i<doc->Size();i++)
//    {
//        (*v)=(*doc)[i];
//
//        int id;//ID
//  
//		//按下标提取  
//        int a=0;  
//        id=(*v)[a++].GetInt();
//		if (id == 1)
//		{
//			break;
//		}
//    }
//
//    return v;
//}

void HelloWorld::aboutGameCallback(Object* pSender) 
{ 
    Size size = Director::sharedDirector()->getWinSize(); 
 
    //显示关于的内容 
    LabelTTF* label = LabelTTF::create("Made by LJW", "Arial", 30); 
    label->setPosition(Point(size.width / 2, size.height / 2)); 
    Scene* s = Scene::create(); 
    Layer* layer = Layer::create(); 
    layer->addChild(label, 1); 
 
    //返回按钮 
    LabelTTF* pBackLabel = LabelTTF::create("Back", "Arial", 30);
    MenuItemLabel* pBackItem = MenuItemLabel::create(pBackLabel, this, menu_selector(HelloWorld::backGameCallback)); 
    Menu* pBackMenu = Menu::create(pBackItem, NULL); 
    pBackItem->setPosition(Point(size.width  - 50, 50)); 
    pBackMenu->setPosition(CCPointZero); 
    layer->addChild(pBackMenu, 1); 
 
    s->addChild(layer); 
 
    Director::sharedDirector()->replaceScene(s); 
    //s->release(); 
    //layer->release(); 
 
} 
 
void HelloWorld::startGameCallback(Object* pSender) 
{ 
    //跳转到游戏中 
	Scene* scene = Scene::create(); 
    Layer* layer = new HelloWorld(); 
    scene->addChild(layer); 
    Director::sharedDirector()->replaceScene(scene); 
    scene->release(); 
    layer->release(); 
} 
 
 
void HelloWorld::exitGameCallback(Object* pSender) 
{ 
    Director::sharedDirector()->end(); 
} 
 
void HelloWorld::backGameCallback(Object* pSender) 
{ 
    Size size= Director::sharedDirector()->getWinSize(); 
    //跳转到游戏中 
    Scene* scene = Scene::create(); 
    Layer* layer = new HelloWorld(); 
    scene->addChild(layer); 
    Director::sharedDirector()->replaceScene(scene); 
    scene->release(); 
    layer->release(); 

} 
 
void HelloWorld::onEnter() 
{ 
    Layer::onEnter(); 
} 