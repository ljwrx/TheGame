#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ItemMoveSprite.h"
#include "CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "SpriteIntro.h"
#include "scrollView.h"
//#include "TopScrollView.h"
#include "ParticalSystem.h"

USING_NS_CC;

using namespace gui;

class HelloWorld : public cocos2d::LayerColor
{
public:
	enum UI_TAG
	{
		UI_SKILLBAR = 2,
		UI_CONTROLSLIDER,
		UI_EXITBUTTON
	};

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
	void onEnter(); 

    void startGameCallback(Object* pSender); 
    void aboutGameCallback(Object* pSender); 
    void exitGameCallback(Object* pSender); 
    void backGameCallback(Object* pSender); 

	void sceneChange(Object* pSender);

	void touchButton(Object *obj,TouchEventType evenType);

	void touchScroll(Object* pSender);

	void topScroll(Object* pSender);

	void particalsystem(Object* pSender);

	rapidjson::Document * getJsonAll(rapidjson::Document* doc,std::string filename);

	rapidjson::Value* getJsonOne(rapidjson::Value* v,rapidjson::Document* doc,int id);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	gui::Layout *m_layout;
	int id;
	std::string chinesename;
	std::string name;
	int health;
	int damage;
	float basemovetime;
	float skilldetail;

};

#endif // __HELLOWORLD_SCENE_H__
