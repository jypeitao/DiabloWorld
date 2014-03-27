#include "popwindow.h"
#include "FireWork.h"
#include "SocketClient.h"
#include "LayerLogin.h"
#include "message.h"

#include "homePage.h"
#include "SocketManager.h"

#include "CustomPop.h"

bool buildingpop::init(){
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 128))){
        
        
        return false;
    }
  
    this->setTouchEnabled(true);
    
    
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);
    
    lock = false;
    
    CCSprite *bkg = CCSprite::create("popbuilding_buzhen_bkg.png");
//    bkg->setAnchorPoint(ccp(0, 0));
    
    
    
    bkg->setPosition(ccp(size.width/2, size.height/2));
    
    this->addChild(bkg);
    //bkg->setScale(1.2);

    size = bkg->getContentSize();
    
    name = CCLabelTTF::create("", "hycc.ttf", 18);
    name->setAnchorPoint(ccp(0, 1));
    //name->setHorizontalAlignment(kCCTextAlignmentLeft);
    name->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    name->setDimensions(CCSizeMake(60, 0));
//    name->setAnchorPoint(ccp(1, 1));
    name->setPosition(ccp(53, size.height-225));
    const ccColor3B color1 = {121,96,67};
    name->setColor(color1);
    bkg->addChild(name);
    
    namedesc = CCLabelTTF::create("", "hycc.ttf", 18);
    namedesc->setAnchorPoint(ccp(0, 1));
    namedesc->setDimensions(CCSizeMake(300, 0));
    namedesc->setHorizontalAlignment(kCCTextAlignmentLeft);
    namedesc->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    namedesc->setPosition(ccp(140, size.height-220));
    const ccColor3B color2 = {36,24,6};
    namedesc->setColor(color2);
    bkg->addChild(namedesc);
    
    name1 = CCLabelTTF::create("敌人", "hycc.ttf", 18);
    name1->setAnchorPoint(ccp(0, 1));
    name1->setHorizontalAlignment(kCCTextAlignmentLeft);
    name1->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    name1->setDimensions(CCSizeMake(60, 0));
//    name1->setAnchorPoint(ccp(1, 1));
    name1->setPosition(ccp(70, size.height-335));
//    const ccColor3B color1 = {255,255,255};
    name1->setColor(color1);
    bkg->addChild(name1);
    
    namedesc1 = CCLabelTTF::create("", "hycc.ttf", 18);
    namedesc1->setAnchorPoint(ccp(0, 1));
    namedesc1->setDimensions(CCSizeMake(300, 0));
    namedesc1->setHorizontalAlignment(kCCTextAlignmentLeft);
    namedesc1->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    namedesc1->setPosition(ccp(135, size.height-328));
//    const ccColor3B color2 = {0,255,0};
    namedesc1->setColor(color2);
    bkg->addChild(namedesc1);

    
//    name2 = CCLabelTTF::create("奖励", "hycc.ttf", 18);
//    name2->setAnchorPoint(ccp(0, 1));
//    name2->setHorizontalAlignment(kCCTextAlignmentLeft);
//    name2->setVerticalAlignment(kCCVerticalTextAlignmentTop);
//    name2->setDimensions(CCSizeMake(400, 0));
//    //    name1->setAnchorPoint(ccp(1, 1));
//    name2->setPosition(ccp(40, size.height-213));
//    //    const ccColor3B color1 = {255,255,255};
//    name2->setColor(color1);
//    bkg->addChild(name2);
    
    cl=CCMenuItemImage::create("common_btn_close_1.png", "common_btn_close_2.png",this, menu_selector(buildingpop::close));
    cl->setPosition(ccp(453, 650));
    bz = CCMenuItemImage::create("popbuilding_buzhen_1.png", "popbuilding_buzhen_2.png",this, menu_selector(buildingpop::buzhen));//buildingpop::close,buildingpop::buzhen
   
//    cl->setAnchorPoint(ccp(0,0));
    bz->setPosition(ccp(152, 207));
    
    ft = CCMenuItemImage::create("popbuilding_fire_1.png", "popbuilding_fire_2.png","popbuilding_fire_3.png", this, menu_selector(buildingpop::fight));
    ft->setAnchorPoint(ccp(0,0));
    ft->setPosition(ccp(243, 180));
    //ft->setScale(1.3);
    
