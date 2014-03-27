
#include "tiplayer.h"
#include "hcitemdata.h"
#include "CData.h"

bool tiplayer::init()
{
    if(!CCLayerColor::initWithColor(ccc4(50, 40, 20, 200)))
    {
        return false;
    }
    
    this->setTouchEnabled(false);
    CCSize tmpsz = CCDirector::sharedDirector()->getWinSize();
    size = CCSizeMake(tmpsz.width/2, tmpsz.height/2);
    this->setContentSize(size);
    

    
    return true;
}

void tiplayer::setData(hcitemdata* data)
{
    itemdata = data;
    this->removeAllChildren();
    
    configGoodsItem * item = CData::getCData()->getConfigOfGoods(data->tempid);
    
    
    char itemicon[40]="";
    if(item->icon>=6000&&item->icon<=6056)
    {
        sprintf(itemicon, "qs_%d.png",item->icon);
        CCSprite* sp = CCSprite::create(itemicon);
        sp->setAnchorPoint(ccp(0, 1));
        sp->setPosition(ccp(10, size.height - 10));
        sp->setScale(0.19);
        this->addChild(sp);

    }
    else
    {
        sprintf(itemicon, "item_%d.png",item->icon);
        CCSprite* sp = CCSprite::create(itemicon);
        sp->setAnchorPoint(ccp(0, 1));
        sp->setPosition(ccp(10, size.height - 10));
        this->addChild(sp);

    }
    
    
    string str ="";
    
    ccColor3B color;
    
    
//    configGoodsItem* item1 = CData::getCData()->getConfigOfGoods(item->growTemp);
    
    char tmp[100] = "";
    sprintf(tmp, "升级经验 (%d/%d)",itemdata->exp,item->maxexp);
    
        
    CCLabelTTF * labpz =  CCLabelTTF::create(tmp,"hycc.ttf", 25);
    labpz->setAnchorPoint(ccp(0, 0.5));
    labpz->setColor(ccc3(160,220,220));
    labpz->setHorizontalAlignment(kCCTextAlignmentLeft);
    labpz->setPosition(ccp(10, size.height - 200));
    this->addChild(labpz);
    
    switch (item->bodytype) {
        case 1:
            str = "【武器】";
            break;
        case 2:
            str = "【衣服】";
            break;
        case 3:
            str = "【兵符】";
            break;
        case 4:
            str = "【盾牌】";
            break;
        case 5:
            str = "【饰品】";
            break;
        case 6:
            str ="【技能书】";
            break;
            
        default:
            str = "【未知】";
            break;
    }
    
    CCLabelTTF * labpos =  CCLabelTTF::create(str.c_str(),"hycc.ttf", 20);
    labpos->setColor(ccc3(160,220,220));
    labpos->setAnchorPoint(ccp(0, 0.5));
    labpos->setHorizontalAlignment(kCCTextAlignmentLeft);
    labpos->setPosition(ccp(10, size.height - 150));
    this->addChild(labpos);
    
    
    CCLabelTTF * labname =  CCLabelTTF::create(item->name.c_str(),"hycc.ttf", 20);
    labname->setPosition(ccp(size.width/2 +35, size.height - 50));
    labname->setColor(ccc3(160,220,220));
    this->addChild(labname);
    
    CCLabelTTF* labdesc = CCLabelTTF::create(item->des.c_str(), "hycc.ttf", 20);
    labdesc->setDimensions(CCSizeMake(size.width-20, 0));
    labdesc->setColor(ccc3(160,220,220));
    labdesc->setHorizontalAlignment(kCCTextAlignmentLeft);
    labdesc->setPosition(ccp(size.width/2, size.height - 300));
    this->addChild(labdesc);
    
    

}