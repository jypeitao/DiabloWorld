//
//  CustomPop.h
//  wx
//
//  Created by guoyahui on 13-6-29.
//
//

#ifndef __wx__CustomPop__
#define __wx__CustomPop__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CustomPop:public CCLayerColor
{
public:
    
    static void show(const char* str);
    
private:
    CREATE_FUNC(CustomPop);
    virtual bool init();
    //    virtual void onExit();
    ~CustomPop();
    
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void close();
    
    bool istouch;
    
    CCMenu * btnsMenu;
    
    
    CCLabelTTF* desc;
};

#endif /* defined(__wx__CustomPop__) */
