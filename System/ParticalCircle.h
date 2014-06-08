#ifndef __PARTICALCIRCLE__
#define __PARTICALCIRCLE__

#include "cocos2d.h"

USING_NS_CC;

class ParticalCircle : public ParticleSystemQuad
{
public:
	~ParticalCircle();

	static ParticalCircle* create();
	static ParticalCircle* createWithTotalParticles(int numberOfParticles);

	virtual bool init();
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
	ParticalCircle();
};


#endif __PARTICALCIRCLE__