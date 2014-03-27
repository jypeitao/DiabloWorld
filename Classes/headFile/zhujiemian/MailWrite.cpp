
#include "MailWrite.h"
#include "CData.h"
#include "SocketManager.h"
#include "CustomPop.h"
#include "json.h"
#include <limits>

static MailWrite* pop = NULL;
bool MailWrite::init(){
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 180))){
        return false;
    }
    
    this->setTouchEnabled(true);
    
    
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);
    
    
    CCSprite *bkg = CCSprite::create("mail_write_bkg.png");
    bkg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bkg);
    CCSize sz = bkg->getContentSize();
    
    ccColor3B black = ccc3(36, 24, 6);
    
    //    CCLabelTTF* title = CCLabelTTF::create("提  示", "Verdana-Bold", 30);
    //    title->setColor(black);
    //    title->setAnchorPoint(ccp(0.5, 1));
    //    title->setPosition(ccp(sz.width/2, sz.height-1));
    //    bkg->addChild(title);

    CCScale9Sprite* editbkg2 = CCScale9Sprite::create();
    sender = CCEditBox::create(CCSizeMake(300,40),editbkg2);
    sender->setReturnType(kKeyboardReturnTypeDone);
    sender->setFontColor(black);
    sender->setMaxLength(8);
    sender->setAnchorPoint(ccp(0, 0.5));
    sender->setPosition(ccp(150, 240));
    bkg->addChild(sender);
    
    
//    editBoxUsername = CCEditBox::create(CCSizeMake(160,40),editbkg);
//    editBoxUsername->setReturnType(kKeyboardReturnTypeDone);
//    editBoxUsername->setFontSize(12);
//    editBoxUsername->setPosition(ccp(160,100));
//    editBoxUsername->setFontColor(ccc3(0, 0, 0));
    CCScale9Sprite* editbkg = CCScale9Sprite::create();
    title = CCEditBox::create(CCSizeMake(300,40),editbkg);
    title->setReturnType(kKeyboardReturnTypeDone);
    title->setFontColor(black);
    title->setMaxLength(8);
    title->setAnchorPoint(ccp(0, 0.5));
    title->setPosition(ccp(150, 186));
    bkg->addChild(title);
    
    
    CCScale9Sprite* editbkg1 = CCScale9Sprite::create();
    desc = CCEditBox::create(CCSizeMake(395,40),editbkg1);
    desc->setReturnType(kKeyboardReturnTypeDone);

//    desc = CCLabelTTF::create("", "Verdana", 25,CCSizeMake(400, 0),kCCTextAlignmentLeft);
    desc->setFontColor(black);
    desc->setMaxLength(20);
    desc->setAnchorPoint(ccp(0, 1));
    desc->setPosition(ccp(115, 152));
    bkg->addChild(desc);
    
//    sender->setMaxLength(10);
//    title->setMaxLength(10);
//    desc->setMaxLength(15);
    
    CCMenuItemImage* bz = CCMenuItemImage::create("common_btn_send_1.png", "common_btn_send_2.png", this, menu_selector(MailWrite::send_502));

    bz->setPosition(ccp(100, 20));
    
    
    CCMenuItemImage* bz2 = CCMenuItemImage::create("common_btn_return_11.png", "common_btn_return_22.png", this, menu_selector(MailWrite::close));
    bz2->setPosition(ccp(-100, 20));
        
    btnsMenu = CCMenu::create(bz,bz2,NULL);
    btnsMenu->setPosition(ccp(sz.width/2,45));
    
    bkg->addChild(btnsMenu);
    
    
    return true;
}

void MailWrite::show()
{
    if(pop == NULL)
    {
        pop = MailWrite::create();
    }
    
    CCDirector::sharedDirector()->getRunningScene()->addChild(pop);
//    pop->sender->setString(info->sender.c_str());
//    pop->title->setString(info->title.c_str());
//    pop->desc->setString(info->content.c_str());
}

void MailWrite::close()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    pop->removeFromParentAndCleanup(true);
    pop=NULL;
    
}


void MailWrite::send_502()
{
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    root["pname"] = sender->getText();
    root["title"] = title->getText();
    root["content"] = desc->getText();
    
    
    
    string json_file=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 502);
    this->schedule(schedule_selector(MailWrite::rec_502));
    load = Loading::create();
    this->addChild(load, 9999);
}

void MailWrite::rec_502()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(502);
    CData::getCData()->m_dictionary->removeObjectForKey(502);
    
    
    if(revMsg)
    {
        load->removeFromParent();
        
        
        this->unschedule(schedule_selector(MailWrite::rec_502));
        char* data=revMsg->data;
        CCLog("%s",data);
        Json::Reader read;
        Json::Value root;
            
        
        if(read.parse(data, root)){
            if(root["result"].asBool())
            {
                this->close();
                CustomPop::show("发送成功！");
            }
            else
            {
                std::string out = root["message"].asCString();
                CustomPop::show(out.c_str());
            }
        }
    }

}

MailWrite::~MailWrite()
{
    
    CCLog("MailWrite destroy");
    
    
}

void MailWrite::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}

bool MailWrite::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    istouch=btnsMenu->ccTouchBegan(touch, event);
    istouch1 = title->ccTouchBegan(touch, event);
    istouch2 = desc->ccTouchBegan(touch, event);
    istouch3 = sender->ccTouchBegan(touch, event);
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void MailWrite::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if(istouch){
        
        btnsMenu->ccTouchMoved(touch, event);
    }
    if (istouch1) {
        title->ccTouchMoved(touch, event);
    }
    if (istouch2) {
        desc->ccTouchMoved(touch, event);
    }
    if (istouch3) {
        sender->ccTouchMoved(touch, event);
    }
}
void MailWrite::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    if (istouch) {
        btnsMenu->ccTouchEnded(touch, event);
        
        istouch=false;
        
    }
    
    
    if (istouch1) {
        title->ccTouchEnded(touch, event);
        
        istouch1 = false;
    }
    if (istouch2) {
        desc->ccTouchEnded(touch, event);
        istouch2 = false;
    }
    if (istouch3) {
        sender->ccTouchEnded(touch, event);
    }
}
