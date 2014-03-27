

#include "friendemploycell.h"
#include "friendemploy.h"

//bool FriendEmployCell::init()
//{
//    if (!CCTableViewCell::init()) {
//        return false;
//    }
//    
//    state = STATE_BTN_INVISIBLE;
//    
//    return true;
//}
FriendEmployCell::FriendEmployCell(){
    state = STATE_BTN_INVISIBLE;
}
FriendEmployCell::~FriendEmployCell(){
    
}
void FriendEmployCell::setFriendInfo(friendinfo *info)
{
    _info = info;
    
    ccColor3B color;
    if (info->guyong) {
        color = ccc3(27, 113, 124);
    }
    else
    {
        color = ccc3(217,195,118);
    }
    
    CCScale9Sprite* spp = CCScale9Sprite::create("employfriend_item_bkg.png");
    int w = 420;
    int h = 80;
    spp->setContentSize(CCSizeMake(w, h));
    spp->setAnchorPoint(ccp(0, 0));
    this->addChild(spp);
    
    textSp = CCSprite::create();
    textSp->setContentSize(CCSizeMake(w, h));
    textSp->setAnchorPoint(ccp(0, 0));
    this->addChild(textSp);
    
    char tmp[20] = "";
//    sprintf(tmp, "%d",info->rank);
//    rank = CCLabelTTF::create(tmp, "hycc.ttf", 18);
//    rank->setPosition(ccp(33, h/2));
//    textSp->addChild(rank);
//    rank->setColor(color);
    
    name = CCLabelTTF::create(info->name.c_str(), "hycc.ttf", 18, CCSizeMake(150, 20), kCCTextAlignmentCenter); //CCLabelTTF::create(info->name.c_str(), "Verdana", 18);
    name->setPosition(ccp(140, h/2-3));
    textSp->addChild(name);
    name->setColor(color);

    
    sprintf(tmp, "%d",info->level);
    level = CCLabelTTF::create(tmp, "hycc.ttf", 18);
    //level->setPosition(ccp(200, h/2));
    level->setPosition(ccp(37, h/2));
    textSp->addChild(level);
    level->setColor(color);

    
    skill = CCLabelTTF::create(info->skill.c_str(), "hycc.ttf", 18);
    skill->setPosition(ccp(315, h/2+15));
    textSp->addChild(skill);
    skill->setColor(color);

    
    sprintf(tmp, "%d",info->price);
    price = CCLabelTTF::create(tmp, "hycc.ttf", 18, CCSizeMake(150, 20), kCCTextAlignmentRight); //CCLabelTTF::create(tmp, "Verdana", 18);
    //price->setAnchorPoint(ccp(1, 0.5));
    price->setPosition(ccp(270, h/2-15));
    textSp->addChild(price);
    price->setColor(color);
    
    tip = CCLabelTTF::create("确认雇佣？", "hycc.ttf", 18);
    tip->setPosition(ccp(w+60, h/2));
    textSp->addChild(tip);
    tip->setColor(color);


    CCMenuItemImage* ok = CCMenuItemImage::create("common_sbtn_ok_1.png", "common_sbtn_ok_2.png", this, menu_selector(FriendEmployCell::send_employ));
    ok->setScale(1.3);
    ok->setAnchorPoint(ccp(0, 0.5));
    ok->setPosition(ccp(20, h/2-5));
    CCMenu* menu = CCMenu::create();
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(w+150, 0));
    menu->setTag(1011);
    menu->addChild(ok);
    menu->setTouchPriority(INT_MIN);
    textSp->addChild(menu);
    
    
//    kCCMenuHandlerPriority
    //        CCMenuItemImage* ok = CCMenuItemImage::create("common_btn_ok_1.png", "common_btn_ok_2.png", this, menu_selector(FriendEmployCell::send_employ));
    //        ok->setUserObject(info);
    //        ok->setAnchorPoint(ccp(0, 1));
    //
    ////        CCMenu* menu = CCMenu::create();
    ////        menu->addChild(ok);
    ////
    ////        menu->setAnchorPoint(ccp(0, 0));
    //        cell->addChild(ok);

}

void FriendEmployCell::guyong()
{
//    textSp->setPosition(ccp(0, 0));
//    this->reset();
//    _info->guyong = true;
//    setFriendInfo(_info);
}

void FriendEmployCell::changeState()
{
    
    if (_info->guyong) {
        return;
    }
    
    
    if (state == STATE_BTN_INVISIBLE) {
        textSp->setPosition(ccp(-300, 0));
        state = STATE_BTN_VISIBLE;
    }
    else
    {
        textSp->setPosition(ccp(0, 0));
        state = STATE_BTN_INVISIBLE;
    }
}

void FriendEmployCell::send_employ()
{
//    _info->guyong = true;
    state = STATE_BTN_INVISIBLE;
    textSp->setPosition(ccp(0, 0));
    
    ccColor3B color = ccc3(27, 113, 124);
    //rank->setColor(color);
    name->setColor(color);
    level->setColor(color);
    skill->setColor(color);
    price->setColor(color);
//    CCLabelTTF* name;
//    CCLabelTTF* level;
//    CCLabelTTF* skill;
//    CCLabelTTF* price;
//    CCLabelTTF* tip;
    
    
    CCLog("FriendEmployCell::send_employ");
    ((friendemploy*)this->getParent())->send_employ(_info);
        
}
