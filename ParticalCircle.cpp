#include "ParticalCircle.h"
#include "firePngData.h"
#include "platform/CCImage.h"
//#include "CCDirector.h"
//#include "CCTextureCache.h"

USING_NS_CC;

static Texture2D* getDefaultTexture()
{
    Texture2D* texture = nullptr;
    Image* image = nullptr;
    do 
    {
        bool ret = false;
        const std::string key = "/__firePngData";
        texture = Director::getInstance()->getTextureCache()->getTextureForKey(key);
        CC_BREAK_IF(texture != nullptr);

        image = new Image();
        CC_BREAK_IF(nullptr == image);
        ret = image->initWithImageData(__firePngData, sizeof(__firePngData));
        CC_BREAK_IF(!ret);

        texture = Director::getInstance()->getTextureCache()->addImage(image, key);
    } while (0);

    CC_SAFE_RELEASE(image);

    return texture;
}

ParticalCircle* ParticalCircle::create(Point from,Point direction,double damage,std::string textureImagePath)
{
    ParticalCircle* ret = new ParticalCircle();
	if (ret && ret->init(textureImagePath))
	{
		ret->realLength = 0;

		if (direction.y <= 0)
		{
			damage = -1;
			return nullptr;
		}

		if (direction.x >= 0)
		{
			ret->calcX = 384 + 22 - from.x;
		}else
		{
			ret->calcX = -22 - from.x;
		}

		if (ret->calcX*direction.y/direction.x < (512 - from.y))
		{
			ret->realX = ret->calcX + from.x;
			ret->realY = ret->calcX*direction.y/direction.x;
			ret->realLength = sqrt( (ret->realX * ret->realX) + (ret->realY * ret->realY) );
			ret->realDuration = ret->realLength / 500;
		}
		else {
			ret->realX = 192 + (512 - from.y)*direction.x/direction.y;
			ret->realY = 512;
			ret->realLength = sqrt( (ret->realX * ret->realX) + (ret->realY * ret->realY) );
			ret->realDuration = ret->realLength / 500;
		}
		ret->damage = damage;

		ret->autorelease();
	}
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

ParticalCircle* ParticalCircle::createWithTotalParticles(int numberOfParticles, std::string textureImagePath)
{
    ParticalCircle* ret = new ParticalCircle();
    if (ret && ret->initWithTotalParticles(numberOfParticles,textureImagePath))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool ParticalCircle::init(std::string textureImagePath)
{
	return initWithTotalParticles(50, textureImagePath);
}

bool ParticalCircle::initWithTotalParticles(int numberOfParticles, std::string textureImagePath)
{
    if( ParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // additive
        this->setBlendAdditive(true);

        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Point(0,0));

        // Gravity mode: radial acceleration
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity mode: speed of particles
        setSpeed(20);
        setSpeedVar(5);


        // angle
        _angle = 90;
        _angleVar = 360;

        // emitter position
        //Size winSize = Director::getInstance()->getWinSize();
        //this->setPosition(Point(winSize.width/2, winSize.height/2));

        //setPosVar(Point::ZERO);

		setPositionType(kCCPositionTypeRelative);
		setAutoRemoveOnFinish(true);

        // life of particles
        _life = 1;
        _lifeVar = 0.5f;

        // size, in pixels
        _startSize = 30.0f;
        _startSizeVar = 10.0f;
        _endSize = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per seconds
        _emissionRate = _totalParticles/_life;

        // color of particles
        _startColor.r = 0.76f;
        _startColor.g = 0.25f;
        _startColor.b = 0.12f;
        _startColor.a = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r = 0.0f;
        _endColor.g = 0.0f;
        _endColor.b = 0.0f;
        _endColor.a = 1.0f;
        _endColorVar.r = 0.0f;
        _endColorVar.g = 0.0f;
        _endColorVar.b = 0.0f;
        _endColorVar.a = 0.0f;

		if (textureImagePath == "")
		{
			Texture2D* texture = getDefaultTexture();
			if (texture != nullptr)
			{
				setTexture(texture);
			}
			return true;
		}

		setTexture(Director::getInstance()->getTextureCache()->addImage(textureImagePath));

        return true;
    }
    return false;
}

ParticalCircle::ParticalCircle()
{
}


ParticalCircle::~ParticalCircle()
{
}
