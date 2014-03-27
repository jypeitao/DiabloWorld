#include "LevelMap.h"

#include "CustomPop.h"

LevelMap::~LevelMap()
{
    CCLog("LevelMap destroy");
    levelSpDic->release();
}

bool LevelMap::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    
    
    this->setTouchEnabled(true);
    
    levelSpDic = CCDictionary::create();
    levelSpDic->retain();
    
    
    currentMap = 0;
    
    size = CCDirector::sharedDirector()->getWinSize();
    mapLayer = CCSprite::create();
    CCSprite* m1 = CCSprite::create("map3.png");
    m1->setAnchorPoint(ccp(0, 0));
    m1->setPosition(ccp(0, 0));
    
    CCSprite* m2 = CCSprite::create("map1.png");
    m2->setAnchorPoint(ccp(0, 0));
    m2->setPosition(ccp(0, 441));
    
    CCSprite* m3 = CCSprite::create("map2.png");
    m3->setAnchorPoint(ccp(0, 0));
    m3->setPosition(ccp(0, 441*2));
    
    CCSprite* m4 = CCSprite::create("map3.png");
    m4->setAnchorPoint(ccp(0, 0));
    m4->setPosition(ccp(0, 441*3));
    
    CCSprite* m5 = CCSprite::create("map1.png");
    m5->setAnchorPoint(ccp(0, 0));
    m5->setPosition(ccp(0, 441*4));
    
   
    mapLayer->addChild(m1);
    mapLayer->addChild(m2);
    mapLayer->addChild(m3);
    mapLayer->addChild(m4);
    mapLayer->addChild(m5);
    mapLayer->setAnchorPoint(ccp(0, 0));
    mapLayer->setPosition(ccp(0, 0));
    
    mapSp = CCSprite::create();
    mapSp->addChild(mapLayer);
    mapSp->setAnchorPoint(ccp(0, 0));
    mapSp->setPosition(ccp(0, 0));
    this->addChild(mapSp);
    
    
    levelsMenu = CCMenu::create();
    levelsMenu->setAnchorPoint(ccp(0, 0));
    levelsMenu->setPosition(ccp(0, 0));
    this->addChild(levelsMenu);
    
    CCSprite* bkg = CCSprite::create("zjm_bkg.png");
    bkg->setAnchorPoint(ccp(0, 0));
    bkg->setPosition(ccp(0, 0));
    this->addChild(bkg);

    
    for (int i = 0; i < 9; i++)
    {
        CCMenuItemSprite* leveltmp = CCMenuItemImage::create("zjm_building_1.png", "zjm_building_1.png", "zjm_building_2.png",this, menu_selector(LevelMap::clkBuilding));
        
        int num = floor(i/3);//0,1,2
        
        leveltmp->setPosition(ccp((i-3*num)%2==1?140:size.width-130, (130)*(i%3) + 442*(int)floor(i/3) +240));//160
        levelSpDic->setObject(leveltmp, i);
        levelsMenu->addChild(leveltmp);
        
        
        const ccColor3B color3 = {255,175,100};
        const ccColor3B colorbg = {255,175,51};
        
        CCSize tmpsz = leveltmp->getContentSize();
        
        CCLabelTTF * name11=CCLabelTTF::create("", "hycc.ttf", 20);
        name11->setDimensions(CCSizeMake(200, 0));
        name11->setHorizontalAlignment(kCCTextAlignmentCenter);
        name11->setVerticalAlignment(kCCVerticalTextAlignmentTop);
        name11->setPosition(ccp(tmpsz.width/2-1, 35));
        
        name11->setColor(colorbg);
//        leveltmp->addChild(name11);
        leveltmp->addChild(name11, 10);
        name11->setTag(1002);
  
    }  
    char * json=CData::getCData()->cityData;
    Json::Reader read;
    Json::Value  root;
    if(read.parse(json, root))
    {
        data=root["data"];
    }
    currentLevelId = data["cityid"].asInt();

    if (CData::getCData()->levelMapOffsetY > 0)
    {
        offsetY = -((int)ceil((currentLevelId-1000)/3))*442;
        //size.height;
    }
    else
    {
        offsetY = CData::getCData()->levelMapOffsetY;
    }
    mapNum = CData::getCData()->getLevelMapNum();
    CCLog("%d",mapNum);
    adjustMap(true);
    
    return true;
}

