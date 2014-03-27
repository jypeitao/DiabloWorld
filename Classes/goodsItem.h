
#ifndef __client1__goodsItem__
#define __client1__goodsItem__

#include <iostream>
#include "cocos2d.h"
#include "hcitemdata.h"

USING_NS_CC;

class goodsItem:public CCSprite
{
public:
    
    ~goodsItem();
//    virtual void onExit();
    
    virtual bool init();
    void setData(hcitemdata *obj);
    void clData();

    
    hcitemdata* itemdata;
    


    CCSprite * bkg;

    CCSprite *datasp;
    

    


    CREATE_FUNC(goodsItem);
    
    

};


#endif /* defined(__client1__goodsItem__) */
