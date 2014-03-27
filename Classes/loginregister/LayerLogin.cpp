#include "LayerLogin.h"
#include "homePage.h"
#include "json.h"
#include "SocketClient.h"
#include "message.h"
#include "MessageQueue.h"
#include "xuanren.h"
#include "zhuangtaiLoad.h"
#include "startAnimate.h"
#include "Singleton.h"
#include "AnimatePacker.h"
#include "SocketManager.h"
#include "CData.h"
#include "CustomPop.h"

#include "TestCpp.h"


bool LayerLogin::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    const char *bgMusic="bg.mp3";
    CData::getCData()->setyinyue(bgMusic);
    SocketManager::getInstance()->startSocket();
    loadRes();
    initUI();
    
    return true;
}

void LayerLogin::firefly()
{
    if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    {
        testOC * test=testOC::create();
        test->firefly();
    }
}

void LayerLogin::jiumiaoshanyou()
{
    if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    {
        testOC * test=testOC::create();
        test->initOc();
    }
}

void LayerLogin::initUI()
{
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bg = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_bkg.png"));
    bg->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
    this->addChild(bg);
    if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    {
        url1=CCMenuItemImage::create("ns-1.png", "ns-2.png", this, menu_selector(LayerLogin::jiumiaoshanyou));
        url1->setPosition(ccp(winSize.width-120, winSize.height-55));
        url2=CCMenuItemImage::create("ff-1.png", "ff-2.png", this, menu_selector(LayerLogin::firefly));
        url2->setPosition(ccp(winSize.width-45, winSize.height-55));
        CCMenu *urlMenu=CCMenu::create(url1,url2,NULL);
        urlMenu->setPosition(CCPointZero);
        urlMenu->setAnchorPoint(ccp(0,0));
        this->addChild(urlMenu);
    }
    else
    {
        url1=CCMenuItemImage::create("ns-1.png", "ns-2.png", this, menu_selector(LayerLogin::callNull1));
        url1->setPosition(ccp(winSize.width-120, winSize.height-55));
        url2=CCMenuItemImage::create("ff-1.png", "ff-2.png", this, menu_selector(LayerLogin::callNull2));
        url2->setPosition(ccp(winSize.width-45, winSize.height-55));
        CCMenu *urlMenu=CCMenu::create(url1,url2,NULL);
        urlMenu->setPosition(CCPointZero);
        urlMenu->setAnchorPoint(ccp(0,0));
        this->addChild(urlMenu);

    }
    this->zhenping();

    sendData=denglu1;

}

void LayerLogin::loadRes()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_login.plist");
}

void LayerLogin::callNull1()
{
    
}
void LayerLogin::callNull2()
{
    
}
void LayerLogin::zhenping(){
    pSpriteDialogLogin = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_input.png"));//CCSprite::create("login_bg_en.png");
    pSpriteDialogLogin->setPosition(ccp(winSize.width*0.5,winSize.height *0.5-100));
    this->addChild(pSpriteDialogLogin);
    CCMenuItemImage* btn_login = CCMenuItemImage::create();
    btn_login->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_login_1.png"));
    btn_login->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_login_2.png"));
    btn_login->setTarget(this, SEL_MenuHandler(&LayerLogin::menuItemCallbackLogin));
    CCLabelTTF *version=CCLabelTTF::create("V1.4", "hycc.ttf", 18);
    version->setColor(ccc3(28,42,52));
    version->setPosition(ccp(winSize.width*0.5,winSize.height *0.5-290));
    this->addChild(version);
    CCMenu *pMenu = CCMenu::create();
    pMenu->alignItemsHorizontally();
    pMenu->addChild(btn_login);
    //pMenu->setPosition(pSpriteDialogLogin->getContentSize().width-75,pSpriteDialogLogin->getContentSize().height/2-10);
    pMenu->setPosition(ccp(winSize.width/2-30, winSize.height/2-460));
    pMenu->setTouchPriority(1);
    pSpriteDialogLogin->addChild(pMenu);

    CCScale9Sprite* editbkg = CCScale9Sprite::create();
    
    editBoxUsername = CCEditBox::create(CCSizeMake(210,50),editbkg);
    editBoxUsername->setReturnType(kKeyboardReturnTypeDone);
    editBoxUsername->setFontSize(12);
    editBoxUsername->setText("");
    editBoxUsername->setFontColor(ccc3(158, 122, 83));
    editBoxUsername->setMaxLength(8);
    editBoxUsername->setPosition(ccp(winSize.width/2-10,96));//160,100
    pSpriteDialogLogin->addChild(editBoxUsername,2);
    
    CCScale9Sprite* editbkg1 = CCScale9Sprite::create();
    editBoxPassword = CCEditBox::create(CCSizeMake(190, 50),editbkg1);
    editBoxPassword->setReturnType(kKeyboardReturnTypeDone);
    editBoxPassword->setInputFlag(kEditBoxInputFlagPassword);
    editBoxPassword->setFontColor(ccc3(158, 122, 83));
    editBoxPassword->setMaxLength(8);
    editBoxPassword->setFontSize(8);
    editBoxPassword->setText("");
    editBoxPassword->setPosition(ccp(winSize.width/2-22,45));//160,60
    
    pSpriteDialogLogin->addChild(editBoxPassword,2);

}

