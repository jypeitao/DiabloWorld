#ifndef __zd__startAnimate__
#define __zd__startAnimate__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class startAnimate:public CCLayer
{
public:
    CREATE_FUNC(startAnimate);
    virtual bool init();
    CCSprite *str1,*str2,*str3,*str4,*str5,*str6,*str7,*str8,*str9;
    int round;
    void kong();
    void animateDesc();
    void animateTwo();
    void animateThree();
    void animateFour();
    void callbackSelectRole(CCObject *pSender);
    ~startAnimate();
};

#endif /* defined(__zd__startAnimate__) */
