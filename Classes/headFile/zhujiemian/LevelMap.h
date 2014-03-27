#ifndef __wx__LevelMap__
#define __wx__LevelMap__

#include <iostream>

#include "cocos2d.h"

#include "popwindow.h"
#include "CData.h"

USING_NS_CC;
using namespace std;

class LevelMap:public CCLayer
{
public:
    CREATE_FUNC(LevelMap);
    
private:
    
    ~LevelMap();
    virtual bool init();
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    
    
    void adjustMap(bool isResetLevel);
    
    void clkBuilding(CCMenuItemImage * building);
    
    CCSize size;
    CCSprite* mapSp;
    CCSprite* mapLayer;
    
    CCPoint startP;
    CCPoint movingP;
    CCPoint endP;
    CCPoint distanceP;
    
    double offsetY;
    
    CCMenu* levelsMenu;
    bool isTouchMenu;
    
    int currentLevelId;
    
    
    int currentMap;
    int mapNum;
    
    CCDictionary* levelSpDic;
    
    buildingpop* buildpop;
    
    Json::Value  data;
};

#endif /* defined(__wx__LevelMap__) */
