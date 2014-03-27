#include "xuanren.h"
#include "homePage.h"
#include "LayerLogin.h"
#include "SocketManager.h"
#include "CustomPop.h"
#include "message.h"
bool xuanren::init(){
    if(!CCLayer::init()){
        return false;
    }
    
    CCLog("xuanren---------------------------0");
    flag=0;
    size=CCDirector::sharedDirector()->getWinSize();
    CCSprite *backGround=CCSprite::create("selectrole_bkg.png");
    backGround->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(backGround);
    CCSprite *  kuang=CCSprite::create("common_item_bkg.png");
    kuang->setScale(1);
    kuang->setTag(9002);
//    kuang->setAnchorPoint(ccp(0, 0));
    selectBtn=CCMenuItemImage::create("common_btn_ok_1.png", "common_btn_ok_2.png", "common_btn_ok_3.png",this, menu_selector(xuanren::EnterName));
    selectBtn->setScale(1.3);
    CCMenu *selectMenu=CCMenu::create(selectBtn,NULL);
    selectMenu->setPosition(ccp(size.width/2, 100));
    this->addChild(selectMenu,1);

     CCLog("xuanren---------------------------1");
    
    jieshao=CCLabelTTF::create("", "hycc.ttf", 23, CCSizeMake(450,58),kCCTextAlignmentCenter);
    jieshao->setColor(ccc3(134,105,59));
    jieshao->setAnchorPoint(ccp(0, 0));
    jieshao->setPosition(ccp(50, 245));//原始375
    jieshao->setDimensions(CCSizeMake(300, 0));
    jieshao->setHorizontalAlignment(kCCTextAlignmentLeft);
    jieshao->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    this->addChild(jieshao,1);
    mingcheng=CCLabelTTF::create("第三方","hycc.ttf" , 40, CCSizeMake(120,40), kCCTextAlignmentLeft);
    mingcheng->setPosition(ccp(80, 905));//原始275
    //this->addChild(mingcheng,1);
    jineng=CCLabelTTF::create("技能：啊啊", "hycc.ttf", 25,CCSizeMake(135,25), kCCTextAlignmentLeft);
    jineng->setPosition(ccp(85, 860));//原始280
    //this->addChild(jineng,1);
    mingcheng=CCLabelTTF::create("第三方","hycc.ttf" , 40, CCSizeMake(110,40), kCCTextAlignmentLeft);
    btn1=CCMenuItemImage::create("common_item_bkg1.png", "common_item_bkg1.png", this, menu_selector(xuanren::FirstPerson));
    CCSize btnSize=btn1->getContentSize();
    btn1->setScale(1.0);
    CCSprite* btnsp1 = CCSprite::create("qs_0001.png");
    btnsp1->setScale(0.18);
    btnsp1->setAnchorPoint(ccp(0.5,0.5));
    //btnsp1->setPosition(ccp(0,0));
    btn1->addChild(btnsp1);
    btnsp1->setPosition(ccp(btnSize.width/2, btnSize.height/2));
    btn2=CCMenuItemImage::create("common_item_bkg1.png", "common_item_bkg1.png", this, menu_selector(xuanren::SecondPerson));
    btn2->setScale(1.0);
    
    CCSprite* btnsp2 = CCSprite::create("qs_0002.png");
    btnsp2->setScale(0.18);
    btnsp2->setAnchorPoint(ccp(0.5,0.5));
    btn2->addChild(btnsp2);
    btnsp2->setPosition(ccp(btnSize.width/2, btnSize.height/2));
    btn3=CCMenuItemImage::create("common_item_bkg1.png", "common_item_bkg1.png", this, menu_selector(xuanren::ThridPerson));
    btn3->setScale(1.0);
    
    CCSprite* btnsp3 = CCSprite::create("qs_0003.png");
    btnsp3->setScale(0.18);
    btnsp3->setAnchorPoint(ccp(0.5,0.5));
    btn3->addChild(btnsp3);
    btnsp3->setPosition(ccp(btnSize.width/2, btnSize.height/2));
    CCMenu *menu=CCMenu::create(btn1,btn2,btn3,NULL);
    menu->alignItemsHorizontallyWithPadding(30);
    menu->setPosition(ccp(size.width/2, size.height/2-218));//原始92    548 660
    this->addChild(menu);
    
    
    renwu=CCSprite::create();
    renwu->setPosition(ccp(size.width/2, size.height/2+100));//原始380
    this->addChild(renwu);
     CCLog("xuanren---------------------------3");
    
    FirstPerson();
    
    return true;
    
}
CCScene * xuanren::scene(){
    CCScene *scene=CCScene::create();
    xuanren *xr=xuanren::create();
    scene->addChild(xr);
    return scene;
}

