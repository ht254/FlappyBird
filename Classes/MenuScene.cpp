#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "Path.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto bg = GameLayer::create();
    auto menu = MenuScene::create();

    scene->addChild(bg, 0);
    scene->addChild(menu, 1);

    return scene;
}

bool MenuScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    float midWidth = visibleSize.width / 2;

    auto bird = Bird::create();
    bird->setPosition(midWidth, visibleSize.height * 0.6);
    addChild(bird, 1);

    auto logo = Sprite::create(IMG_TITLE);
    logo->setPosition(midWidth, visibleSize.height * 0.8);
    addChild(logo, 2);

    auto startBtn = Sprite::create(IMG_START_BTN);
    auto startBtnPressed = Sprite::create(IMG_START_BTN_PRESSED);
    auto startMenuItem = MenuItemSprite::create(startBtn, startBtnPressed, nullptr, MenuScene::startGame);

    auto closeBtn = Sprite::create(IMG_CLOSE_BTN);
    auto closeBtnPressed = Sprite::create(IMG_CLOSE_BTN_PRESSED);
    auto closeMenuItem = MenuItemSprite::create(closeBtn, closeBtnPressed, nullptr, MenuScene::quitGame);

    auto menu = Menu::create(startMenuItem, closeMenuItem, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(midWidth, visibleSize.height * 0.4);
    addChild(menu, 5);

    return true;
}

void MenuScene::quitGame(Ref* sender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->end();
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

void MenuScene::startGame(Ref* sender)
{
    auto gameScene = GameScene::createScene();
    auto transition = TransitionFade::create(1.0f, gameScene, Color3B(0, 0, 0));
    Director::getInstance()->replaceScene(transition);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_SWOOSHING);
}
