

#ifndef __wx__friendinfo__
#define __wx__friendinfo__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

#endif /* defined(__wx__friendinfo__) */

class friendinfo:public CCObject
{
public:
    friendinfo()
    {
        
    };
    int userid;
    string name;
    string skill;
    
    int level;
    
    int price;
    int rank;
    
    bool guyong;
    
//    CREATE_FUNC(friendinfo);
    
    
};