void xuanren::FirstPerson(){
    if(flag!=1){
        jieshao->setString("齐天大圣：武僧，拥有高生命高防御");
        CCSprite * kuang3=CCSprite::create("common_item_bkg.png");
        kuang3->setScale(1);
        kuang3->setTag(9002);
        btn2->removeChildByTag(9003);
        btn3->removeChildByTag(9004);
        CCSize sz = btn1->getContentSize();
        kuang3->setPosition(ccp(sz.width/2, sz.height/2));
        btn1->addChild(kuang3,1);
        flag=1;
        renwu->initWithFile("qs_0001.png");
    }
 CCLog("xuanren---------------------------4");
    
}
void xuanren::SecondPerson(){
    
    if(flag!=2){
        jieshao->setString("蛮族之王：狂战士，拥有高攻击");
       CCSprite * kuang1=CCSprite::create("common_item_bkg.png");
        kuang1->setScale(1);
//        kuang1->setAnchorPoint(ccp(0, 0));
        kuang1->setTag(9003);
        btn1->removeChildByTag(9002);
        btn3->removeChildByTag(9004);
        CCSize sz = btn1->getContentSize();
        kuang1->setPosition(ccp(sz.width/2, sz.height/2));
        btn2->addChild(kuang1,1);
        flag=2;
        renwu->initWithFile("qs_0002.png");
    }

    
}
void xuanren::ThridPerson(){

    if(flag!=3){
        jieshao->setString("恶魔统帅：术士，拥有高速度，可先手攻击");
        CCSprite * kuang1=CCSprite::create("common_item_bkg.png");
        kuang1->setScale(1);
//        kuang1->setAnchorPoint(ccp(0, 0));
        kuang1->setTag(9004);
        btn1->removeChildByTag(9002);
        btn2->removeChildByTag(9003);
        CCSize sz = btn1->getContentSize();
        kuang1->setPosition(ccp(sz.width/2, sz.height/2));
        btn3->addChild(kuang1,1);
        flag=3;
        renwu->initWithFile("qs_0003.png");
    }

    
}

void xuanren::onExit()
{
    CCLog("xuanren onExit");
}