//    bz = CCMenuItemImage::create("", "", this, menu_selector(buildingpop::buzhen));
//    bz->setAnchorPoint(ccp(0,0));
//    bz->setPosition(ccp(40, 30));
    //bz->setScale(1.3);
    
    btnsMenu = CCMenu::create(cl,ft,bz,NULL);
    
    btnsMenu->setAnchorPoint(ccp(0,0));
    btnsMenu->setPosition(ccp(0,0));
    
    bkg->addChild(btnsMenu);
    
    CCSprite* gold = CCSprite::create("popbuilding_gold.png");
    gold->setPosition(ccp(195, 300));
    bkg->addChild(gold);
    goldlabel = CCLabelTTF::create("", "hycc.ttf", 18, CCSizeMake(150, 0), kCCTextAlignmentLeft);
    goldlabel->setAnchorPoint(ccp(0, 0.5));
    goldlabel->setPosition(ccp(215, 300));
    goldlabel->setColor(color2);
    bkg->addChild(goldlabel);
    
    CCSprite* wei = CCSprite::create("popbuilding_wei.png");
    wei->setPosition(ccp(80, 300));
    bkg->addChild(wei);
    weilabel = CCLabelTTF::create("", "hycc.ttf", 18, CCSizeMake(150, 0), kCCTextAlignmentLeft);
    weilabel->setAnchorPoint(ccp(0, 0.5));
    weilabel->setPosition(ccp(100, 300));
    weilabel->setColor(color2);
    bkg->addChild(weilabel);
    
    
    CCSprite* wu = CCSprite::create("popbuilding_wu.png");
    wu->setPosition(ccp(320, 300));
    bkg->addChild(wu);
    wulabel = CCLabelTTF::create("", "hycc.ttf", 18, CCSizeMake(250, 0), kCCTextAlignmentLeft);
    wulabel->setAnchorPoint(ccp(0, 0.5));
    wulabel->setPosition(ccp(340, 300));
    wulabel->setColor(color2);
    bkg->addChild(wulabel);
    
    
//    this->setTouchPriority((std::numeric_limits<int>::min()));
    
    
    return true;
}

void buildingpop::buzhen()
{
//    newBuZhen * sp = newBuZhen::create();
//    this->getParent()->addChild(sp);
    ((homePage*)(this->getParent()))->openNewBuZhen();
    this->removeFromParent();
}

void buildingpop::close(){
    this->hide();
}
//
void buildingpop::fight(){
    if(lock)
    {
        return;
    }
    lock = true;
    
    load=Loading::create();
    addChild(load,9999);
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    root["zjid"]= this->item->bid;
    
    CData::getCData()->battleCityId = this->item->bid;
    
    std::string json_file_zhandou=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file_zhandou.c_str(), 4501);
       this->schedule(schedule_selector(buildingpop::receiveFireData),0.2);
    
    
}

void buildingpop::receiveFireData(){
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(4501);
    CData::getCData()->m_dictionary->removeObjectForKey(4501);
    
    if(revMsg){
        
        this->unschedule(schedule_selector(buildingpop::receiveFireData));
       char* data=revMsg->data;
        CCLog("%s",data);
        
        Json::Reader read;
        Json::Value value;
        if(read.parse(data, value))
        {
            
            if (value["result"].asBool()) {
                
                CData::getCData()->setdata(data);
                CData::getCData()->setczorzy(true);
                CData::getCData()->battleCityId = this->item->bid;
            CCScene *scene=Fire::scene();
                
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
            load->removeFromParent();
                
            }
            else
            {
                CustomPop::show(value["message"].asString().c_str());
            }
            
            this->hide();
        }
        
        
        
        
        
        
//        CCLog("%s",data);
//        if(data){
//            CData::getCData()->setdata(data);
//            CData::getCData()->setczorzy(true);
//        
//            
//            
//            
//            CData::getCData()->battleCityId = this->item->bid;
//            CCScene *scene=Fire::scene();
//            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
//            
//
//            this->hide();
//        }
    }

}


void buildingpop::show(MapItem *item){
    lock = false;
    this->setVisible(true);
        this->item = item;
    
    
    
    char * json=CData::getCData()->cityData;
    Json::Reader read;
    Json::Value  root;
    Json::Value  data;
    
    
    if(read.parse(json, root))
    {
        data=root["data"];
    }
    
    
    int curCityID = data["cityid"].asInt();
    if (item->bid <= curCityID) {
        ft->setEnabled(true);
    }
    else
    {
        ft->setEnabled(false);
    }
    
    name->setString(item->nickname.c_str());
    namedesc->setString(item->desc.c_str());

    namedesc1->setString(item->enemydesc.c_str());
    CCLog("%s",namedesc1);
    char tmp[50]= "";
    sprintf(tmp, "钱 +%d",item->coin);
    goldlabel->setString(tmp);
    
    char tmp1[50]= "";
    sprintf(tmp1, "威 +%d",item->exp);
    weilabel->setString(tmp1);
    
    if (item->itemId == 0) {
        wulabel->setString("无掉落物品");
    }
    else
    {
        char tmp2[50]= "";
        configGoodsItem* gitem = CData::getCData()->getConfigOfGoods(item->itemId);
        sprintf(tmp2, "物 【%s】",gitem->name.c_str());
        wulabel->setString(tmp2);
    }
   
    
    
}
void buildingpop::hide()
{
    this->setVisible(false);
    this->removeAllChildren();
    this->getParent()->removeChild(this, true);
}

//void buildingpop::onExit()
//{
//    CCLog("buildingpop onExit");
//    
//    CCLayerColor::onExit();
//    
//}

buildingpop::~buildingpop()
{
    CCLog("buildingpop destroy");
}

void buildingpop::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}

bool buildingpop::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    istouch=btnsMenu->ccTouchBegan(touch, event);
    
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void buildingpop::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if(istouch){
        
        btnsMenu->ccTouchMoved(touch, event);
    }
}
void buildingpop::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    if (istouch) {
        btnsMenu->ccTouchEnded(touch, event);
        
        istouch=false;
        
    }
}

