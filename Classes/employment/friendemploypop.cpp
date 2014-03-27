

#include "friendemploypop.h"
#include "CustomPop.h"
#include <limits>

static FriendEmployPop* pop = NULL;
bool FriendEmployPop::init(){
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 180))){
        return false;
    }
    
    this->setTouchEnabled(true);
    
    
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);
    
    
    CCSprite *bkg = CCSprite::create("common_pop_bkg.png");
    bkg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bkg);
    CCSize sz = bkg->getContentSize();
    
    ccColor3B black = ccc3(0, 0, 0);
    
    CCLabelTTF* title = CCLabelTTF::create("提  示", "Verdana-Bold", 30);
    title->setColor(black);
    title->setAnchorPoint(ccp(0.5, 1));
    title->setPosition(ccp(sz.width/2, sz.height-1));
    bkg->addChild(title);
    
    
    
    desc = CCLabelTTF::create("", "Verdana", 30,CCSizeMake(400, 0),kCCTextAlignmentCenter);
    
    desc->setColor(black);
    //    desc->setAnchorPoint(ccp(0.5, 1));
    desc->setPosition(ccp(sz.width/2, sz.height/2+10));
    bkg->addChild(desc);
    
    
    CCMenuItemImage* bz = CCMenuItemImage::create("common_btn_ok_1.png", "common_btn_ok_2.png", this, menu_selector(FriendEmployPop::close));
    //    bz->setAnchorPoint(ccp(0,0));
    
    //    bz->setPosition(ccp(sz.width/2, 30));
    bz->setScale(1.3);
    
    btnsMenu = CCMenu::create(bz,NULL);
    btnsMenu->setPosition(ccp(sz.width/2,40));
    
    bkg->addChild(btnsMenu);
    
    
    return true;
}

void FriendEmployPop::show(const char* str)
{
    if(pop == NULL)
    {
        pop = FriendEmployPop::create();
    }
    
    CCDirector::sharedDirector()->getRunningScene()->addChild(pop);
    pop->desc->setString(str);
}

void FriendEmployPop::close()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    pop->removeFromParentAndCleanup(true);
    pop=NULL;
    
}

FriendEmployPop::~FriendEmployPop()
{
    
    CCLog("FriendEmployPop destroy");
    
    
}

void FriendEmployPop::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}

bool FriendEmployPop::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    istouch=btnsMenu->ccTouchBegan(touch, event);
    
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void FriendEmployPop::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if(istouch){
        
        btnsMenu->ccTouchMoved(touch, event);
    }
}
void FriendEmployPop::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    if (istouch) {
        btnsMenu->ccTouchEnded(touch, event);
        
        istouch=false;
        
    }
}
