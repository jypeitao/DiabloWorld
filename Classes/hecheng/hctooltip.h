
#ifndef __client1__hctooltip__
#define __client1__hctooltip__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class hctooltip:public CCLayerColor
{
public:
    
    virtual bool init();
    virtual void onExit();
    ~hctooltip();
    
    void setData(int tempid);
    
    CCSize size;
    
    CREATE_FUNC(hctooltip);
};
#endif /* defined(__client1__hctooltip__) */
