#include "zhuangtaiLoad.h"
#include "json.h"
#include "LayerLogin.h"
#include "CData.h"
#include "homePage.h"
#include "SocketManager.h"

void zhuangtai::send_103()
{
    
    this->schedule(schedule_selector(zhuangtai::rec_103));
    Json::FastWriter  write;
    
    Json::Value person1;
    
    person1["userId"]= CData::getCData()->getUserId();
    person1["characterId"]=CData::getCData()->getCharactorId();
    
    std::string  json_file1=write.write(person1);
    
    SocketManager::getInstance()->sendMessage(json_file1.c_str(), 103);
}

void zhuangtai::rec_103()
{
    Message* revMsg1 = (Message *)CData::getCData()->m_dictionary->objectForKey(103);
    CData::getCData()->m_dictionary->removeObjectForKey(103);
    if(revMsg1){
        this->unschedule(schedule_selector(zhuangtai::rec_103));
        CData::getCData()->setSendVal(revMsg1->data);
        Json::Reader reader;
        Json::Value root;
        Json::Value data;
        if(reader.parse(revMsg1->data, root)){
            data=root["data"];
            gold=data["yuanbao"].asInt();
            coin=data["coin"].asInt();
            level=data["level"].asInt();
            maxExp=data["maxexp"].asInt();
            Exp=data["exp"].asInt();
            gas= 0;//data["gas"].asInt();
            power=data["gas"].asInt();
            this->setCoin(coin);
            
            CData::getCData()->setSendVal(revMsg1->data);
            //__coin=coin;
        }
        CCLog("%s",revMsg1->data);
        char goldNum[5]="";
        sprintf(goldNum, "%d",gold);
        _goldLabel->setString(goldNum);
        
        char agNum[5]="";
        sprintf(agNum, "%d",coin);
        _ag->setString(agNum);
        
        char gasNum[5]="";
        sprintf(gasNum, "%d",gas);
        _qi->setString(gasNum);
        
        char levelNum[20]="";
        sprintf(levelNum, "%d",level);
        
        levelLabel->setString(levelNum);
        char tiNum[20]="";
        sprintf(tiNum, "%d",power);

    }
}

bool zhuangtai::init()
{
    
    if(!CCLayer::init()){
        return false;
    }

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(zhuangtai::upData), "refresh_zhuangtai", NULL);

    
    
    char * json=CData::getCData()->getSendVal();
    CCLog("%s",json);
    Json::Reader read;
    Json::Value  root;
    Json::Value  data;
    
//    int characterId;
    
    if(read.parse(json, root)){
        data=root["data"];
        coin=data["coin"].asInt();//货币
        __coin=coin;
        gold=data["yuanbao"].asInt();//金子、
        level=data["level"].asInt();//等级
        Exp=data["exp"].asInt();//当前经验
        maxExp=data["maxexp"].asInt();//最大经验
        gas=data["gas"].asInt();//气
        power=data["gas"].asInt();//力量
        vipNum=data["vip"].asInt();
        _gid=data["gid"].asInt();
        CData::getCData()->setSZnum(level);
        this->setGid(_gid);
        CData::getCData()->setcoin(coin);
        CData::getCData()->setgold(gold);
        CData::getCData()->setExp(Exp);
        CData::getCData()->setLevel(level);
        CData::getCData()->setMaxExp(maxExp);
        rolename=data["name"].asString();
//        characterId=data["characterId"].asInt();
    }
    icoin<<coin;
    igold<<gold;
    ilevel<<level;
    this->zhuangtaiInit();
    
    return true;

}

void zhuangtai::setGid(int gid){
    _gid=gid;
}
int zhuangtai::getGid(){
    return _gid;
}
void zhuangtai::reload(){
    
}

void zhuangtai::clkHomeLink()
{
    
}

void zhuangtai::clkLinkRecharge()
{
    
}

