#include <fstream>
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "Path.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto game = GameScene::create();

	scene->addChild(game, 5);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	cheating = false;
	state = State::Tutorial;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	float midWidth = visibleSize.width / 2;

	layer = GameLayer::create();
	addChild(layer, 0);

	bird = Bird::create();
	bird->setPosition(Point(visibleSize.width * 0.36f, visibleSize.height * 0.6f));
	addChild(bird, 1);

	tutorialNode = Node::create();

	auto tutorial = Sprite::create(IMG_TUTORIAL);
	tutorial->setPosition(midWidth, visibleSize.height / 2);
	tutorialNode->addChild(tutorial);

	auto textReady = Sprite::create(IMG_TEXT_READY);
	textReady->setPosition(midWidth, visibleSize.height * 0.7);
	tutorialNode->addChild(textReady);

	addChild(tutorialNode, 5);

	scoreLabel = Label::createWithBMFont(FNT_FONT, "0", TextHAlignment::CENTER);
	scoreLabel->setAnchorPoint(Point(0.5f, 0.5f));
	scoreLabel->setPosition(midWidth, visibleSize.height * 0.9);
	addChild(scoreLabel, 5);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	schedule(schedule_selector(GameScene::update));

	return true;
}

void GameScene::startPlay()
{
	tutorialNode->setVisible(false);
	layer->addPipes();
	bird->fall();
	state = State::Playing;
}

void GameScene::update(float dt)
{
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	if (state == State::Playing) {
		bird->update(dt);
		layer->update(dt);
		if (!cheating && layer->checkCollision(bird)) {
			audioEngine->playEffect(SFX_HIT);
			layer->stop();
			bird->fall();
			state = State::Falling;
		} else if (layer->hitGround(bird)) {
			audioEngine->playEffect(SFX_DIE);
			layer->stop();
			bird->die();
			gameOver();
		}
		updateScore();
	} else if (state == State::Falling) {
		bird->update(dt);
		if (layer->hitGround(bird)) {
			audioEngine->playEffect(SFX_DIE);
			bird->die();
			gameOver();
		}
	}
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	auto pos = touch->getLocationInView();
	if (pos.x < 20 && pos.y < 20) {
		cheating = !cheating;
		return true;
	}
	if (state == State::Tutorial) {
		startPlay();
		audioEngine->playEffect(SFX_WING);
		bird->flyUp();
		return true;
	} else if (state == State::Playing) {
		audioEngine->playEffect(SFX_WING);
		bird->flyUp();
		return true;
	}
	return false;
}

void GameScene::updateScore()
{
	int score = layer->getScore();
	scoreLabel->setString(Value(score).asString());
}

void GameScene::gameOver()
{
	state = State::Gameover;

	scoreLabel->setVisible(false);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	float scrWidth = visibleSize.width;
	float scrHeight = visibleSize.height;
	float midWidth = scrWidth / 2;
	float midHeight = scrHeight / 2;

	auto gameover = Sprite::create(IMG_TEXT_GAME_OVER);
	gameover->setPosition(midWidth, scrHeight * 0.7);
	addChild(gameover, 4);

	auto panel = Sprite::create(IMG_SCORE_PANEL);
	panel->setPosition(midWidth, midHeight);
	addChild(panel, 4);

	int score = layer->getScore();
	auto finalScoreLabel = Label::createWithBMFont(FNT_SCORE, Value(score).asString());
	finalScoreLabel->setAnchorPoint(Point(1.0f, 1.0f));
	finalScoreLabel->setPosition(midWidth + 100, midHeight + 30);
	addChild(finalScoreLabel, 5);

	int record = readRecord();
	if (score > record) {
		record = score;
		writeRecord(record);
		auto newRecord = Sprite::create(IMG_NEW);
		newRecord->setPosition(midWidth + 34, midHeight - 4);
		addChild(newRecord, 5);
	}
	auto recordLabel = Label::createWithBMFont(FNT_SCORE, Value(record).asString());
	recordLabel->setAnchorPoint(Point(1.0f, 1.0f));
	recordLabel->setPosition(midWidth + 100, midHeight - 10);
	addChild(recordLabel, 5);

	if (score >= 10) {
		int idx = 0;
		static int scoreLevel[] = {20, 30, 40};
		while (idx < 3 && score >= scoreLevel[idx]) {
			++idx;
		}
		auto medal = Sprite::create(String::createWithFormat(IMAGES_DIR"medals_%d.png", idx)->getCString());
		medal->setPosition(scrWidth * 0.27f, scrHeight * 0.49f);
		addChild(medal, 5);
	}

	auto startBtn = Sprite::create(IMG_START_BTN);
	auto startBtnPressed = Sprite::create(IMG_START_BTN_PRESSED);
	auto startMenuItem = MenuItemSprite::create(startBtn, startBtnPressed, nullptr, MenuScene::startGame);

	auto closeBtn = Sprite::create(IMG_CLOSE_BTN);
	auto closeBtnPressed = Sprite::create(IMG_CLOSE_BTN_PRESSED);
	auto closeMenuItem = MenuItemSprite::create(closeBtn, closeBtnPressed, nullptr, MenuScene::quitGame);

	auto menu = Menu::create(startMenuItem, closeMenuItem, nullptr);
	menu->alignItemsHorizontally();
	menu->setPosition(midWidth, scrHeight * 0.3);
	addChild(menu, 4);

}

int GameScene::readRecord()
{
	return UserDefault::getInstance()->getIntegerForKey("score", 0);
}

void GameScene::writeRecord(int record)
{
	UserDefault::getInstance()->setIntegerForKey("score", record);
}