void LevelMap::clkBuilding(CCMenuItemImage *building)
{
    
    
    MapItem *item = (MapItem*)building->getUserObject();
    
    if(item == NULL)
    {
        CustomPop::show("关卡信息为空！");
        return;
    }
    
    buildpop = buildingpop ::create();
    
    this->getParent()->addChild(buildpop,100);
    buildpop->show(item);

}

void LevelMap::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN, true);
    CCLayer::registerWithTouchDispatcher();
}

bool LevelMap::ccTouchBegan(CCTouch *touch, CCEvent *event)
{

    
    startP =  convertTouchToNodeSpace(touch);
    
    isTouchMenu=levelsMenu->ccTouchBegan(touch, event);
    
    CCPoint touchPoint = convertTouchToNodeSpace(touch);
    
    
    if (touchPoint.y < 80 || touchPoint.y > size.height - 180) {
        return false;
    }
    
    
    
    
    
    
    
    
    return true;
}

void LevelMap::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    
    movingP = convertTouchToNodeSpace(touch);
    distanceP = ccpSub(movingP, startP);
    CCPoint tmpP = mapLayer->getPosition();
    
    if(offsetY + distanceP.y > 0)
    {

        offsetY = 0;
        CData::getCData()->levelMapOffsetY = offsetY;
    }
    else if (offsetY + distanceP.y < -442*(mapNum-1))
    {

        offsetY =  -442*(mapNum-1);
        CData::getCData()->levelMapOffsetY = offsetY;
    }
    else
    {
        offsetY +=  distanceP.y;
        CData::getCData()->levelMapOffsetY = offsetY;
    }
    adjustMap(true);
    startP = movingP;
    
    if(isTouchMenu){
        
        levelsMenu->ccTouchMoved(touch, event);
    }
}

void LevelMap::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    
        
    
    if (isTouchMenu) {
        levelsMenu->ccTouchEnded(touch, event);
        
        isTouchMenu=false;
        
    }
    
    
    adjustMap(true);

    
    
}

void LevelMap::adjustMap(bool isResetLevel)
{
   int num = floor(offsetY/442);
    
    currentMap = -num;
    
    int offnum = num%3;
    float tmpoff = offsetY - num*442;
    mapLayer->setPosition(ccp(0, (offnum-1)*442 + tmpoff));
    
    

    
   if(isResetLevel)
   {
    
    int offlevel = 1000 + currentMap*3 -3;

    for (int i = 0; i < 9 ; i++)
    {
        
        MapItem* tmpLevelItemData = NULL;
        tmpLevelItemData = CData::getCData()->getConfigOfMapLevel(offlevel + i);
        
        
        
        
        
        
        CCMenuItemSprite* tmp = (CCMenuItemSprite*)levelSpDic->objectForKey(i);
        tmp->removeChildByTag(9999);
        
        if (tmpLevelItemData!= NULL && tmpLevelItemData->bid < currentLevelId)
        {
            CCSize tmpsz = tmp->getContentSize();
            CCSprite* ssp = CCSprite::create();
            
            int num = data["citylist"][tmpLevelItemData->bid - 1000].asInt();
            for (int k = 0; k<num; k++)
            {
                CCSprite * star = CCSprite::create("zjm_star.png");
                star->setPosition(ccp(k*30, 0));
                ssp->addChild(star);
                
            }
            ssp->setPosition(ccp(tmpsz.width/2-15*num+15, 0));
            ssp->setTag(9999);
            tmp->addChild(ssp, 0);
        }
        
        
        
        
        
        
        
        
        if(tmpLevelItemData != NULL)
        {
            
        if(tmpLevelItemData->bid > currentLevelId)
        {
            tmp->setEnabled(false);
        }
        else
        {
            tmp->setEnabled(true);
        }
        
            tmp->setUserObject(tmpLevelItemData);
            
        }
        
        //for (int j = 1001; j<=1005; j++)
        //{
            CCLabelTTF* tmpName = (CCLabelTTF*)(tmp->getChildByTag(1002));
            if(tmpLevelItemData)
            {
                tmpName->setString(tmpLevelItemData->nickname.c_str());
                

            }
        //}
        
        
        
        
        
        
    }
       
   }
    
    levelsMenu->setPosition(ccp(0, -442 + tmpoff));
    
}



