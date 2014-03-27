
#ifndef __client1__next__
#define __client1__next__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <limits>
using namespace cocos2d;
using namespace CocosDenshion;
class next:public CCLayerColor{
public:
    virtual bool init();
    virtual void  registerWithTouchDispatcher();
   
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    CREATE_FUNC(next);
};
#endif /* defined(__client1__next__) */
