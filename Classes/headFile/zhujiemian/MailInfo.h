
#ifndef __wx__MailInfo__
#define __wx__MailInfo__

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class MailInfo:public CCObject
{
public:
    MailInfo()
    {
        
    };
    int mailId;
    string title;
    string sender;
    string sendTime;
    string content;

    
    int isReaded;

    
};

#endif /* defined(__wx__MailInfo__) */
