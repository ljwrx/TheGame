
#ifndef __SELECT__MAP__SCENE__
#define __SELECT__MAP__SCENE__

#include "cocos2d.h"

class SelectMapScene : public cocos2d::Scene
{
public:
	enum Select
	{
		Map = 1,
		Item = 2
	};

public:
	~SelectMapScene();

	virtual void onEnter();

	bool init();
	CREATE_FUNC(SelectMapScene);
private:
	SelectMapScene();

	void _changeSel(void);

private:
	Select _nowSel;
};
#endif