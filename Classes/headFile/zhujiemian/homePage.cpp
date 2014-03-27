#include "homePage.h"
#include "CCScrollView.h"
#include "zhuangtaiLoad.h"
#include "json.h"
#include "LayerLogin.h"
#include "SocketManager.h"
#include "CustomPop.h"

void homePage::onExit()
{
    CCLog("homePage onExit");
    CCLayer::onExit();
}

homePage::~homePage(){
    
    CCLog("homePage destroy");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}
bool homePage::init(){
    if(!CCLayer::init()){
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    
    load=Loading::create();
    this->addChild(load,9999);
    
    int characterId=CData::getCData()->getCharactorId();
    CCLog("%d",characterId);
    Json::FastWriter writer;
    Json::Value sendMessage;
    sendMessage["characterId"]=characterId;
    sendMessage["index"]=0;
    std::string json_file_jianghu=writer.write(sendMessage);
    CCLog("%s",json_file_jianghu.c_str());
    SocketManager::getInstance()->sendMessage(json_file_jianghu.c_str(), 4500);
    this->schedule(schedule_selector(homePage::rec_4500));
    
    
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    
    
       return true;
}
void homePage::initTitle(){

}

//加载中部地图
void homePage::btnsLoading(){
        
        layerMainMap= LevelMap::create();//  Btns::create();
        layerMainMap->setAnchorPoint(ccp(0, 0));
        this->addChild(layerMainMap,0);
        
}
void homePage::zhuangtaiLoad(){
    zhuangtai1 =zhuangtai::create();
    zhuangtai1->setVisible(true);
    zhuangtai1->setPosition(ccp(0, size.height-100));
    this->addChild(zhuangtai1,1);
    
}

void homePage::openPersonal()
{

    this->removelayers();
    btnEmployFriends->setVisible(false);
    btnHeCheng->setVisible(false);
    layerPersonInfo = personalinfo::create();
    this->addChild(layerPersonInfo);
    

}

void homePage::removelayers()
{
    this->removeChild(layerMainMap, true);
    this->removeChild(layerPersonInfo);
    this->removeChild(layerNewBuZhen);
    this->removeChild(compound);
    this->removeChild(layerMail);
    //this->removeChild(rechargeLayer);
    this->removeChild(layerFriend);
}

void homePage::openArenaWindow()
{
    //CustomPop::show("敬请期待");
    this->removelayers();
    btnEmployFriends->setVisible(false);
    btnHeCheng->setVisible(false);
    layerArena = ArenaWindow::create();
    this->addChild(layerArena);

}

void homePage::openMailWindow()
{
    this->removelayers();
    btnEmployFriends->setVisible(false);
    btnHeCheng->setVisible(false);
    layerMail = MailWindow::create();
    this->addChild(layerMail);

    //CustomPop::show("敬请期待");

}

void homePage::employFriends()
{
    this->removelayers();
    btnEmployFriends->setVisible(false);
    btnHeCheng->setVisible(false);
    layerFriend=friendmain::create();
    this->addChild(layerFriend);
    //CustomPop::show("敬请期待");
}

void homePage::recharge()
{
    //this->removelayers();
    //btnEmployFriends->setVisible(false);
    //btnHeCheng->setVisible(false);
    //rechargeLayer=Recharge::create();
    //this->addChild(rechargeLayer);
    CustomPop::show("尚未开通");
}

//下部功能按钮
void homePage::downBtnLoading(){
    
    btnHeCheng = CCMenuItemImage::create("zjm_hc_1.png", "zjm_hc_2.png", this, menu_selector(homePage::openHeCheng));
    btnHeCheng->setPosition(ccp(70, size.height-165));
    
    btnEmployFriends = CCMenuItemImage::create("zjm_employfriends_1.png", "zjm_employfriends_2.png", this, menu_selector(homePage::employFriends));
    btnEmployFriends->setPosition(ccp(size.width-60, size.height-165));
    
    CCMenuItemImage *btnPersonal = CCMenuItemImage::create("zjm_personal_1.png", "zjm_personal_1.png", this, menu_selector(homePage::openPersonal));
    btnPersonal->setAnchorPoint(ccp(0.5, 0.5));
    btnPersonal->setPosition(ccp(size.width/2, 733));

    linkFecharge = CCMenuItemImage::create("zjm_linkrecharge_1.png", "zjm_linkrecharge_2.png", this, menu_selector(homePage::recharge));
    linkFecharge->setAnchorPoint(ccp(0, 0));
    linkFecharge->setPosition(ccp(50, 25));
    
    btnMail = CCMenuItemImage::create("zjm_mail_1.png", "zjm_mail_2.png", this, menu_selector(homePage::openMailWindow));
    btnMail->setAnchorPoint(ccp(0, 0));
    btnMail->setPosition(ccp(150, 25));
    
    btnArena = CCMenuItemImage::create("zjm_arena_1.png", "zjm_arena_2.png", this, menu_selector(homePage::openArenaWindow));
    btnArena->setAnchorPoint(ccp(0, 0));
    btnArena->setPosition(ccp(240, 25));
    
    
    homeLink = CCMenuItemImage::create("zjm_linkhome_1.png", "zjm_linkhome_2.png", this, menu_selector(homePage::mainView));
    homeLink->setAnchorPoint(ccp(1, 0));
    homeLink->setPosition(ccp(size.width-45,25));
    
    
    menu=CCMenu::create(btnHeCheng,btnEmployFriends,btnPersonal,linkFecharge,homeLink,btnMail,btnArena,NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));

    this->addChild(menu,6,1878);
    
}
void homePage::mainView(){

   
    this->removelayers();
    btnEmployFriends->setVisible(true);
    btnHeCheng->setVisible(true);
    layerMainMap= LevelMap::create();//  Btns::create();
    layerMainMap->setAnchorPoint(ccp(0, 0));
    this->addChild(layerMainMap,0);
    
    CData::getCData()->setyinxiao();
     zhuangtai1->upData();
    
    
}

void homePage::openNewBuZhen()
{
    this->removelayers();
    btnEmployFriends->setVisible(false);
    btnHeCheng->setVisible(false);
    layerNewBuZhen = newBuZhen::create();
    this->addChild(layerNewBuZhen);
}



void homePage::openHeCheng(){
    //CustomPop::show("敬请期待");
    this->removelayers();
    btnEmployFriends->setVisible(false);
    btnHeCheng->setVisible(false);
    compound=CHecheng::create();
    this->addChild(compound);
}


void homePage::rec_4500()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(4500);
    CCLog("%s",revMsg);
    CData::getCData()->m_dictionary->removeObjectForKey(4500);
    
    if(revMsg)
    {
        this->unschedule(schedule_selector(homePage::rec_4500));//删除刷新
        CData::getCData()->cityData = revMsg->data;
        CCLog("%s",revMsg->data);
        load->removeFromParent();
        
        this->initTitle();//加载标题
        this->btnsLoading();//加载中部按钮
        this->zhuangtaiLoad();//加载状态栏
        this->downBtnLoading();//加载底部按钮
        
       zhuangtai1->upData();
        
       if (CData::getCData()->isArenaFire) {
              this->openArenaWindow();
          }

        
        
    }

}


