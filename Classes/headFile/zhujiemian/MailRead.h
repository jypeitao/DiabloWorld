
#ifndef __wx__MailRead__
#define __wx__MailRead__

#include <iostream>
#include "cocos2d.h"
#include "MailInfo.h"

USING_NS_CC;

class MailRead:public CCLayerColor
{
public:
    
    static void show(MailInfo* info);
    
private:
    CREATE_FUNC(MailRead);
    virtual bool init();
    //    virtual void onExit();
    ~MailRead();
    
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void close();
    
    bool istouch;
    
    CCMenu * btnsMenu;
    
    CCLabelTTF* sender;
    CCLabelTTF* title;
    CCLabelTTF* desc;
};

#endif /* defined(__wx__MailRead__) */
