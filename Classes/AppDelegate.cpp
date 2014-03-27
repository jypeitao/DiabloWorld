#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "LayerLogin.h"
#include "logo.h"
#include "SocketManager.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    Director *pDirector = Director::getInstance();
    
    pDirector->setOpenGLView(EGLView::getInstance());
    EGLView::getInstance()->setDesignResolutionSize(480, 800, ResolutionPolicy::SHOW_ALL);
    Director::getInstance()->setDepthTest(false);
    // turn on display FPS
//   pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    Scene *pScene = Scene::create();
    if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    {
        //pScene->addChild(LayerLogin::create());
    }
    else if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    {
        pScene->addChild(logo::create());
    }
    pScene->addChild(logo::create());
   // CCScene *pScene=HelloWorld::scene();
   // CCScene *pScene=xuanren::scene();
    // run 
    pDirector->runWithScene(pScene); 

    
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
