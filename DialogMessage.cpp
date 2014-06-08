#include "DialogMessage.h"

USING_NS_CC;

#define DIALOGMESSAGE_WIDTH		210
#define DIALOGMESSAGE_HEIGHT	210

DialogMessage* DialogMessage::create(void)
{
	DialogMessage *si_Instant = new DialogMessage();
	if (si_Instant && si_Instant->init())
	{
		si_Instant->setTouchEnabled(false);
		si_Instant->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(si_Instant);
	}

    return si_Instant;
}

bool DialogMessage::initDialog(std::string spriteUrl, std::string spriteDetail)
{
	auto size = Director::sharedDirector()->getWinSize();

	Sprite *spritePic = Sprite::create(spriteUrl);
	this->addChild(spritePic,1);
	spritePic->setAnchorPoint(ccp(0.5,0.5));
	spritePic->setPosition(96,160);

	LabelTTF *spriteIntro = LabelTTF::create(spriteDetail,"Helvetica",10.0);
	this->addChild(spriteIntro,1);
	spriteIntro->setAnchorPoint(ccp(0.5,0.5));
	spriteIntro->setPosition(96,96);

	return true;
}

bool DialogMessage::init()
{
    if ( !LayerColor::initWithColor(ccc4(255,255,255,255),DIALOGMESSAGE_WIDTH,DIALOGMESSAGE_HEIGHT) )
    {
        return false;
    }
    return true;
}

DialogMessage::DialogMessage()
{

}


DialogMessage::~DialogMessage()
{

}