xuanren::~xuanren()
{
    
    CCLog("xuanren destroy");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("selectrole_bkg.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("common_pop_text_bkg.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("qs_0001.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("qs_0002.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("qs_0003.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("common_pop_bkg.png");
}

void xuanren::EnterName(){
    
    CCSprite * TCK=CCSprite::create("common_pop_bkg.png");
    CCSize tmpsz = TCK->getContentSize();
    TCK->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(TCK,3);
    CCLabelTTF * nameLabel=CCLabelTTF::create("主 角 名 称", "hzgb.ttf", 25);
    nameLabel->setPosition(ccp(tmpsz.width/2+1, tmpsz.height-39));
    nameLabel->setColor(ccc3(27, 18, 6));
    TCK->addChild(nameLabel,6);
    CCLabelTTF * nameLabel1=CCLabelTTF::create("主 角 名 称", "hzgb.ttf", 25);
    nameLabel1->setPosition(ccp(tmpsz.width/2, tmpsz.height-38));
    nameLabel1->setColor(ccc3(236, 190, 108));
    TCK->addChild(nameLabel1,6);

       enterUsrName=CCEditBox::create(CCSizeMake(367, 60), CCScale9Sprite::create("common_pop_text_bkg.png"));
    enterUsrName->setReturnType(kKeyboardReturnTypeDone);
    enterUsrName->setText("");
    enterUsrName->setMaxLength(8);
    enterUsrName->setFontColor(ccc3(10, 10, 0));
       TCK->addChild(enterUsrName,4);
    enterUsrName->setPosition(ccp(tmpsz.width/2, tmpsz.height/2));
//    CCLabelTTF * surename=CCLabelTTF::create("确  定", "Marker Felt", 35);
//    surename->setAnchorPoint(ccp(0, 0));
//    surename->setPosition(ccp(35, 20));
//    CCLabelTTF * reloadname=CCLabelTTF::create("重  置", "Marker Felt", 25);
//    reloadname->setAnchorPoint(ccp(0, 0));
//    reloadname->setPosition(ccp(43, 20));
    CCMenuItemImage * sure=CCMenuItemImage::create("common_btn_ok_1.png", "common_btn_ok_2.png", "common_btn_ok_3.png", this, menu_selector(xuanren::replacScene));
    sure->setScale(1.3);
//    sure->setPosition(ccp(0, 0));//-120
//    sure->addChild(surename,1);
//    CCMenuItemImage * reload=CCMenuItemImage::create("pk-04.png", "pk-03.png", this, menu_selector(xuanren::reloadUsrName));
//    reload->setPosition(ccp(120, 0));
//    reload->addChild(reloadname,1);
    CCMenu * menu=CCMenu::create(sure,NULL);
    menu->setPosition(ccp(size.width/2, 70));
    TCK->addChild(menu,4);
}
void xuanren::reloadUsrName(){
    enterUsrName->setText("");
}
void xuanren::replacScene(){
    if(strcmp(enterUsrName->getText(),""))
    {
    load=Loading::create();
    this->addChild(load,9999);
    
    Json::FastWriter  writer;
    Json::Value person;
    person["rolename"]=enterUsrName->getText();
    person["profession"]=flag;
    
    std::string  json_file=writer.write(person);
   
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 102);
    
    
    this->schedule(schedule_selector(xuanren::receiveRoleInfo),0.2);
    }
    else
    {
        CustomPop::show("名称不能为空");
        //load->removeFromParent();
    }

}
void xuanren::receiveRoleInfo(){
    Message * recRoleMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(102);
    CData::getCData()->m_dictionary->removeObjectForKey(102);
    
    if(recRoleMsg){
//        this->removeChild(load);
        char * datastr=recRoleMsg->data;
        printf("%s\n",datastr);
        Json::Reader read;
        Json::Value root;
        Json::Value data;
        int characterId;
       const char * message="";
        bool result;
        if(datastr){
            this->unschedule(schedule_selector( xuanren::receiveRoleInfo));
            if (read.parse(datastr, root)) {
                Json::Value data=root["data"];
                characterId=data["newCharacterId"].asInt();
                CData::getCData()->setCharactorId(characterId);
                
                result=root["result"].asBool();
                message=root["message"].asString().c_str();
                if(result){
                    
                    this->schedule(schedule_selector(xuanren::receiveHomeInfo), 0.2);
                    
                    Json::FastWriter  write;
                    
                    Json::Value person1;
                    
                    person1["userId"]=CData::getCData()->getUserId();
                    person1["characterId"]=characterId;
                    
                    std::string  json_file1=write.write(person1);
                         
                    SocketManager::getInstance()->sendMessage(json_file1.c_str(), 103);
                    
                    
                    
                }
                else{
                    CustomPop::show("用户名已经拥有了！~");
                    load->removeFromParent();
                }
                
            }
        }else{
        }

    }
    
}

void xuanren::receiveCityData()
{
    Message* msg = (Message*)CData::getCData()->m_dictionary->objectForKey(4500);
    CData::getCData()->m_dictionary->removeObjectForKey(4500);
    if(msg)
    {
        this->unschedule(schedule_selector(xuanren::receiveCityData));
        
        //        {"message": "", "data": {"cityid": 1000, "citylist": []}, "result": true}
        CData::getCData()->cityData = msg->data;
        printf("%s\n",CData::getCData()->cityData);
        
        
        this->schedule(schedule_selector(xuanren::receiveHomeInfo), 0.2);
    }

}


void xuanren::receiveHomeInfo(){
    Message * recRoleMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(103);
    CData::getCData()->m_dictionary->removeObjectForKey(103);
    
    if(recRoleMsg)
    {
        this->removeChild(load);
        this->unschedule(schedule_selector(xuanren::receiveHomeInfo));
        char * data=recRoleMsg->data;
        CData::getCData()->setSendVal(data);
        this->enterHomePage();
    }
    
}
void xuanren::enterHomePage(){
    this->removeChild(load);
    this->removeAllChildren();
    CCScene *homePage=CCScene::create();//homepage  beginAni
    homePage->addChild(homePage::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(2,homePage));

}