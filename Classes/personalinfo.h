
#ifndef __client1__personalinfo__
#define __client1__personalinfo__

#include <iostream>
#include "cocos2d.h"
#include "goodsItem.h"
#include "tiplayer.h"
#include "LodingLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class personalinfo:public CCLayerColor
{
public:
    
    ~personalinfo();
    virtual void onExit();
    
    virtual bool init();
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
//    CCArray* itemArr;
    CCDictionary* itemArr;
    CCSize size;
    goodsItem *e1;
    goodsItem *e2;
    goodsItem *e3;
    goodsItem *e4;
    goodsItem *e5;
    goodsItem *e6;
    CCSprite* bj;
    CCSprite * headsp;
    
    bool readdraging;
    bool draging;
    hcitemdata *dragitem;
    
    CCLabelTTF* shang;
    CCLabelTTF* fang;
    CCLabelTTF* min;
    
    CCScale9Sprite * bigcardbkg;
    
    goodsItem * readydragingsp;
    goodsItem * dragingsp;
    
    goodsItem * acceptsp;
    int acceptindex;
    int dragingindex;
    
    tiplayer *tooltip;
    
    Loading* loading;
    
    
    CREATE_FUNC(personalinfo);
    
private:
    
    bool lock;
    
    void refresh_203();
    void refresh_204();
    
    void send_210();
    void rec_210();
    
    void send_203();
    void rec_203();
    
    void send_204();
    void rec_204();
    
    void send_212();
    void rec_212();
    
    void send_215();
    void rec_215();
    
};

#endif /* defined(__client1__personalinfo__) */
