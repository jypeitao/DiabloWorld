
#include "MailRenderer.h"


//bool MailRenderer::init()
//{
//    if (!CCTableViewCell::init()) {
//        return false;
//    }
//    
//        
//    return true;
//}
MailRenderer::MailRenderer(){
    state = STATE_BTN_INVISIBLE;
}
MailRenderer::~MailRenderer(){
    
}

void MailRenderer::setInfo(MailInfo *info)
{
    _info = info;
    
    
    int w = 420;
    int h = 80;
    
    CCScale9Sprite* sp = CCScale9Sprite::create("mitem_bkg.png");
    sp->setContentSize(CCSizeMake(w-10, h));
    sp->setAnchorPoint(ccp(0, 0));
    sp->setPosition(ccp(0, 0));
    this->addChild(sp);
    
    
    CCSprite* rdsp;
    if(_info->isReaded == 0)
    {
        rdsp = CCSprite::create("mail_noread.png");
    }
    else{
        rdsp = CCSprite::create("mail_read.png");
    }
    rdsp->setAnchorPoint(ccp(0, 0.5));
    rdsp->setPosition(ccp(5, h/2));
    sp->addChild(rdsp);

    
    
    
    
    
    ccColor3B color = ccc3(36, 24, 6);
    
    CCLabelTTF* time = CCLabelTTF::create(_info->sendTime.c_str(), "hycc.ttf", 14);
    time->setHorizontalAlignment(kCCTextAlignmentCenter);
    time->setColor(color);
    time->setAnchorPoint(ccp(0, 0));
    time->setPosition(ccp(250, h/2-10));
    sp->addChild(time);
//
//    
    CCLabelTTF* name = CCLabelTTF::create(_info->title.c_str(), "hycc.ttf", 24);
    name->setHorizontalAlignment(kCCTextAlignmentLeft);
    name->setColor(color);
    name->setAnchorPoint(ccp(0, 1));
    name->setPosition(ccp(70, h-5));
    sp->addChild(name);
//
//    
    char tmp[100] = "";
    sprintf(tmp, "发件人：%s",_info->sender.c_str());
    CCLabelTTF* money = CCLabelTTF::create(tmp, "hycc.ttf", 18);
    money->setHorizontalAlignment(kCCTextAlignmentLeft);
    money->setColor(color);
    money->setAnchorPoint(ccp(0, 0.5));
    money->setPosition(ccp(70, h/2-10));
    sp->addChild(money);
//
    
}

