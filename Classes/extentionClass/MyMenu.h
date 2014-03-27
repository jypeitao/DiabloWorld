#ifndef __Client__MyMenu__
#define __Client__MyMenu__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
class MyMenu:public cocos2d::CCMenu{
public:
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    bool moved;
    CREATE_FUNC(MyMenu);
};
#endif /* defined(__Client__MyMenu__) */
