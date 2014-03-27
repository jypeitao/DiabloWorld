//
//  friendmain.cpp
//  client1
//
//  Created by guoyahui on 13-5-27.


#include "friendmain.h"

bool friendmain::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);
    
    CCSprite* bkg = CCSprite::create("friendmain_bkg.png");
    bkg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bkg);
    
    CCMenuItemImage* btn_employ = CCMenuItemImage::create("friendmain_btn_emply_1.png", "friendmain_btn_emply_2.png", this, menu_selector(friendmain::showfriendemploy));
    
    CCMenuItemImage* btn_employlog = CCMenuItemImage::create("friendmain_btn_log_1.png", "friendmain_btn_log_2.png", this, menu_selector(friendmain::showfriendemploylog));
    
    CCMenu* menu = CCMenu::create(btn_employ,btn_employlog,NULL);
    menu->setPosition(ccp(size.width/2, size.height/2-5));
//    menu->alignItemsVertically();
    menu->alignItemsVerticallyWithPadding(90);
    this->addChild(menu);
    
    
    
    return true;
}

void friendmain::showfriendemploy()
{
    _friendemploy = friendemploy::create();
    this->addChild(_friendemploy);
    
}
void friendmain::showfriendemploylog()
{
    _friendemploylog = friendemploylog::create();
    this->addChild(_friendemploylog);
}

