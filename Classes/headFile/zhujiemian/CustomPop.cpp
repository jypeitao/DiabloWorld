
#include "CustomPop.h"
#include <limits>

static CustomPop* pop = NULL;
bool CustomPop::init(){
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
    
    ccColor3B black1 = ccc3(236, 190, 108);
    ccColor3B black = ccc3(27, 18, 6);
    
    CCLabelTTF* title = CCLabelTTF::create("提  示", "hycc.ttf", 28);
    title->setColor(black);
    title->setAnchorPoint(ccp(0.5, 1));
    title->setPosition(ccp(sz.width/2+1, sz.height-23));
    bkg->addChild(title);
    CCLabelTTF* title1 = CCLabelTTF::create("提  示", "hycc.ttf", 28);
    title1->setColor(black1);
    title1->setAnchorPoint(ccp(0.5, 1));
    title1->setPosition(ccp(sz.width/2, sz.height-22));
    bkg->addChild(title1);
    
    
    
    desc = CCLabelTTF::create("", "hycc.ttf", 25,CCSizeMake(400, 0),kCCTextAlignmentCenter);
    
    desc->setColor(black);
//    desc->setAnchorPoint(ccp(0.5, 1));
    desc->setPosition(ccp(sz.width/2, sz.height/2+10));
    bkg->addChild(desc);
    
    
    CCMenuItemImage* bz = CCMenuItemImage::create("common_btn_ok_1.png", "common_btn_ok_2.png", this, menu_selector(CustomPop::close));
//    bz->setAnchorPoint(ccp(0,0));
    
//    bz->setPosition(ccp(sz.width/2, 30));
    bz->setScale(1.3);
    
    btnsMenu = CCMenu::create(bz,NULL);
    btnsMenu->setPosition(ccp(sz.width/2,80));
    
    bkg->addChild(btnsMenu);
    

    return true;
}

void CustomPop::show(const char* str)
{
    if(pop == NULL)
    {
        pop = CustomPop::create();
    }
    
    CCDirector::sharedDirector()->getRunningScene()->addChild(pop);
    pop->desc->setString(str);
}

void CustomPop::close()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    pop->removeFromParentAndCleanup(true);
    //pop->removeFromParent();
    //this->removeChild(pop);
    pop=NULL;
    
}

CustomPop::~CustomPop()
{
    
    CCLog("CustomPop destroy");
    

}

void CustomPop::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}

bool CustomPop::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    istouch=btnsMenu->ccTouchBegan(touch, event);
    
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void CustomPop::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if(istouch){
        
        btnsMenu->ccTouchMoved(touch, event);
    }
}
void CustomPop::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    if (istouch) {
        btnsMenu->ccTouchEnded(touch, event);
        
        istouch=false;
        
    }
}
