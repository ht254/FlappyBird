#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

USING_NS_CC;

class Bird : public Sprite
{
public:

	bool init();
	CREATE_FUNC(Bird);

	void update(float dt);
	void flyUp();
	void fall();
	void die();

private:

	enum class State { Normal, FlyingUp, Falling };

	Action* normalAnimation;
	Action* flyAnimation;
	Action* fallAnimation;
	State state;
	Size visibleSize;
	float velocity;
	float gravity;

};

#endif // __BIRD_H__
