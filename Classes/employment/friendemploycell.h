
#ifndef __wx__friendemploycell__
#define __wx__friendemploycell__


#define STATE_BTN_INVISIBLE 1
#define STATE_BTN_VISIBLE 2


#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

#include "friendinfo.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FriendEmployCell:public CCTableViewCell
{
public:
    void setFriendInfo(friendinfo* info);
    void changeState();
    void guyong();
    FriendEmployCell();
    ~FriendEmployCell();
    //CREATE_FUNC(FriendEmployCell);
private:
    
    //virtual bool init();
    
    void send_employ();
    void rec_employ();
    
    CCLabelTTF* rank;
    CCLabelTTF* name;
    CCLabelTTF* level;
    CCLabelTTF* skill;
    CCLabelTTF* price;
    CCLabelTTF* tip;
    
    int state;
    friendinfo* _info;
    
    CCSprite* textSp;
    
};

#endif /* defined(__wx__friendemploycell__) */
