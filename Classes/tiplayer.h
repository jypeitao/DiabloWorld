
#ifndef __client1__tiplayer__
#define __client1__tiplayer__

#include <iostream>
#include "cocos2d.h"
#include "hcitemdata.h"

USING_NS_CC;
using namespace std;

class tiplayer:public CCLayerColor
{
public:
    
    virtual bool init();
    
    void setData(hcitemdata* data);
    hcitemdata *itemdata;
    CCSize size;
    
    CREATE_FUNC(tiplayer);
};

#endif /* defined(__client1__tiplayer__) */