void zhuangtai::zhuangtaiInit(){
    
    char coinn[15]="";
    char levell[15]="";
    char goldd[15]="";
    char tili[15]="";
    char powerNow[15]="";
    sprintf(coinn, "%d",coin);
    sprintf(levell, "%d",level);
    sprintf(goldd, "%d",gold);
    sprintf(tili, "%d",power);
    sprintf(powerNow, "%d",gas);
    
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* status = CCSprite::create("zt_bkg.png");
    status->setAnchorPoint(ccp(0.5, 0));
    status->setPosition(ccp(size.width/2, -14));
    this->addChild(status);
    
    this->setContentSize(status->getContentSize());
    
//    this->setContentSize(CCSizeMake(640, 78));
    this->initWithColor(ccc4(100, 100, 100, 25));
    char vipsNum[40]="";
    if (vipNum>=1&&vipNum<=9){
        sprintf(vipsNum, "vip%d.png",vipNum);
        CCSprite * vip=CCSprite::create(vipsNum);
        vip->setAnchorPoint(ccp(0, 0));
        vip->setPosition(ccp(160, 45));
            status->addChild(vip,2);
    }
    
    ccColor3B black = ccc3(222,173,98);//244,164,96
    //ccColor3B white = ccc3(180,180,70);
    
    
    nameLabel=CCLabelTTF::create(rolename.c_str(), "hycc.ttf", 18);//Thonburi
    nameLabel->setColor(black);
   
    nameLabel->setAnchorPoint(ccp(0.5,0.5));
    nameLabel->setPosition(ccp(125, 50));//60
    _exp=CCSprite::create("zt_exp_bar.png");//经验值
    _exp->setAnchorPoint(ccp(0, 0));
    _exp->setPosition(ccp(80, 20));//90  47
    _exp->setScaleX((float)Exp/maxExp);
    
    
    //ccColor3B lvcolor = ccc3(180,180,70);
    levelLabel=CCLabelTTF::create(levell, "hycc.ttf", 24);//等级数字
    levelLabel->setColor(black);
    levelLabel->setPosition(ccp(40, 50));//36 36
    levelLabel->setAnchorPoint(ccp(0.5, 0.5));
    
    _goldLabel=CCLabelTTF::create(goldd, "hycc.ttf", 16);//金子Thonburi
    _goldLabel->setPosition(ccp(220, 53));
    _goldLabel->setAnchorPoint(ccp(0, 0));
    _goldLabel->setColor(black);
    _goldLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    
    _ag=CCLabelTTF::create(coinn, "hycc.ttf", 16);//银子
    _ag->setPosition(ccp(220, 17));
    _ag->setAnchorPoint(ccp(0, 0));
    _ag->setColor(black);
    _ag->setHorizontalAlignment(kCCTextAlignmentLeft);
    _ti=CCLabelTTF::create(tili, "hycc.ttf", 16);//体力
    _ti->setPosition(ccp(340, 53));
    _ti->setAnchorPoint(ccp(0, 0));
    _ti->setColor(black);
    _ti->setHorizontalAlignment(kCCTextAlignmentLeft);
    _qi=CCLabelTTF::create(powerNow, "hycc.ttf", 16);//气
    _qi->setPosition(ccp(340, 17));
    _qi->setAnchorPoint(ccp(0, 0));
    _qi->setColor(black);
    _qi->setHorizontalAlignment(kCCTextAlignmentLeft);
    
    status->addChild(nameLabel,3);
    status->addChild(_qi,2);
    status->addChild(_ti,2);
    status->addChild(_ag,2);
    status->addChild(_goldLabel,2);
    status->addChild(levelLabel);
//    status->addChild(level,3);
    status->addChild(_exp,2);
    
    
//    this->addChild(backGrounds);
    
//    initData();
    
}

void zhuangtai::initData()
{
    
    
    
}

void zhuangtai::sendZGBagInfo(){
    load=Loading::create();
    load->setPosition(ccp(0, -760));
    this->addChild(load,9999);
   
    int characterId=CData::getCData()->getCharactorId();
    Json::FastWriter writer;
    Json::Value sendMessage;
    sendMessage["characterId"]=characterId;
    std::string json_file_zg=writer.write(sendMessage);
    
    SocketManager::getInstance()->sendMessage(json_file_zg.c_str(), 203);
    
    this->schedule(schedule_selector(zhuangtai::receiveZGBagInfo),0.5);
    
}
void zhuangtai::receiveZGBagInfo(){
    
}


void zhuangtai::removeB(){
    CData::getCData()->setyinxiao();

    this->removeChild(backGround, true);
}

int zhuangtai::getGas(){
    return gas;
}
int zhuangtai::getMaxExp(){
    return maxExp;
}
int zhuangtai::getExp(){
    return Exp;
}
int zhuangtai::getPower(){
    return power;
}
int zhuangtai::getGold(){
    return gold;
}
void zhuangtai::setCoin(int coin){
    __coin=coin;
}
int zhuangtai::getcoin(){
    return __coin;
}
void zhuangtai::upData(){
//    int a=CData::getCData()->getfirstLogin();
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    
    Json::FastWriter  write;
    
    Json::Value person1;
    

    person1["characterId"]=CData::getCData()->getCharactorId();
    
    std::string  json_file1=write.write(person1);

    SocketManager::getInstance()->sendMessage(json_file1.c_str(), 105);
    this->schedule(schedule_selector(zhuangtai::receiveUpdata), 0.2);
    
    
    
    
    
   
    
    
}
void  zhuangtai::receiveUpdata(){
    
    Message* revMsg1 = (Message *)CData::getCData()->m_dictionary->objectForKey(105);
    CData::getCData()->m_dictionary->removeObjectForKey(105);
    if(revMsg1){
        
        this->unschedule(schedule_selector(zhuangtai::receiveUpdata));
        Json::Reader reader;
        Json::Value root;
        Json::Value data;
        if(reader.parse(revMsg1->data, root)){
            data=root["data"];
            gold=data["gold"].asInt();
            coin=data["coin"].asInt();
            level=data["level"].asInt();
            maxExp=data["maxexp"].asInt();
            Exp=data["exp"].asInt();
            gas= 0;//data["gas"].asInt();
            power=data["huoli"].asInt();
            this->setCoin(coin);
           
            CData::getCData()->setSendVal(revMsg1->data);
            //__coin=coin;
        }
        CCLog("%s",revMsg1->data);
        char goldNum[5]="";
        sprintf(goldNum, "%d",gold);
        _goldLabel->setString(goldNum);
        
        char agNum[5]="";
        sprintf(agNum, "%d",coin);
        _ag->setString(agNum);
        
        char gasNum[5]="";
        sprintf(gasNum, "%d",gas);
        _qi->setString(gasNum);
        
        char levelNum[20]="";
        sprintf(levelNum, "%d",level);
        
        levelLabel->setString(levelNum);
        char tiNum[20]="";
        sprintf(tiNum, "%d",power);
        _ti->setString(tiNum);
        
        nameLabel->setString(data["rolename"].asString().c_str());
        
        
    }
   
}


void zhuangtai::onExit()
{
    CCLog("zhuangtai onExit");
    CCLayerColor::onExit();
}

zhuangtai::~zhuangtai()
{
    CCLog("zhuangtai destroy");
     CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "refresh_zhuangtai");
}



