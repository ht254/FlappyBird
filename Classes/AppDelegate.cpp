#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "MenuScene.h"
#include "Path.h"

USING_NS_CC;


bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();

    if(!glView) {
        glView = GLView::createWithRect("Flappy Bird", Rect(0, 0, 360, 640));
        director->setOpenGLView(glView);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    glView->setDesignResolutionSize(288, 512, ResolutionPolicy::NO_BORDER);

    srand(time(NULL));

    preloadSFX();

    // create a scene. it's an autorelease object
    auto scene = MenuScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::preloadSFX()
{
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

    audioEngine->preloadEffect(SFX_DIE);
    audioEngine->preloadEffect(SFX_HIT);
    audioEngine->preloadEffect(SFX_POINT);
    audioEngine->preloadEffect(SFX_SWOOSHING);
    audioEngine->preloadEffect(SFX_WING);

    audioEngine->setEffectsVolume(0.4f);
}

