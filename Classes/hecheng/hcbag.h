
#ifndef __client1__hcbag__
#define __client1__hcbag__

#include <iostream>
#include"cocos2d.h"
#include "myobject.h"
#include "LodingLayer.h"
#include "hcitemdata.h"
#include "CHecheng.h"
#include "hcgoodsitem.h"
#include "hctooltip.h"

USING_NS_CC;
using namespace std;


class hcbag:public CCLayerColor{
public:
    
    ~hcbag();
    virtual void onExit();
    virtual bool init();
    
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    bool istouch;
    
    void setData(char * data);
    void clkItem(CCSprite * item);
    void close();
    void ok();
    
    CCSprite * tmpsp;
    hcitemdata * tmpdata;
    CCSprite * hightlightsp;
    
    hcgoodsItem * tmpGoodsItem;
    
    CCSize size;
    CCMenu * menu;
    CHecheng* hc;
    
    CCDictionary * dicGoods;
    
    hctooltip * tooltip;
    
    
    CCMenuItemImage * okBtn;
    
    CREATE_FUNC(hcbag);
};


#endif /* defined(__client1__hcbag__) */
