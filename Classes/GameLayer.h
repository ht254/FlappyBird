#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "Bird.h"
#include "Pipe.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:

	GameLayer();
	virtual bool init();

	void addPipes();
	void update(float dt);
	bool checkCollision(Bird* bird);
	bool hitGround(Bird* bird);
	void stop();
	int getScore();

	CREATE_FUNC(GameLayer);

private:
	float speed;
	float pipeDistance;
	float pipeWidth;
	int score;
	Size visibleSize;
	Point origin;
	float pointX;
	Sprite* land;
	std::vector<Pipe*> pipes;
};

#endif // __GAME_LAYER_H__
