#include "Pipe.h"
#include "Path.h"

bool Pipe::init()
{
    if (!Node::init()) {
        return false;
    }

    downPipe = Sprite::create(IMG_PIPE_DOWN);
    downPipe->setAnchorPoint(Point(0, 0));
    addChild(downPipe);

    upPipe = Sprite::create(IMG_PIPE_UP);
    upPipe->setAnchorPoint(Point(0, 1));
    addChild(upPipe);

    return true;
}

void Pipe::setRandomPostionY()
{
    float gap = 100;
    float mid = 112 + 200 + CCRANDOM_MINUS1_1() * gap;
    downPipe->setPositionY(mid + gap / 2);
    upPipe->setPositionY(mid - gap / 2);
}

float Pipe::getPositionX()
{
    return upPipe->getPositionX();
}

void Pipe::setPositionX(float x)
{
    downPipe->setPositionX(x);
    upPipe->setPositionX(x);
}

bool Pipe::checkCollision(Bird* bird)
{
    auto birdPos = bird->getPosition();
    if (upPipe->getPositionX() < birdPos.x
            && birdPos.x < upPipe->getPositionX() + upPipe->getContentSize().width) {
        if (birdPos.y > downPipe->getPositionY() || birdPos.y < upPipe->getPositionY()) {
            return true;
        }
    }
    return false;
}
