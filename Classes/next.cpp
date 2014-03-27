
#include "next.h"
#include "FireWork.h"
bool next::init(){
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))){
        return false;
    }
    setTouchEnabled(true);
    return true;
}
void  next::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    //CCLayer::registerWithTouchDispatcher();(std::numeric_limits<int>::min())
    CCLayer::registerWithTouchDispatcher();
}

bool next::ccTouchBegan(CCTouch* touch, CCEvent* event){
    return true;
}
void next::ccTouchMoved(CCTouch* touch, CCEvent* event){
    
}
void next::ccTouchEnded(CCTouch* touch, CCEvent* event){
    CCLog("sdfqwe");
    Fire * fir=(Fire *)this->getParent();
    fir->nextchat();
}