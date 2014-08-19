#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : public Layer
{
public:

	static Scene* createScene();
	bool init();
	CREATE_FUNC(GameScene);

	void startPlay();
	void gameOver();

	void update(float dt);
	void updateScore();

	int readRecord();
	void writeRecord(int record);

	bool onTouchBegan(Touch* touch, Event* event);

private:

	enum class State { Tutorial, Playing, Falling, Gameover };

	bool cheating;
	State state;
	Label* scoreLabel;
	Node* tutorialNode;
	GameLayer* layer;
	Bird* bird;

};

#endif // __GAME_SCENE_H__
