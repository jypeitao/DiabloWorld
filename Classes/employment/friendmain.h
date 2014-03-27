

#ifndef __client1__friendmain__
#define __client1__friendmain__

#include <iostream>
#include "cocos2d.h"

#include "friendemploy.h"
#include "friendemploylog.h"

USING_NS_CC;
using namespace std;

class friendmain:public CCLayer
{
public:
    
//    ~friendmain();
    CREATE_FUNC(friendmain);
    
    
    
private:
    
    virtual bool init();
    
    void showfriendemploy();
    void showfriendemploylog();
    void showfriendinvite();
    
    friendemploy*       _friendemploy;
    friendemploylog*    _friendemploylog;
    
    
    CCSize size;

    
    
    

};

#endif /* defined(__client1__friendmain__) */
