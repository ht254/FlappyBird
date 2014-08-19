#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(MenuScene);

	static void startGame(Ref* sender);
	static void quitGame(Ref* sender);

};

#endif // __MENU_SCENE_H__
