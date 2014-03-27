
#ifndef __wx__MailRenderer__
#define __wx__MailRenderer__

#define STATE_BTN_INVISIBLE 1
#define STATE_BTN_VISIBLE 2

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MailInfo.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MailRenderer:public CCTableViewCell
{
public:
    void setRead();
    void setInfo(MailInfo* info);
    //CREATE_FUNC(MailRenderer);
    MailRenderer();
    ~MailRenderer();
    
    
private:
    MailInfo* _info;
    //virtual bool init();
    int state;
    
};

#endif /* defined(__wx__MailRenderer__) */
