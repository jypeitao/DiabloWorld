
#ifndef __wx__MailWrite__
#define __wx__MailWrite__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MailInfo.h"

#include "LodingLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MailWrite:public CCLayerColor
{
public:
    
    static void show();
    
private:
    CREATE_FUNC(MailWrite);
    virtual bool init();
    //    virtual void onExit();
    ~MailWrite();
    
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void close();
    
    void send_502();
    void rec_502();
    
    bool istouch;
    bool istouch1;
    bool istouch2;
    bool istouch3;
    
    CCMenu * btnsMenu;
    
    CCEditBox* sender;
    CCEditBox* title;
    CCEditBox* desc;
    
    Loading* load;
    
    
};

#endif /* defined(__wx__MailWrite__) */