void LayerLogin::onExit()
{
    CCLog("LayerLogin onExit");
    CCLayer::onExit();
}

LayerLogin::~LayerLogin()
{
    CCLog("LayerLogin destroy");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui_login.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("ui_login.png");
}

void LayerLogin::menuItemCallbackLogin(CCObject* pSender)
{
    if(strcmp(editBoxUsername->getText(), "")&&strcmp(editBoxPassword->getText(), ""))
    {
        const char  *  userName=editBoxUsername->getText();
        const char *   password=editBoxPassword->getText();
        int i=0,j=0,uIllegal=0,pIllegal=0;
        while((userName[i]!='\0'))
        {
            if((userName[i]>='0'&&userName[i]<='9')||(userName[i]>='a'&&userName[i]<='z')||(userName[i]>='A'&&userName[i]<='Z'))
            {
                i++;
                continue;
            }
            else
            {
                i++;
                uIllegal++;
            }
        }
        while(password[j]!='\0')
        {
            if((password[j]>='0'&&password[j]<='9')||(password[j]>='a'&&password[j]<='z')||(password[j]>='A'&&password[j]<='Z'))
            {
                j++;
                continue;
            }
            else
            {
                j++;
                pIllegal++;
            }
        }
        if(uIllegal>0||pIllegal>0)
        {
            CustomPop::show("用户名或密码包含非法字符!~");
        }
        else
        {
            load=Loading::create();
            addChild(load,9999);
            Json::FastWriter  writer;
            Json::Value person;
            person["username"]=userName;
            person["password"]=password;
            std::string  json_file=writer.write(person);
            CCLog("%s",json_file.c_str());
            SocketManager::getInstance()->sendMessage(json_file.c_str(), 101);
            this->schedule(schedule_selector(LayerLogin::receiveLoginData), 0.2);
        }
    }
    else
    {
        CustomPop::show("帐号或密码不能为空！~");
    }
}
void LayerLogin::receiveLoginData(){
    Message* revMsg2 = (Message *)CData::getCData()->m_dictionary->objectForKey(101);
    CData::getCData()->m_dictionary->removeObjectForKey(101);
    
    
    
    if(revMsg2){
        
        
        this->unschedule(schedule_selector(LayerLogin::receiveLoginData));
        
        char * denglu=revMsg2->data;
        CCLog("%s",denglu);
        CData::getCData()->setSendVal(denglu1);
        Json::Reader read;
        Json::Value root;
        bool result;
        Json::Value data;
        if(denglu){
            if (read.parse(denglu, root)) {
                Json::Value data=root["data"];
                std::string message=root["message"].asString();
                result=root["result"].asBool();
                if(result)
                {
                    CData::getCData()->setCharactorId(data["characterId"].asInt());
                    hasRole=data["hasRole"].asBool();
                    CData::getCData()->setUserId(data["userId"].asInt());
                    if(hasRole)
                    {
                        CData::getCData()->setfirstLogin(2);
                        this->schedule(schedule_selector(LayerLogin::sendPersonalData), 0.2);
                    }
                    else
                    {
                        CData::getCData()->setfirstLogin(1);
                        CCScene *scene=CCScene::create();
                        CCLayer *slayer=startAnimate::create();
                        scene->addChild(slayer);
                        load->removeFromParent();
                        CCDirector::sharedDirector()->replaceScene(scene);
                    }
                }
                else
                {
                    CustomPop::show(message.c_str());
                    load->removeFromParent();
                }
            }
        }
    }
}
void LayerLogin::sendPersonalData(){
    this->unschedule(schedule_selector(LayerLogin::sendPersonalData));
    
    this->schedule(schedule_selector(LayerLogin::receivePersonalData), 0.2);
    Json::FastWriter  write;
    
    Json::Value person1;
    
    person1["userId"]= CData::getCData()->getUserId();
    person1["characterId"]=CData::getCData()->getCharactorId();
    
    std::string  json_file1=write.write(person1);
    
    SocketManager::getInstance()->sendMessage(json_file1.c_str(), 103);
    
    
    Json::Value citymsg;
    citymsg["userId"] = CData::getCData()->getUserId();
    citymsg["characterId"] = CData::getCData()->getCharactorId();
    citymsg["index"] = 0;
    std::string json_file_city = write.write(citymsg);

    return;
    
    SocketManager::getInstance()->sendMessage(json_file_city.c_str(), 4500);
    
    
    this->schedule(schedule_selector(LayerLogin::receiveCityData), 0.2);
    
    
}

