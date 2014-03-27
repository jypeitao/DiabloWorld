
#include "hcgoodsitem.h"
#include "CData.h"
bool hcgoodsItem::init()
{
    
    if (!CCSprite::init()) {
        return false;
    }
    
    itemdata = NULL;
    
    bkg = CCSprite::create("common_item_bkg1.png");
    bkg->setAnchorPoint(ccp(0, 0));
    this->addChild(bkg);
    
    this->setContentSize(bkg->getContentSize());
    
    
    return true;
}


void hcgoodsItem::setData(hcitemdata *obj)
{
    bkg->removeChild(datasp,true);
    
    itemdata = obj;
    if(itemdata == NULL)
    {
        return;
    }
    
    
    configGoodsItem *gooditem = CData::getCData()->getConfigOfGoods(obj->tempid);
    char itemicon[40]="";
    if(gooditem->icon >=6000 && gooditem->icon<= 6056)
    {
        
        sprintf(itemicon, "qs_%d.png",gooditem->icon);
        datasp = CCSprite::create(itemicon);
        datasp->setScale(0.19);
    }
    else
    {
        sprintf(itemicon, "item_%d.png",gooditem->icon);
        datasp = CCSprite::create(itemicon);
    }
    CCSize sz = bkg->getContentSize();
    datasp->setPosition(ccp(sz.width/2, sz.height/2));
    bkg->addChild(datasp);

        char numstr[10] = "";
        sprintf(numstr, "%d",itemdata->num);
        lablenum = CCLabelTTF::create(numstr, "hycc.ttf", 20);
        lablenum->setColor(ccc3(0, 255, 0));
        lablenum->setAnchorPoint(ccp(1, 0));
        lablenum->setPosition(ccp(sz.width-5, 0));
        bkg->addChild(lablenum);

    
}

void hcgoodsItem::clData()
{
    setData(NULL);
}

hcgoodsItem::~hcgoodsItem()
{
    
    CCLog("hcgoodsItem destroy");
}


