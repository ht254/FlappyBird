#ifndef __PIPE_H__
#define __PIPE_H__

#include "cocos2d.h"
#include "Bird.h"

USING_NS_CC;

class Pipe : public Node
{
public:

	bool init();
	CREATE_FUNC(Pipe);

	void setRandomPostionY();
	float getPositionX();
	void setPositionX(float x);
	bool checkCollision(Bird* bird);

private:
	Sprite* upPipe;
	Sprite* downPipe;

};


#endif // __PIPE_H__
