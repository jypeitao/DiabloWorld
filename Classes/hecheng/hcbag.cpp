#include "hcbag.h"
#include "json.h"
#include "hcitemdata.h"
#include "CustomPop.h"


bool hcbag::init()
{
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 230)))
    {
        return false;
    }

    size = CCDirector::sharedDirector()->getWinSize();
    tmpsp = NULL;
    this->setTouchEnabled(true);
    
    
    tmpGoodsItem = NULL;
    
    tooltip = hctooltip::create();
    this->addChild(tooltip,1000);
    tooltip->setVisible(false);
    
    
    dicGoods = CCDictionary::create();
    dicGoods->retain();
    
    return true;
}

void hcbag::ok()
{
    if(tmpGoodsItem && tmpGoodsItem->itemdata && tmpGoodsItem->itemdata->num >=4)
    {
        hc->sethcdata(tmpGoodsItem->itemdata);
        this->removeFromParent();
    }
    else
    {
        CustomPop::show("合成条件不足");
    }

}

void hcbag::close()
{
    this->removeFromParent();
}

void hcbag::clkItem(CCSprite * item)
{
    if(tmpsp)
    {
        tmpsp->removeChild(hightlightsp, true);
    }
   
    hightlightsp = CCSprite::create("common_item_bkg.png");
    
    hightlightsp->setAnchorPoint(ccp(0, 0));
    
    item->addChild(hightlightsp);
    
    tmpsp = item;
    tmpdata = (hcitemdata *)item->getUserObject();
    
    okBtn->setEnabled(true);
    
}

void hcbag::setData(char *data)
{
    Json::Reader read;
    Json::Value root;
    Json::Value jsonData;
    Json::Value itemList;
    if(read.parse(data, root)){
        bool result=root["result"].asBool();
        if(result){
            jsonData=root["data"];
            CCLog("%s",data);
            itemList=jsonData["itemlist"];
            
            
            
                        
            for (int j = 0; j<25; j++) {
                
                hcgoodsItem *sp = hcgoodsItem::create();
                
                CCSize k = sp->getContentSize();
                int kk = k.width;
                
                sp->setPosition(ccp(((size.width - kk*5)/6 + kk) * (j%5 + 1) -kk/2,  size.height -120 * (j/5) - 80));
                
                this->addChild(sp);
                
                dicGoods->setObject(sp, j);
            }
            
            
            
            
            for(int i=0;i<itemList.size();i++){//itemList.size()
                
                                
                hcitemdata * item = new hcitemdata();
                item->itemid =itemList[i]["itemid"].asInt();
//                item->icon = itemList[i]["icon"].asInt();
                item->tempid  =itemList[i]["tempid"].asInt();
                item->num = itemList[i]["stack"].asInt();
                
                hcgoodsItem* itemsp = (hcgoodsItem*) dicGoods->objectForKey(i);
                
                itemsp->setData(item);
                
                }
            
            menu = CCMenu::create();
            menu->setContentSize(size);
            this->addChild(menu);
            
            
            
            CCMenuItemImage * clsBtn=CCMenuItemImage::create("common_btn_return_1.png", "common_btn_return_2.png", this, menu_selector(hcbag::close));
            
            clsBtn->setScale(1.3);
            clsBtn->setAnchorPoint(ccp(0, 0));
            clsBtn->setPosition(ccp(100, 80));
            
             okBtn=CCMenuItemImage::create("common_sbtn_ok_1.png", "common_sbtn_ok_2.png","common_sbtn_ok_3.png", this, menu_selector(hcbag::ok));
            okBtn->setScale(1.3);
//            okBtn->setEnabled(false);
            okBtn->setAnchorPoint(ccp(1, 0));
            okBtn->setPosition(ccp(size.width-100, 80));
//            CCLabelTTF * t_CK1=CCLabelTTF::create("确 定", "Helvetica", 30);
////            t_CK1->setAnchorPoint(ccp(0, 0));
//            t_CK1->setPosition(ccp(tmpsz.width/2, tmpsz.height/2));
//            okBtn->addChild(t_CK1);
            
            menu->addChild(okBtn);
            menu->addChild(clsBtn);

            
//            menu->alignItemsHorizontallyWithPadding(10);
            menu->setAnchorPoint(ccp(0, 0));
            menu->setPosition(ccp(0, 0));
            
        }
    }
    
//            
//            const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("item.json").c_str();
//            ifstream ifs;
//            ifs.open(path);
//            assert(ifs.is_open());
//            Json::Reader reader;
//            Json::Value root;
    

}

void hcbag::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}

bool hcbag::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    CCPoint touchPoint=convertTouchToNodeSpace(touch);
    hcgoodsItem* item;
    int len = dicGoods->count();
    
    for (int i = 0; i<len; i++) {
        item =(hcgoodsItem*) dicGoods->objectForKey(i);
        if(item->boundingBox().containsPoint(touchPoint))
        {
            if(item->itemdata)
            {
                
                if(tmpGoodsItem)
                {
                    tmpGoodsItem->removeChild(hightlightsp, true);
                }
                tmpGoodsItem = item;
                hightlightsp = CCSprite::create("common_item_bkg.png");
                hightlightsp->setScale(1.1);
                hightlightsp->setAnchorPoint(ccp(0, 0));
                hightlightsp->setPosition(ccp(0, -3));
                tmpGoodsItem->addChild(hightlightsp);
                
            
            tooltip->setData(item->itemdata->tempid);
            tooltip->setVisible(true);
            
            CCPoint p =ccp(touchPoint.x + 10 ,touchPoint.y + 10);
            
            CCSize sz = tooltip->getContentSize();
            if(touchPoint.x > size.width - sz.width)
            {
                p.x = touchPoint.x - sz.width - 10;
            }
            
            if(touchPoint.y > size.height - sz.height)
            {
                p.y = touchPoint.y - sz.height;
            }
            
            
            
            tooltip->setPosition(p);
            }
        }
        
    }
    istouch=menu->ccTouchBegan(touch, event);
    
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void hcbag::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    tooltip->setVisible(false);
    
    if(istouch){
        
        menu->ccTouchMoved(touch, event);
    }
}
void hcbag::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    tooltip->setVisible(false);
    
    CCPoint touchPoint=convertTouchToNodeSpace(touch);
    hcgoodsItem* item;
    int len = dicGoods->count();
    
    for (int i = 0; i<len; i++) {
        item =(hcgoodsItem*) dicGoods->objectForKey(i);
        if(item->boundingBox().containsPoint(touchPoint))
        {
            
            
        }
        
    }
    
    
    if (istouch) {
        menu->ccTouchEnded(touch, event);
        
        istouch=false;
    }
}

void hcbag::onExit()
{
    CCLog("hcbag onExit");
//    
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayerColor::onExit();
}


hcbag::~hcbag()
{
    CCLog("hcbag destroy");
}



