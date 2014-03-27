
#ifndef __client1__hcgoodsitem__
#define __client1__hcgoodsitem__

#include <iostream>
#include "cocos2d.h"
#include "hcitemdata.h"

USING_NS_CC;

class hcgoodsItem:public CCSprite
{
public:
    
//    virtual void onExit();
    ~hcgoodsItem();
    
    virtual bool init();
    void setData(hcitemdata *obj);
    void clData();
    
    
    hcitemdata* itemdata;
    
    //    CCObject * itemData;
    
    CCSprite * bkg;
    
    CCSprite *datasp;
    
    CCLabelTTF* lablenum;
    
        
    CREATE_FUNC(hcgoodsItem);
    
    
    
};

#endif /* defined(__client1__hcgoodsitem__) */
