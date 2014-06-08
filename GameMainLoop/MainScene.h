
#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
	~MainScene();


	bool init(void);
	CREATE_FUNC(MainScene);
private:
	MainScene();

	void _checkSPisCreate();

	void _buttonRecall(int flag);

private:
	cocos2d::Sprite* _sp;
};
