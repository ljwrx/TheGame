#ifndef __PARTICALCIRCLE__
#define __PARTICALCIRCLE__

#include "cocos2d.h"

USING_NS_CC;

class ParticalCircle : public ParticleSystemQuad
{
public:
	~ParticalCircle();

	static ParticalCircle* create(Point from,Point direction,double damage,std::string textureImagePath = "");
	static ParticalCircle* createWithTotalParticles(int numberOfParticles,std::string textureImagePath = "");

	virtual bool init(std::string textureImagePath);
    virtual bool initWithTotalParticles(int numberOfParticles,std::string textureImagePath);
	
	float calcX;
	float realX;
	float realY;
	float realLength;
	float realDuration;
	double damage;

private:
	ParticalCircle();
};


#endif __PARTICALCIRCLE__