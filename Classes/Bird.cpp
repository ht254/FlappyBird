#include "SimpleAudioEngine.h"
#include "Bird.h"
#include "Path.h"

USING_NS_CC;

bool Bird::init()
{
	if (!Sprite::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	velocity = 0.0f;
	gravity = 18.0f;
	state= State::Normal;

	// this->setAnchorPoint(Point(0.5f, 1.0f));

	auto animation = Animation::create();
	int which = rand() % 3;
	for (int i = 0; i < 3; ++i) {
		auto imageName = String::createWithFormat(IMAGES_DIR "bird%d_%d.png", which, i);  
		animation->addSpriteFrameWithFile(imageName->getCString()); 
	}

	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);

	normalAnimation = Animate::create(animation);  
	runAction(normalAnimation);

	// fallAnimation = EaseOut::create(RotateTo::create(0.6f, 90.0f), 0.4f);
	fallAnimation = RotateTo::create(0.6f, 90.0f);
	fallAnimation->retain();

	flyAnimation = Sequence::create(
		EaseOut::create(RotateTo::create(0.15f, 0), 0.4f),
		EaseIn::create(RotateTo::create(0.25f, -30), 0.4f),
		// RotateTo::create(0.15f, 0),
		// RotateTo::create(0.25f, -30),
		nullptr
	);
	flyAnimation->retain();

	return true;
}

void Bird::update(float dt)
{
	float y = this->getPositionY() - velocity * dt;
	if (y > visibleSize.height) {
		y = visibleSize.height;
	}
	this->setPositionY(y);
	if (velocity < 0 && velocity + gravity >= 0) {
		this->fall();
	}
	velocity += gravity;
}

void Bird::flyUp()
{
	velocity = -360.0f;
	if (state != State::FlyingUp) {
		if (state == State::Falling) {
			this->stopAction(fallAnimation);
		}
		this->runAction(flyAnimation);
		state = State::FlyingUp;
	}
}

void Bird::fall()
{
	if (state == State::FlyingUp) {
		this->stopAction(flyAnimation);
		this->runAction(fallAnimation);
		state = State::Falling;
	}
}

void Bird::die()
{
	this->stopAllActions();
}


