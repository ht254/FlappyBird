#ifndef  __APP_DELEGATE_H__
#define  __APP_DELEGATE_H__

#include "cocos2d.h"

USING_NS_CC;

class AppDelegate : private Application
{
public:

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();

    void preloadSFX();

};

#endif // __APP_DELEGATE_H__