void LayerLogin::receiveCityData()
{
    
    Message* msg = (Message*)CData::getCData()->m_dictionary->objectForKey(4500);
    CData::getCData()->m_dictionary->removeObjectForKey(4500);
    if(msg)
    {
        this->unschedule(schedule_selector(LayerLogin::receiveCityData));
        CData::getCData()->cityData = msg->data;
        printf("%s\n",CData::getCData()->cityData);
        
        this->schedule(schedule_selector(LayerLogin::receivePersonalData), 0.2);
    }
    
}


void LayerLogin::receivePersonalData(){
    
    Message* revMsg1 = (Message *)CData::getCData()->m_dictionary->objectForKey(103);
    CData::getCData()->m_dictionary->removeObjectForKey(103);
    if(revMsg1){
        this->unschedule(schedule_selector(LayerLogin::receivePersonalData));
        denglu1=revMsg1->data;
        CData::getCData()->setSendVal(denglu1);
        printf("------%s\n",denglu1);
        pSpriteDialogLogin->removeFromParent();
        url1->setVisible(false);
        url2->setVisible(false);
        load->removeFromParent();
        
        CCMenuItemImage *pMenuItemStart = CCMenuItemImage::create();
        pMenuItemStart->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_start_1.png"));
        pMenuItemStart->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_start_2.png"));
        pMenuItemStart->setTarget(this, SEL_MenuHandler(&LayerLogin::menuItemCallbackStart));
        CCMenu *pMenu = CCMenu::create(pMenuItemStart,NULL);
        this->addChild(pMenu,2);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        pMenu->setPosition(winSize.width/2, 180);
        
    }
}
void LayerLogin::removeLoader(){
}


void LayerLogin::menuItemCallbackStart(CCObject *pSender)
{   
    CCLog("start");
    
    CCScene *container=CCScene::create();//homepage  beginAni
    homePage * homePage = homePage::create();
    container->addChild(homePage);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, container));

    
}
void LayerLogin::menuItemCallbackSelector(CCObject *pSender)
{
    
}

