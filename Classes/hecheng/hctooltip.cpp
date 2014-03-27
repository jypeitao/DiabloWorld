
#include "hctooltip.h"
#include "hcitemdata.h"
#include "CData.h"

bool hctooltip::init()
{
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 200)))
    {
        return false;
    }
    
    this->setTouchEnabled(false);
    CCSize tmpsz = CCDirector::sharedDirector()->getWinSize();
    size = CCSizeMake(tmpsz.width/2, tmpsz.height/2);
    
    this->setContentSize(size);
    
    
    
    return true;
}

void hctooltip::setData(int tempid)
{
    
    this->removeAllChildren();
    configGoodsItem * item = CData::getCData()->getConfigOfGoods(tempid);
    
    const ccColor3B color2 = {160,220,220};
    CCSprite* sp;
     char itemicon[40]="";
    if(item->icon >=6000 && item->icon<= 6056)
    {
        
       sprintf(itemicon, "qs_%d.png",item->icon);
        sp = CCSprite::create(itemicon);
        sp->setScale(0.19);
        sp->setAnchorPoint(ccp(0, 1));
        sp->setPosition(ccp(10, size.height - 10));
        this->addChild(sp);

    }
    else
    {
        sprintf(itemicon, "item_%d.png",item->icon);
        sp = CCSprite::create(itemicon);
         sp->setAnchorPoint(ccp(0, 1));
        sp->setPosition(ccp(10, size.height - 10));
        this->addChild(sp);
    }
        
    CCLabelTTF * labname =  CCLabelTTF::create(item->name.c_str(),"hycc.ttf", 20);
    labname->setPosition(ccp(size.width/2 +55, size.height - 50));
    labname->setColor(color2);
    this->addChild(labname);
    
    CCLabelTTF* labdesc = CCLabelTTF::create(item->des.c_str(), "hycc.ttf", 20);
    labdesc->setDimensions(CCSizeMake(size.width-20, 0));
    labdesc->setHorizontalAlignment(kCCTextAlignmentLeft);
    labdesc->setPosition(ccp(size.width/2, size.height - 200));
    labdesc->setColor(color2);
    this->addChild(labdesc);
    
    
}

void hctooltip::onExit()
{
    CCLog("hctooltip onExit");
    CCLayerColor::onExit();
}

hctooltip::~hctooltip()
{
    CCLog("hctooltip destroy");
}


