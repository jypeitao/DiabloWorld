//
//  LodingLayer.cpp
//  client1
//
#include "LodingLayer.h"
bool Loading::init(){
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))){
        return false;
    }
    setTouchEnabled(true);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading.plist");
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    ar=CCArray::create();
    //ar=CCArray::createWithCapacity(12);
    char str[64] = {0};
    for(int i = 1; i <=12; i++)
    {
        sprintf(str,"load%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName(str);
        ar->addObject(frame);

    }
    animation = CCAnimation::createWithSpriteFrames(ar, 0.1f);
    CCSprite *sp=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("load1.png"));
    sp->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(sp);
    CCActionInterval* action=CCAnimate::create(animation);
    go=CCRepeatForever::create(action);
    sp->runAction(go);
    go->retain();
    return true;
}
void Loading::registerWithTouchDispatcher()
{
    // NDK编译，需加上头 #include <limits>
    // 优先级数字设为最小，那么具有最高优先级，最后参数设为true，则触摸会被这里吞掉，下面的层不会接收到触摸事件
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    //CCLayer::registerWithTouchDispatcher();(std::numeric_limits<int>::min())
    CCLayer::registerWithTouchDispatcher();
}

bool Loading::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    // 因为回调调不到了，所以resume写在了这里
    CCLog("loading layer");
    return true;
}
void Loading::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
}
void Loading::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
}
Loading::~Loading()
{   
    go->release();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("loading.plist");
    //CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeTextureForKey("loading.png");

}
