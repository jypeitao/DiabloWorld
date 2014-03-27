
#ifndef __wx__friendemploylog__
#define __wx__friendemploylog__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class friendemploylog:public CCLayer
{
public:
    CREATE_FUNC(friendemploylog);
    
private:
    
    virtual bool init();
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    
    void rec_2309();
   
    
    CCScrollView* _scrollView;
    
    CCSize size;
    
    bool istouch;

};

#endif /* defined(__wx__friendemploylog__) */
