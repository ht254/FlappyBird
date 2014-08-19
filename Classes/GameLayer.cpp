#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "Bird.h"
#include "Path.h"

USING_NS_CC;

GameLayer::GameLayer():
	speed(150),
	pipeDistance(180),
	pipeWidth(52),
	score(0),
	visibleSize(Director::getInstance()->getVisibleSize()),
	origin(Director::getInstance()->getVisibleOrigin()),
	pointX(visibleSize.width * 0.36f - 26)
{
}

bool GameLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto t = time(NULL);
	auto hour = localtime(&t)->tm_hour;
	bool isNight = hour <= 6 || hour >= 18;
	auto bg = Sprite::create(isNight ? IMG_BG_NIGHT : IMG_BG_DAY);
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg, 0);

	land = Sprite::create(IMG_LAND);
	land->setAnchorPoint(Point(0, 0));
	land->setPosition(0, 0);
	float moveDistance = land->getContentSize().width - visibleSize.width;
	float landMoveDuration = moveDistance / speed;
	auto landAnimation = RepeatForever::create(
		Sequence::create(
			MoveTo::create(landMoveDuration, Point(-moveDistance, 0)),
			MoveTo::create(0, Point(0, 0)),
			nullptr
		)
	);
	land->runAction(landAnimation);
	this->addChild(land, 3);

	return true;
}

void GameLayer::addPipes()
{
	for (int i = 0; i < 3; ++i) {
		auto pipe = Pipe::create();
		pipe->setPositionX(300 + visibleSize.width + pipeDistance * i);
		pipe->setRandomPostionY();
		this->addChild(pipe);
		pipes.push_back(pipe);
	}
}

void GameLayer::update(float dt)
{
	for (size_t i = 0; i < pipes.size(); ++i) {
		auto pipe = pipes[i];
		if (pipe->getPositionX() < -pipeWidth) {
			auto prePipe = pipes[i == 0 ? pipes.size() - 1 : i - 1];
			pipe->setPositionX(prePipe->getPositionX() + pipeDistance);
			pipe->setRandomPostionY();
		}
	}
	for (auto pipe : pipes) {
		float oldX = pipe->getPositionX();
		float x = oldX - dt * speed;
		if (x <= pointX && pointX < oldX ) {
			++score;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_POINT);
		}
		pipe->setPositionX(x);
	}
}

bool GameLayer::checkCollision(Bird* bird)
{
	for (auto pipe : pipes) {
		if (pipe->checkCollision(bird)) {
			return true;
		}
	}
	return false;
}

bool GameLayer::hitGround(Bird* bird)
{
	return bird->getBoundingBox().getMinY() + 20 < land->getContentSize().height;
}

void GameLayer::stop()
{
	land->stopAllActions();
}

int GameLayer::getScore()
{
	return score;
}

