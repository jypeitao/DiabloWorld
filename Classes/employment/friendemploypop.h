
#ifndef __wx__friendemploypop__
#define __wx__friendemploypop__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class FriendEmployPop:public CCLayerColor
{
public:
    
    static void show(const char* str);
    
private:
    CREATE_FUNC(FriendEmployPop);
    virtual bool init();
    //    virtual void onExit();
    ~FriendEmployPop();
    
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void close();
    
    bool istouch;
    
    CCMenu * btnsMenu;
    
    
    CCLabelTTF* desc;
};


#endif /* defined(__wx__friendemploypop__) */
