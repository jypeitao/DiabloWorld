#include "FireWork.h"
#include "json.h"

#include "TeXiao.h"
#include "GameOver.h"
#include "AnimatePacker.h"
#include "Singleton.h"
#include "SocketManager.h"
#include "CustomPop.h"

#define Time 2.5f
static Fire * g_config=NULL;
static int moreene[9]={0};
static int skillnumbers[20]={0};


bool Fire::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    
    size=CCDirector::sharedDirector()->getWinSize();
    
    CCSprite * background=CCSprite::create("firework_bkg.png");
    background->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(background,-2);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bg2.mp3");
    initFireData();
    
    return true;
    
}


void Fire::initFireData()
{   
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("jn_name.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("begin1.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("result_attacked.plist");
    
    label1=CCLabelTTF::create("", "Marker Felt", 30, CCSizeMake(200,40), kCCTextAlignmentLeft);
    label1->setColor(ccc3(0, 0, 255));
    label1->setPosition(ccp(520, 500));
    this->addChild(label1,5);
    label2=CCLabelTTF::create("", "Marker Felt", 30, CCSizeMake(200,40), kCCTextAlignmentLeft);
    label2->setColor(ccc3(0, 0, 255));
    label2->setPosition(ccp(520, 460));
    this->addChild(label2,5);
    label3=CCLabelTTF::create("", "Marker Felt", 30, CCSizeMake(200,40), kCCTextAlignmentLeft);
    label3->setColor(ccc3(0, 0, 255));
    label3->setPosition(ccp(520, 420));
    this->addChild(label3,5);
    ene_dic=CCDictionary::create();
    ene_dic->retain();
    player_dic=CCDictionary::create();
    player_dic->retain();
    AnimatePacker :: getInstance()->loadAnimations("qishouTX.xml");
    jn_dic=CCDictionary::create();
    jn_dic->retain();
    buff1=CCSprite::create("tjbgbuff.png");
    buff1->setPosition(ccp(320, 260));
    buff1->setVisible(false);
    this->addChild(buff1);
    buff2=CCSprite::create("xsjbuff.png");
    buff2->setPosition(ccp(320, 260));
    buff2->setVisible(false);
    this->addChild(buff2);
    buff3=CCSprite::create("yszsbuff.png");
    buff3->setPosition(ccp(320, 260));
    buff3->setVisible(false);
    this->addChild(buff3);
    setTouchEnabled(true);
    first=false;
    kaishi=0;
    sk=new skillList();
    
    chat_dic=CCDictionary::create();
    chat_dic->retain();
    
    rounds=0;
    
    CCLog("*********___________----------");
    
    char * data2=CData::getCData()->getdata();
    //CCLog("%s",data2);
    Json::Reader read;
    Json::Value root;
    Json::Value data;
    Json::Value stepdata;
    int skill;
    int eee=0;
    if(read.parse(data2, root)){
        data=root["data"];
        stepdata=data["stepData"];
        for (int i=0; i<stepdata.size(); i++) {
            CCLog("@");
            skill=stepdata[i]["skill"].asInt();
            if(skill!=610101){
                
                
                for(int j=0;j<20;j++){
                    
                    
                    if(skillnumbers[j]==skill){
                        break;
                        
                    }else{
                        if(skillnumbers[j]==0){
                            
                            skillnumbers[eee]=skill;
                            eee++;
                            break;
                        }
                    }
                    
                }
            }
        }
        
    }
    for(int i=0;i<20;i++){
        if(skillnumbers[i]!=0){
            const char * texiaoname=sk->skills(skillnumbers[i]);
            char names[40]="";
            sprintf(names, "%s.xml",texiaoname);
            CCLog("%s",names);
            AnimatePacker::getInstance()->loadAnimations(names);
        }
    }
    
    bool flaag=false;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg2.mp3", true);
    
    this->getJsonData(data2);
    
    }

Fire *Fire::getInstance()
{
    Fire *fireInstance=new Fire();
    return fireInstance;
}
int Fire::getaudionum(){
    return audionum;
}
void Fire::whetherChat(int index){
    
    // const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("dialogue1.json").c_str();
    next * nex=next::create();
    nex->setTag(004);
    this->addChild(nex);
    print=CCLabelTTF::create("", "Marker Felt", 24, CCSizeMake(0, 50), kCCTextAlignmentLeft);
    print->setAnchorPoint(ccp(0, 1));
    print->setPosition(ccp(10, 50));
    this->addChild(print,5);
    //    ifstream ifs;
    //    ifs.open(path);
    
    //    assert(ifs.is_open());
    Json::Reader read;
    Json::Value root;
    Json::Value shuju;
    int ic=5;
    const char * na;
    int ic1=0;
    const char * na1;
    
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("dialogue1.json");
    CCString* str = CCString::createWithContentsOfFile(path.c_str());
    
    
    if(read.parse(str->getCString(), root)){
        char inttostr[40]="";
        sprintf(inttostr, "%d",index);
        shuju=root[inttostr];
        
        
        CCLog("%d",shuju.size());
        for (int i=0; i<shuju.size(); i++) {
            
            chatdialogue * dia=new chatdialogue();
            dia->autorelease();
            dia->msg=shuju[i]["msg"].asString().c_str();
            dia->name=shuju[i]["name"].asString().c_str();
            dia->icon=shuju[i]["icon"].asInt();
            chat_dic->setObject(dia, i);
        }
        
    }
    chatdialogue * d=(chatdialogue *)chat_dic->objectForKey(0);
    chatdialogue * d1=(chatdialogue *)chat_dic->objectForKey(1);//\u5f20\u4e09
    if(d){
        if(!strcmp(d->name.c_str(), "")){
            ic=d->icon;
            na="主公";
        }
        else{
            
            ic1=d->icon;
            na1=d->name.c_str();
            
            
        }
    }
    if(d1){
        if(!strcmp(d1->name.c_str(), "")){
            ic=d1->icon;
            na="主公";
            
        }
        else{
            
            ic1=d1->icon;
            na1=d1->name.c_str();
            
            
            
        }
    }
    
    jiantou =this->moveup();
    jiantou->setPosition(ccp(600, 10));
    jiantou->setVisible(false);
    chatbg=CCSprite::create("chat_bg.png");
    
    chatbg->setOpacity(GLubyte(153));
    chatbg->setAnchorPoint(ccp(0, 0));
    chatbg->setPosition(ccp(5, 30));
    this->addChild(chatbg,1);
    
    chatbg->addChild(jiantou,2);
    
    
    
    if(ic1>10){
        char icc1[60]="";
        sprintf(icc1, "qs_%d.png",ic1);
        //        enemyIcon=CCSprite::create("qs_0001.png");
        enemyIcon=CCSprite::create(icc1);
        enemyIcon->setScale(0.38);
        enemyIcon->setVisible(false);
        //enemyIcon->setAnchorPoint(ccp(0, 0));
        enemyIcon->setPosition(ccp(80, 100));
        
        this->addChild(enemyIcon,1);
        enemyName1=CCLabelTTF::create(na1, "Marker Felt", 35, CCSizeMake(180, 45), kCCTextAlignmentLeft);
        enemyName1->setAnchorPoint(ccp(0, 0));
        //create(na1, "Marker Felt", 35);
        enemyName1->setVisible(false);
        //enemyName1->setAnchorPoint(ccp(0, 0));
        enemyName1->setPosition(ccp(180, 100));
        enemyName1->setColor(ccc3(230, 0, 18));
        this->addChild(enemyName1,1);
    }
    if(ic==0){
        char icc[60]="";
        //        sprintf(icc, "s_wj_icon_%d.png",ic);
        int sex = CData::getCData()->getSex();
        if(sex == 1)
        {
            playerIcon=CCSprite::create("qs_0001.png");
        }
        else if (sex == 2)
        {
            playerIcon=CCSprite::create("qs_0002.png");
        }
        else
        {
            playerIcon=CCSprite::create("qs_0003.png");
        }
        
        
        playerIcon->setScale(0.38);
        playerIcon->setVisible(false);
        
        playerIcon->setPosition(ccp(80, 100));//560 100
        this->addChild(playerIcon,1);
        
        
        playerName1=CCLabelTTF::create(na, "Marker Felt", 35, CCSizeMake(180, 45), kCCTextAlignmentLeft);
        
        playerName1->setVisible(false);
        playerName1->setColor(ccc3(23, 181, 172));
        
        playerName1->setAnchorPoint(ccp(0, 0));
        playerName1->setPosition(ccp(180, 100));//460
        this->addChild(playerName1,1);
    }
    //    ifs.close();
    this->chatPlay();
    
}
void Fire::chatPlay(){
    
    bool chatFlag=CData::getCData()->getChatFlag();
    
    chat_dic->count();
    CCLog("%d",chat_dic->count());
    chatdialogue * chadia;
    int leng;
    e=0;
    if(roundss<chat_dic->count()){
        jiantou->setVisible(false);
        chadia=(chatdialogue *)chat_dic->objectForKey(roundss);
        if(!strcmp(chadia->name.c_str(), "")){
            char iconName[40]="";
            sprintf(iconName, "qs_%d.png",chadia->icon);
            if(playerIcon){
                playerIcon->setVisible(true);
                playerName1->setVisible(true);
            }
            if(enemyIcon){
                enemyIcon->setVisible(false);
                enemyName1->setVisible(false);
            }
            CCLog("%s",chadia->msg.c_str());
            print->initWithString(chadia->msg.c_str(), "Helvetica",30, CCSizeMake(0, 50), kCCTextAlignmentLeft);//330
            //  print->setContentSize(CCSizeMake(33, 50));
            print->setAnchorPoint(ccp(0, 1));
            print->setPosition(ccp(175, 100));
            //            playerIcon->initWithFile("s_wj_icon_5000.png");
            //            playerIcon->setAnchorPoint(ccp(0, 1));
            //            playerIcon->setPosition(ccp(500, 160));
            
            CCLog("%s",chadia->name.c_str());
            // playerName1->setString(chadia->name.c_str());
            this->schedule(schedule_selector(Fire::updatalabel), 0.1);
            //            CCActionInterval * delay=CCDelayTime::create(3);
            //            CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::chatPlay));
            //            CCFiniteTimeAction * final=CCSequence::create(delay,func,NULL);
            //            playerIcon->runAction(final);
            
            //this->chatPlay();
        }
        else{
            char iconName[40]="";
            CCLog("%s",chadia->msg.c_str());
            sprintf(iconName, "qs_%d.png",chadia->icon);
            print->initWithString(chadia->msg.c_str(), "Helvetica",30, CCSizeMake(0, 50), kCCTextAlignmentLeft);
            print->setAnchorPoint(ccp(0, 1));
            print->setPosition(ccp(175, 100));
            // enemyIcon->initWithFile("s_wj_icon_5000.png");
            if(playerIcon){
                playerIcon->setVisible(false);
                playerName1->setVisible(false);
            }
            if(enemyIcon){
                enemyIcon->setVisible(true);
                enemyName1->setVisible(true);
            }
            this->schedule(schedule_selector(Fire::updatalabel), 0.1);
            
        }
    }else{
        this->removeChildByTag(004,true);
        this->doChat();
    }
    
    roundss++;
}
void Fire::zhenping(CCNode * sender){
    // CCScene * f = CCDirector::sharedDirector()->getRunningScene();
    CCPoint size = sender->getPosition();
    CCActionInterval * left1 = CCMoveTo::create(0.03,ccp(sender->getPosition().x+5,sender->getPosition().y));
    CCActionInterval * right1 = CCMoveTo::create(0.03,ccp(sender->getPosition().x-5,sender->getPosition().y));
    CCActionInterval * top1 = CCMoveTo::create(0.03,ccp(sender->getPosition().x,sender->getPosition().y+5));
    CCActionInterval * rom1 = CCMoveTo::create(0.03,size);
    CCFiniteTimeAction* action3 = CCSequence::create(left1,right1,top1,rom1,NULL);
    sender->runAction(action3);
}
void Fire::updatalabel(){
    if(e==10){
        
        this->unschedule(schedule_selector(Fire::updatalabel));
        jiantou->setVisible(true);
        
    }else{
        e++;
        print->setVisible(true);
        print->setDimensions(CCSizeMake(33*e, 50));
        if(e==10){
            
            
        }
        
    }
}
void Fire::removeChat(){
    // m_pNextBG->removeChildByTag(9013);
    chatBounder->removeFromParentAndCleanup(true);
    m_pNextBG->removeFromParentAndCleanup(true);
    
}
void Fire::doChat(){
    //this->zhenping();
    this->removeChild(print,true);
    this->removeChild(chatbg,true);
    this->removeChild(playerName1,true);
    this->removeChild(enemyName1,true);
    this->removeChild(enemyIcon,true);
    this->removeChild(playerIcon,true);
    char * data2=CData::getCData()->getdata();
    this->getJsonData(data2);
}
void Fire::enegrySprite(CCSprite * node,int star){
    //    switch (star) {
    //        case 1:
    //            statements
    //            break;
    //
    //        default:
    //            break;
    //    }
}
void Fire::nextchat(){
    CCLog("%f",print->getDimensions().width);
    if(print->getDimensions().width<330){
        jiantou->setVisible(true);
        print->setDimensions(CCSizeMake(330, 50));
        this->unschedule(schedule_selector(Fire::updatalabel));
    }else if(print->getDimensions().width==330){
        
        print->setDimensions(CCSizeMake(0, 50));
        print->setVisible(false);
        this->chatPlay();
    }
}
Fire::~Fire(){
    
    CCLog("Fire destroy!!!!!!!!!!");
    ene_dic->release();
    player_dic->release();
    jn_dic->release();
    chat_dic->release();
    if (sk) {
        delete sk;
    }
    //    delete tx;
    //    delete mz;
    
    //    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    
}
Fire* Fire::fire(){
    if (!g_config) {
        
        //CCLog("Audio effect %d",a);
        g_config = new Fire();
    }
    
    return g_config;
    
}
void Fire::repate(){
    kaishi=0;
    CCSprite * background=CCSprite::create("pkbg.png");
    background->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(background,-2);
    rounds=0;
    char * data2=CData::getCData()->getdata();
    this->getJsonData(data2);
}
void Fire::getJsonData(char * json){
    
    CCLog("enter this");
    
    this->jsonData(json);
    
    this->attackData(json);
}
CCScene * Fire::scene(){
    CCScene *scene=CCScene::create();
    Fire *fire=Fire::create();
    fire->setTag(902);
    scene->addChild(fire);
    return scene;
}
void Fire::SimpleAttack(){
    this->checkOut();
}
void Fire::MoreAttack(){//******************************
    //for(int i=0;i<_length;i++){
    
    t=0;//**********************
    
    enemy=(CCSprite *)this->getChildByTag(_eneBattId[moreene[ea]]);
    enemy->removeChildByTag(9023+moreene[ea],true);
    enemy->removeChildByTag(9800+moreene[ea],true);
    CCSprite * blood=(CCSprite *)enemy->getChildByTag(_eneBattId[moreene[ea]]+1000);
    
    if(_eneChanHp[moreene[ea]]+_eneCurrHp[moreene[ea]]<=0){
        
        CCActionInterval *  scal=CCScaleTo::create(1/Time, 0, 1);
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::removeAction));
        CCFiniteTimeAction *Action=CCSequence::create(scal,func,NULL);
        blood->runAction(Action);
    }
    else{
        
        //percent=((double)currHp+changeHp/(double)totalHp);
        int ech=_eneChanHp[moreene[ea]];
        int echp=_eneCurrHp[moreene[ea]];
        int eth=_eneTotHp[moreene[ea]];
        percent1=((double)(ech+echp)/(double)(eth));
        CCActionInterval *  scal=CCScaleTo::create(1/Time, percent1, 1);
        CCCallFunc * func=CCCallFunc::create(this,callfunc_selector(Fire::removeAction));
        CCFiniteTimeAction *Action=CCSequence::create(scal,func,NULL);
        blood->runAction(Action);
    }
    ea++;
    //}
}
void Fire::removeAction(){
    
    //for (int i=0; i<_length; i++) {
    if(_eneChanHp[t]+_eneCurrHp[t]<=0){
        enemy=(CCSprite *)this->getChildByTag(_eneBattId[t]);
        enemy->setTag(_eneBattId[t]);
        //enemy->removeChildByTag(9023+t);
        const char * texiaoname=sk->skills(_skillId);
        char txname[50]="";
        sprintf(txname, "%s.xml",texiaoname);
        
        // AnimatePacker :: getInstance()->freeAnimations(txname);
        this->removeChildByTag(_eneBattId[t],true);
        _eneBattId[t]=0;
        if(t==_length-1){
            this->SimpleAttack();
        }
    }else{
        enemy=(CCSprite *)this->getChildByTag(_eneBattId[t]);
        // enemy->removeChildByTag(9023+t);
        if(t==_length-1){
            this->SimpleAttack();
        }
        
    }
    t++;
}
void Fire::checkOut(){
    
    chaBattleId=0;
    int eneBattleId;
    int eneChaId;
    int eneActionId;
    int eneChangeHP;
    int eneCurrentHp;
    int eneTotalHp;
    int chaId;
    int actionID;
    int skillId;
    int chaCurrentPower;
    //Json::Value eneArr;
    Json::Value eneArr;
    Json::Value buff;
    chaBattleId=stepData[rounds]["chaBattleId"].asInt();
    
    if(chaBattleId!=0){
        eneArr=stepData[rounds]["enemyChaArr"];
        chaId=stepData[rounds]["chaId"].asInt();
        actionID=stepData[rounds]["actionId"].asInt();
        skillId=stepData[rounds]["skill"].asInt();
        chaCurrentPower=stepData[rounds]["chaCurrentPower"].asInt();
        
        if(eneArr.size()==1)
        {
            int round=0;
            if(eneChaId-10<10){
                fireinfo * fire=new fireinfo();
                fire->personId=eneChaId-10;
                
                buff=eneArr[round]["enemyBuffArr"];
                for (int i=0; i<buff.size(); i++) {
                    fire->buff[i]=buff[i].asInt();
                }
                player_dic->setObject(fire, fire->personId);
                //delete fire;
            }
            eneBattleId=eneArr[round]["enemyBattleId"].asInt();
            
            eneChaId=eneArr[round]["enemyChaId"].asInt();
            
            eneActionId=eneArr[round]["enemyActionId"].asInt();
            
            eneChangeHP=eneArr[round]["enemyChangeHp"].asInt();
            
            eneCurrentHp=eneArr[round]["enemyCurrentHp"].asInt();
            
            eneTotalHp=eneArr[round]["enemyTotalHp"].asInt();
            if(chaBattleId==-1){
                this->debuff(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp);
            }else{
                this->actionAttack(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp, actionID, chaBattleId,chaId,skillId);
            }
            //        this->actionAttack(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp, actionID, chaBattleId,chaId,skillId);
        }
        else if(eneArr.size()>1){
            int eneChaid[eneArr.size()];
            int eneChanHp[eneArr.size()];
            int eneCurrHp[eneArr.size()];
            int eneTotHp[eneArr.size()];
            int eneBattId[eneArr.size()];
            int eneActId[eneArr.size()];
            for(int i=0;i<eneArr.size();i++){
                if(eneChaId-10<10){
                    fireinfo * fire=   new fireinfo();
                    fire->personId=eneChaId-10;
                    
                    buff=eneArr[i]["enemyBuffArr"];
                    for (int i=0; i<buff.size(); i++) {
                        fire->buff[i]=buff[i].asInt();
                    }
                    if(buff.size()==0){
                        * fire->buff=0;
                        player_dic->setObject(fire, fire->personId);
                    }else{
                        player_dic->setObject(fire, fire->personId);
                    }
                    //delete fire;
                }
                eneBattleId=eneArr[i]["enemyBattleId"].asInt();
                
                eneChaId=eneArr[i]["enemyChaId"].asInt();
                
                eneActionId=eneArr[i]["enemyActionId"].asInt();
                
                eneChangeHP=eneArr[i]["enemyChangeHp"].asInt();
                
                eneCurrentHp=eneArr[i]["enemyCurrentHp"].asInt();
                
                eneTotalHp=eneArr[i]["enemyTotalHp"].asInt();
                eneChaid[i]=eneChaId;
                eneChanHp[i]=eneChangeHP;
                eneCurrHp[i]=eneCurrentHp;
                eneTotHp[i]=eneTotalHp;
                eneActId[i]=eneActionId;
                eneBattId[i]=eneBattleId;
            }
            this->moreActionAttack(eneBattId, eneChaid, eneChanHp, eneCurrHp, eneTotHp, eneActId, chaBattleId, chaId,eneArr.size(),skillId);
        }
        int e1=0;
        int e2=0;
        int e3=0;
        int e4=0;
        int e5=0;
        for (int i=0; i<9; i++) {
            fireinfo *fire=(fireinfo *) player_dic->objectForKey(i);
            if(fire){
                for(int j=0;j<5;j++){
                    if(fire->buff[j]==100005){
                        e1++;
                    }else if(fire->buff[j]==100003){
                        e2++;
                    }else if(fire->buff[j]==100001){
                        e3++;
                    }
                }
            }
        }
        if(e1==0){
            buff1->setVisible(false);
        }else if(e2==0)
        {
            buff2->setVisible(false);
        }else if(e3==0){
            buff3->setVisible(false);
        }
        
        rounds++;
    }
    else{
        AnimatePacker :: getInstance()->freeAnimations ("qishouTX.xml");
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName ("result_attacked.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName ("jn_name.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName ("begin1.plist");
        for(int i=0;i<20;i++){
            if(skillnumbers[i]!=0){
                const char * texiaoname=sk->skills(skillnumbers[i]);
                char names[40]="";
                sprintf(names, "%s.xml",texiaoname);
                AnimatePacker::getInstance()->freeAnimations(names);
            }
        }
        
        GameOver *game=GameOver::create();
        game->setTag(8021);
        this->addChild(game,9999);
    }
    //此处将获取的json数据传递给消息触发器
    
}
void Fire::attackData(char * jsonData){
    printf("%s\n",jsonData);
    Json::Reader read;
    Json::Value value;
    int chaBattleId;
    int eneBattleId;
    int eneChaId;
    int eneActionId;
    int eneChangeHP;
    int eneCurrentHp;
    int eneTotalHp;
    int chaId;
    //int pos;
    int dir;
    int actionId;
    int skillId;int chaCurrentPower;
    
    Json::Value eneArr;
    if (read.parse(jsonData, value)) {
        //此处解析攻击json数据
        Json::Value data=value["data"];
        battleresult=data["battleResult"].asInt();
        CData::getCData()->setFireResult(battleresult);
        stepData=data["stepData"];
        
        chaBattleId=stepData[rounds]["chaBattleId"].asInt();
        dir=stepData[rounds]["chaDirection"].asInt();
        eneArr=stepData[rounds]["enemyChaArr"];
        chaId=stepData[rounds]["chaId"].asInt();
        actionId=stepData[rounds]["actionId"].asInt();
        skillId=stepData[rounds]["skill"].asInt();
        chaCurrentPower=stepData[rounds]["chaCurrentPower"].asInt();
        _chaCurrentPower=chaCurrentPower;
        if(eneArr.size()==1)
        {
            eneBattleId=eneArr[rounds]["enemyBattleId"].asInt();
            eneChaId=eneArr[rounds]["enemyChaId"].asInt();
            eneActionId=eneArr[rounds]["enemyActionId"].asInt();
            eneChangeHP=eneArr[rounds]["enemyChangeHp"].asInt();
            eneCurrentHp=eneArr[rounds]["enemyCurrentHp"].asInt();
            eneTotalHp=eneArr[rounds]["enemyTotalHp"].asInt();
            _eneCurrentPower=eneArr[rounds]["enemyCurrentPower"].asInt();
            if(chaBattleId==-1){
                this->debuff(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp);
            }else{
                this->actionAttack(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp, actionId, chaBattleId,chaId,skillId);
            }
        }
        else if(eneArr.size()>1){
            int eneChaid[eneArr.size()];
            int eneChanHp[eneArr.size()];
            int eneCurrHp[eneArr.size()];
            int eneTotHp[eneArr.size()];
            int eneBattId[eneArr.size()];
            int eneActId[eneArr.size()];
            for(int i=0;i<eneArr.size();i++){
                eneBattleId=eneArr[i]["enemyBattleId"].asInt();
                
                eneChaId=eneArr[i]["enemyChaId"].asInt();
                
                eneActionId=eneArr[i]["enemyActionId"].asInt();
                
                eneChangeHP=eneArr[i]["enemyChangeHp"].asInt();
                
                eneCurrentHp=eneArr[i]["enemyCurrentHp"].asInt();
                
                eneTotalHp=eneArr[i]["enemyTotalHp"].asInt();
                eneChaid[i]=eneChaId;
                eneChanHp[i]=eneChangeHP;
                eneCurrHp[i]=eneCurrentHp;
                eneTotHp[i]=eneTotalHp;
                eneActId[i]=eneActionId;
                eneBattId[i]=eneBattleId;
                
            }
            
            this->moreActionAttack(eneBattId, eneChaid, eneChanHp, eneCurrHp, eneTotHp, eneActId, chaBattleId, chaId,eneArr.size(),skillId);
        }
        //此处将获取的json数据传递给消息触发器
    }
    rounds++;
}
void Fire::moreActionAttack(int *eneBattId, int *eneChaid, int * eneChanHp, int * eneCurrHp, int * eneTotHp, int * eneActId, int chaBattleId, int chaId,int length,int skillId){
    max=1;
    for(int i=0;i<length;i++){
        _eneBattId[i]=eneBattId[i];
        _eneChaid[i]=eneChaid[i];
        _eneChanHp[i]=eneChanHp[i];
        _eneCurrHp[i]=eneCurrHp[i];
        _eneTotHp[i]=eneTotHp[i];
        _eneActId[i]=eneActId[i];
        
    }
    _skillId=skillId;
    _chaBattleId=chaBattleId;
    _chaId=chaId;
    _length=length;
    if (kaishi==0){
        kaishi=1;
        
        //    knif=CCSpriteBatchNode::create("begin.png");
        //    this->addChild(knif);
        CCArray * kneif=CCArray::create();
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("01.png");
        CCSprite *explosion = CCSprite::createWithSpriteFrame(pFrame);
        explosion->setTag(1111);
        explosion->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(explosion);
        for(int i=2;i<=10; i++)
        {
            CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%02d.png",i)->getCString());
            
            kneif->addObject(spf);
        }
        
        CCActionInterval * delay=CCDelayTime::create(1);
        CCAnimation * Action=CCAnimation::createWithSpriteFrames(kneif, 0.1f);
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(Fire::moreattactnext));
        CCFiniteTimeAction *playerAct=CCSequence::create(delay,CCAnimate::create(Action),fun2,NULL);
        explosion->runAction(playerAct);
    }
    else {
        this->moreattactnext();
    }
}
void Fire::moreattactnext(){
    player=(CCSprite *)this->getChildByTag(_chaBattleId);
    CCFadeOut *playfadeout=CCFadeOut::create(0.18f);//0.18f
    CCFadeIn *playerfadein=CCFadeIn::create(0.3f);//0.3f
    CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(Fire::moreAttackName));
    CCFiniteTimeAction *playerAct=CCSequence::create(playfadeout,playerfadein,fun2,NULL);
    player->runAction(playerAct);
    
}
void Fire::moreAttackName(){
    //CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("lq_lq_01.png");
    
    this->removeChildByTag(1111);
    const char * skillname=sk->skillname(_skillId);
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(skillname);
    label=CCSprite::createWithSpriteFrame(pFrame);
    //label=CCLabelTTF::create(skillname, "Marker Felt", 35);
    label->setPosition(ccp(size.width/2, size.height/2));
    label->setTag(999);
    this->addChild(label);
    CCActionInterval *action=CCMoveTo::create(0.88, ccp(size.width/2, size.height/2));
    CCFadeOut *fadeout=CCFadeOut::create(0.12f);
    CCCallFunc * func1=CCCallFunc::create(this, callfunc_selector(Fire::moreAttackTitle));
    //CCCallFunc * fun3=CCCallFunc::create(this, callfunc_selector(Fire::removeSprite));
    CCFiniteTimeAction *allaction=CCSequence::create(action,fadeout,func1,NULL);
    label->runAction(allaction);
    
}
void Fire::debuff(int eneBid,int enechaid,int changeHp1,int eneCurrHp,int eneTotalHp){
    enemy=(CCSprite *)this->getChildByTag(eneBid);
    
    
    
    
    currHp=eneCurrHp;
    totalHp=eneTotalHp;
    changeHp=changeHp1;
    // texiao->removeFromParent();//normalattack
    
    
  //  tx=CCSprite::createWithSpriteFrameName("ptbj_01.png");
    tx=CCSprite::create("attacked_img.png");
  //  tx->runAction(AnimatePacker::getInstance()->getAnimate("ptbj"));
    tx->setPosition(ccp(70, 75));

    
    char cHp[10]={0};
    sprintf(cHp, "%d",changeHp);
    
    //reduB=CCLabelTTF::create(cHp,"Marker Felt", 30);
    reduB=CCLabelAtlas::create(cHp, "number.png", 30, 50, '-');
    reduB->setTag(0020);
    reduB->setColor(ccc3(255, 0, 0));
    reduB->setAnchorPoint(ccp(0.5, 0));
    reduB->setPosition(ccp(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
    enemy->addChild(reduB);
    enemy->addChild(tx);
    // CCActionInterval * set_small=CCScaleTo::create(0, 0);
    CCActionInterval * set_big=CCScaleTo::create(0.2/Time, 1.5);
    CCActionInterval * set_nor=CCScaleTo::create(0.2/Time, 1);
    //CCActionInterval *a_jianxue=CCMoveTo::create(0.45, ccp(reduB->getPosition().x, reduB->getPosition().y+80));
    
    CCFadeOut *a_jiaxue_fadeout=CCFadeOut::create(0.5f/Time);
    // CCCallFunc * fun3=CCCallFunc::create(this, callfunc_selector(Fire::removeSprite));
    CCCallFunc * reduceBlood=CCCallFunc::create(this, callfunc_selector(Fire::changeBlood));
    CCFiniteTimeAction *jianxueaction=CCSequence::create(set_big,set_nor,a_jiaxue_fadeout,reduceBlood,NULL);
    //CCFiniteTimeAction *jianxueaction=CCSequence::create(a_jianxue,a_jiaxue_fadeout,reduceBlood,NULL);
    reduB->runAction(jianxueaction);
    //    CCShaky3D *shake=CCShaky3D::create(0.3/Time, CCSizeMake(2, 2), 5, false);
    //    enemy->runAction(shake);
    zhenping(enemy);
    
    
    
    
    //changeHp=changeHp;
    currHp=eneCurrHp;
    eneBID=eneBid;
    totalHp=eneTotalHp;
    _actionId=99;
}
void Fire::buffbegin(int bufftype){
    
    CCActionInterval * buffrote1=CCRotateBy::create(10, 360);
    CCActionInterval * buffrote2=CCRotateBy::create(15, 360);
    CCActionInterval * fadein1=CCFadeIn::create(1);
    CCActionInterval * fadeout1=CCFadeOut::create(1);
    CCFiniteTimeAction * final=CCSequence::create(fadein1,fadeout1,NULL);
    CCActionInterval * fadein2=CCFadeIn::create(1.5);
    CCActionInterval * fadeout2=CCFadeOut::create(1.5);
    CCFiniteTimeAction * final2=CCSequence::create(fadein2,fadeout2,NULL);
    CCActionInterval * fadein3=CCFadeIn::create(1.2);
    CCActionInterval * fadeout3=CCFadeOut::create(1.2);
    CCFiniteTimeAction * final3=CCSequence::create(fadein3,fadeout3,NULL);
    switch (bufftype) {
        case 1:
            buff1->setVisible(true);
            buff1->runAction(CCRepeatForever::create(buffrote1));
            buff1->runAction(CCRepeatForever::create((CCActionInterval *)final));
            break;
        case 2:
            buff2->setVisible(true);
            buff2->runAction(CCRepeatForever::create(buffrote2));
            buff2->runAction(CCRepeatForever::create((CCActionInterval *)final3));
            break;
        case 3:
            buff3->setVisible(true);
            buff3->runAction(CCRepeatForever::create((CCActionInterval *)final2));
            break;
        default:
            break;
    }
    
}
void Fire::buffend(){
    
}
void Fire::AttackName(){
    // texiao->removeFromParent();
    this->removeChildByTag(2078,true);
    CCLog("%d",_chaCurrentPower);
    CCSprite * nl=(CCSprite *)player->getChildByTag(24);

    const char * skillname=sk->skillname(_skillId);
    const char * skillss=sk->throwTX(_skillId);
    if(!strcmp(skillname, "")){
        CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(skillname);
        label=CCSprite::createWithSpriteFrame(pFrame);
        label->setPosition(ccp(size.width/2, size.height/2));
        label->setTag(999);
        this->addChild(label);
        CCActionInterval *action=CCMoveTo::create(0.88, ccp(size.width/2, size.height/2));
        CCFadeOut *fadeout=CCFadeOut::create(0.12f);
        CCCallFunc * func1=CCCallFunc::create(this, callfunc_selector(Fire::whethertwice));//Fire::attacked
        // CCCallFunc * fun3=CCCallFunc::create(this, callfunc_selector(Fire::removeSprite));
        CCFiniteTimeAction *allaction=CCSequence::create(action,fadeout,func1,NULL);
        label->runAction(allaction);
        this->whethertwice();
    }else {
        this->whethertwice();
    }
}
void Fire::whethertwice(){
    
    skk=(skill *)this->returnskills(_skillId);
    if(skk->throwEffectId!=0){
        this->throwtwice();
    }else{
        this->attacked();
    }
}
void Fire::throwtwice(){
    enemy=(CCSprite *)this->getChildByTag(eneBID);
    player=(CCSprite *)this->getChildByTag(chaIdd);
    CCLog("%d",player->getTag());
    CCLog("%d",enemy->getTag());
    CCLog("%f  %f",player->getPosition().x);
    CCLog("%f  %f",player->getPosition().y);
    CCLog("%f  %f",enemy->getPosition().x);
    CCLog("%f  %f",enemy->getPosition().y);
    const char * skillname=sk->throwTX(_skillId);
    const char * texiaoname=sk->skills(_skillId);
    CCParticleSystemQuad * stars;
    if(!strcmp(texiaoname, "tx")){
        stars=CCParticleSystemQuad::create("touxi_1.plist");
        // stars->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire_1.png"));
        // stars->setBlendAdditive(false);
        stars->setPosition(player->getPosition());
        stars->setTag(8032);
        this->addChild(stars);
        CCActionInterval * delay=CCDelayTime::create(0.1);
        CCActionInterval * moveto=CCMoveTo::create(0.5/Time, enemy->getPosition());
        
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::attacked));
        CCFiniteTimeAction * final=CCSequence::create(delay,moveto,func,NULL);
        stars->runAction(final);
    }else{
        char txname[50]="";
        sprintf(txname, "%s.xml",texiaoname);
        
        char combine[50]="";
        
        sprintf(combine, "%s_01_01.png",texiaoname);
        tz=CCSprite::createWithSpriteFrameName(combine);
        
        char animate[50]="";
        sprintf(animate, "%s_tz",texiaoname);
        tz->runAction(CCRepeatForever::create( AnimatePacker::getInstance()->getAnimate(animate)));
        float y1;
        float y2;
        float x1;
        float x2;
        float angel;
        x1=player->getPosition().x;
        x2=enemy->getPosition().x;
        y1=player->getPosition().y;
        y2=enemy->getPosition().y;
        
        angel=(y1-y2)/(x1-x2);
        angel=atanf(angel)/M_PI*180;
        
        tz->setPosition(ccp(x1, y1+50));
        if(angel<0){
            tz->setRotation(90-angel);
            
        }else{
            tz->setRotation(90-angel);
        }
        tz->setTag(8078);
        this->addChild(tz,2);
        
        
        CCActionInterval * delay=CCDelayTime::create(0.1);
        CCActionInterval * moveto=CCMoveTo::create(0.5/Time, enemy->getPosition());
        
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::attacked));
        CCFiniteTimeAction * final=CCSequence::create(delay,moveto,func,NULL);
        tz->runAction(final);
        
    }
    
}
void Fire::moreAttackTitle(){
    this->removeChildByTag(999,true);
    skill *sk=this->returnskills(_skillId);
    skillList * skk=new skillList();
    if(eneBID-10<10){
        if(_skillId==100002){
            buffbegin(1);
            label3->setColor(ccc3(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方防御增加");
            label3->setPosition(ccp(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            CCDelayTime * delaytime=CCDelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, ccp(520, 520));
            CCFadeOut * fadeout=CCFadeOut::create(1);
            CCSequence * seq=CCSequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
            
            //        if(!strcmp(label3->getString(), "")){
            //            label3->setString("我方防御增加");
            //        }else if(!strcmp(label2->getString(), "")){
            //            label2->setString("我方防御增加");
            //        }else if(!strcmp(label1->getString(), "")){
            //            label1->setString("我方防御增加");
            //        }else{
            //            const char * str=label1->getString();
            //            label1->setString(label2->getString());
            //            label2->setString(label3->getString());
            //            label3->setString("我方防御增加");
            //        }
            
        }else if(_skillId==100005){
            buffbegin(2);
            label3->setColor(ccc3(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方攻击增加");
            label3->setPosition(ccp(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            CCDelayTime * delaytime=CCDelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, ccp(520, 520));
            CCFadeOut * fadeout=CCFadeOut::create(1);
            CCSequence * seq=CCSequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
            //        if(!strcmp(label3->getString(), "")){
            //            label3->setString("我方攻击增加");
            //        }else if(!strcmp(label2->getString(), "")){
            //            label2->setString("我方攻击增加");
            //        }else if(!strcmp(label1->getString(), "")){
            //            label1->setString("我方攻击增加");
            //        }else{
            //            const char * str=label1->getString();
            //            label1->setString(label2->getString());
            //            label2->setString(label3->getString());
            //            label3->setString("我方攻击增加");
            //        }
        }
        else if(_skillId==100001){
            buffbegin(3);
            //        if(!strcmp(label3->getString(), "")){
            //            label3->setString("我方暴击增加");
            //        }else if(!strcmp(label2->getString(), "")){
            //            label2->setString("我方暴击增加");
            //        }else if(!strcmp(label1->getString(), "")){
            //            label1->setString("我方暴击增加");
            //        }else{
            //            const char * str=label1->getString();
            //            label1->setString(label2->getString());
            //            label2->setString(label3->getString());
            //            label3->setString("我方暴击增加");
            //        }
            label3->setColor(ccc3(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方暴击增加");
            label3->setPosition(ccp(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            CCDelayTime * delaytime=CCDelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, ccp(520, 520));
            CCFadeOut * fadeout=CCFadeOut::create(1);
            CCSequence * seq=CCSequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
    }else{
        if(_skillId==100002){
            //            buffbegin(1);
            //            if(!strcmp(label3->getString(), "")){
            //                label3->setString("敌方防御增加");
            //            }else if(!strcmp(label2->getString(), "")){
            //                label2->setString("敌方防御增加");
            //            }else if(!strcmp(label1->getString(), "")){
            //                label1->setString("敌方防御增加");
            //            }else{
            //                const char * str=label1->getString();
            //                label1->setString(label2->getString());
            //                label2->setString(label3->getString());
            //                label3->setString("敌方防御增加");
            //            }
            label3->setColor(ccc3(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方防御增加");
            label3->setPosition(ccp(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            CCDelayTime * delaytime=CCDelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, ccp(520, 520));
            CCFadeOut * fadeout=CCFadeOut::create(1);
            CCSequence * seq=CCSequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }else if(_skillId==100005){
            buffbegin(2);
            label3->setColor(ccc3(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方攻击增加");
            label3->setPosition(ccp(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            CCDelayTime * delaytime=CCDelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, ccp(520, 520));
            CCFadeOut * fadeout=CCFadeOut::create(1);
            CCSequence * seq=CCSequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
        else if(_skillId==100001){
            buffbegin(3);
            label3->setColor(ccc3(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方暴击增加");
            label3->setPosition(ccp(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            CCDelayTime * delaytime=CCDelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, ccp(520, 520));
            CCFadeOut * fadeout=CCFadeOut::create(1);
            CCSequence * seq=CCSequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
    }
    
    
    const char * namees=skk->releaseName(sk->releaseEffect);
    CCLog("%s",namees);
    char combine[40]="";
    //    char  anames[40]="";
    //    sprintf(anames, "%s_tz",namees);
    
    sprintf(combine, "%s_01.png",namees);
    CCLog("%s",combine);
    texiao=CCSprite::createWithSpriteFrameName(combine);
    texiao->setTag(0014);
    
    texiao->runAction(AnimatePacker::getInstance()->getAnimate(namees));
    //delete skk;
    //texiao=(CCSprite *)texiao::TX()->texiaosCreate("mou", 8);
    texiao->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    this->addChild(texiao,5);
    CCActionInterval * moveto=CCMoveTo::create(0.7, ccp(player->getPosition().x, player->getPosition().y));//enemy
    CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(Fire::moreAttacked));
    CCFiniteTimeAction *playerAct=CCSequence::create(moveto,fun2,NULL);
    
    texiao->runAction(playerAct);
    
}
void Fire::moreAttacked(){
    texiao->removeFromParentAndCleanup(true);
    
    //this->removeChildByTag(0014);
    j=0;
    ea=0;
    //t=0;//ceshi
    const char * texiaoname=sk->skills(_skillId);
    char txname[50]="";
    sprintf(txname, "%s.xml",texiaoname);
    
    // AnimatePacker :: getInstance()->loadAnimations(txname);
    for (int i=0; i<_length; i++) {
        moreene[j]=i;
        j++;
        
        
        
        int idnum=sk->skillnums(_skillId);
        CCLog("%d  %s",idnum,texiaoname);
        if(_skillId==100001){
            
        }else if(_skillId==100002){
            
        }
        enemy=(CCSprite *)this->getChildByTag(_eneBattId[i]);
        enemy->setTag(_eneBattId[i]);
        
        char combine[50]="";
        sprintf(combine, "%s_01.png",texiaoname);
        mz=CCSprite::createWithSpriteFrameName(combine);
        // mz=CCSprite::createWithSpriteFrameName("mou_01.png");
        
        mz->runAction(AnimatePacker::getInstance()->getAnimate(texiaoname));
        
        // mz=texiao::TX()->texiaosCreate(texiaoname, idnum);
        mz->setPosition(ccp(50, 50));
        mz->setTag(9023+i);
        char changeBlood[20]="";
        sprintf(changeBlood, "%d",_eneChanHp[i]);
        //CCLabelTTF * reduB=CCLabelTTF::create(changeBlood,"Marker Felt", 30);
        CCLabelAtlas * reduB=CCLabelAtlas::create(changeBlood, "number.png", 30, 50, '-');
        reduB->setColor(ccc3(255, 0, 0));
        reduB->setTag(9800+i);
        reduB->setAnchorPoint(ccp(0.5, 0));
        reduB->setPosition(ccp(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
        enemy->addChild(mz);
        enemy->addChild(reduB);
        // CCActionInterval * set_small=CCScaleBy::create(0, 0);
        CCActionInterval * set_big=CCScaleBy::create(0.2, 1.5);
        CCActionInterval * set_nor=CCScaleBy::create(0.2, 1);
        //CCActionInterval *a_jianxue1=CCMoveTo::create(0.2, ccp(reduB->getPosition().x, reduB->getPosition().y+60));
        CCFadeOut *a_jiaxue_fadeout1=CCFadeOut::create(0.5f);
        CCCallFunc*  func2=CCCallFunc::create(this, callfunc_selector(Fire::MoreAttack));
        CCFiniteTimeAction *jianxueaction1=CCSequence::create(set_big,set_nor,a_jiaxue_fadeout1,func2,NULL);
        reduB->runAction(jianxueaction1);
        zhenping(enemy);
        
        
    }
    
}

void Fire::actionAttack(int eneBattleId,int eneChaID,int eneChangeHp,int eneCurrentHp,int eneTotalHp,int actionID,int chaBattleID,int chaId,int skillId){
    CCLog("%d",eneBattleId);
    enemy=(CCSprite *)this->getChildByTag(eneBattleId);
    player=(CCSprite *)this->getChildByTag(chaBattleID);
    chaIdd=chaBattleID;
    if (kaishi==0){
        
        
        //    knif=CCSpriteBatchNode::create("begin.png");
        //    this->addChild(knif);
        CCArray * kneif=CCArray::create();
        
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("01.png");
        explosion = CCSprite::createWithSpriteFrame(pFrame);
        explosion->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(explosion);
        for (int i=2;i<=10; i++)
        {
            CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%02d.png",i)->getCString());
            CCLog(CCString::createWithFormat("%02d.png",i)->getCString());
            CCLog("\n");
            kneif->addObject(spf);
        }
        
        CCActionInterval * delay=CCDelayTime::create(4/Time);
        CCAnimation * Action=CCAnimation::createWithSpriteFrames(kneif, 0.25f/Time);
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(Fire::runBegin));
        CCActionInterval* act = CCAnimate::create(Action);
        CCFiniteTimeAction *playerAct=CCSequence::create(delay,act,fun2,NULL);
        explosion->runAction(playerAct);
        
        _skillId=skillId;
        changeHp=eneChangeHp;
        currHp=eneCurrentHp;
        eneBID=eneBattleId;
        totalHp=eneTotalHp;
        _actionId=actionID;
        
    }
    //此处执行攻击者动画
    else if(kaishi==1){
        this->runBegin();
        _skillId=skillId;
        changeHp=eneChangeHp;
        currHp=eneCurrentHp;
        eneBID=eneBattleId;
        totalHp=eneTotalHp;
        _actionId=actionID;
    }
}

void Fire::runBegin(){
    if(kaishi==0){
        kaishi=1;
        explosion->removeFromParentAndCleanup(true);
    }
    printf("chaBattleId      %d\n",chaIdd);
    cout<<chaIdd/10<<endl;
    if(chaIdd/10==1){
        // sk=new skillList();
        const char * texiaoname=sk->skills(_skillId);
        if(!strcmp(texiaoname, "sq")||!strcmp(texiaoname, "sl")||!strcmp(texiaoname, "sj")||!strcmp(texiaoname, "sf")||!strcmp(texiaoname, "sr")||!strcmp(texiaoname, "sdjx")||!strcmp(texiaoname, "mrj")||!strcmp(texiaoname, "wlbf")){
            
        }
        else{
            
            //   texiao::TX()->texiaosCreate(texiaoname, 5);
        }
        ///CCLog("%s",texiaoname);
        CCActionInterval * moveon=CCMoveTo::create(0.12/Time, ccp(player->getPosition().x, player->getPosition().y+20));
        CCActionInterval * movedown=CCMoveTo::create(0.12/Time, ccp(player->getPosition().x, player->getPosition().y));
        
        CCCallFunc * fun4=CCCallFunc::create(this, callfunc_selector(Fire::fangzhao));
        CCFiniteTimeAction *playerAct1=CCSequence::create(moveon,movedown,fun4,NULL);
        player->runAction(playerAct1);
    }
    else if(chaIdd/10==2){
        //skillList * sk=new skillList();
        // const char * texiaoname=sk->skills(_skillId);
        // if(strcmp(texiaoname, "0")){
        CCActionInterval * moveon=CCMoveTo::create(0.12/Time, ccp(player->getPosition().x, player->getPosition().y-20));
        CCActionInterval * movedown=CCMoveTo::create(0.12/Time, ccp(player->getPosition().x, player->getPosition().y));
        
        CCCallFunc * fun4=CCCallFunc::create(this, callfunc_selector(Fire::fangzhao));
        CCFiniteTimeAction *playerAct1=CCSequence::create(moveon,movedown,fun4,NULL);
        CCLog("player tag ===%d",player->getTag());
        player->runAction(playerAct1);
        //}
        
    }
    
    
}
void Fire::fangzhao(){
    
    //此处执行招数动画
    if(_actionId==98){
        
        float y1;
        float y2;
        float x1;
        float x2;
        float angel;
        x1=player->getPosition().x;
        x2=enemy->getPosition().x;
        y1=player->getPosition().y;
        y2=enemy->getPosition().y;
        
        angel=(y1-y2)/(x1-x2);
        angel=atanf(angel)/M_PI*180;
        // CData::getCData()->setTFiremusic();
        srandom(time(NULL));
        int s1=0;
        s1=rand()%3;
        switch(s1)
        {
            case 0:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
            case 1:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack2.mp3");
                break;
            case 2:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack3.mp3");
                break;
            default:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
        }
        skill *sk=this->returnskills(_skillId);
        skillList * skk=new skillList();
        const char * namees=skk->releaseName(sk->releaseEffect);
        
        
        CCLog("%d",sk->releaseEffect);
        //         char  anames[40]="";
        //        sprintf(anames, "%s_tz",namees);
        char combine[40]="";
        sprintf(combine, "%s_01.png",namees);
        texiao=CCSprite::createWithSpriteFrameName(combine);
        
        texiao->setTag(2078);
        texiao->runAction(AnimatePacker::getInstance()->getAnimate(namees));
        // addChild(touxi,99);
        //delete skk;
        //texiao=(CCSprite *)texiao::TX()->texiaosCreate("mou", 8);
        texiao->setPosition(ccp(player->getPosition().x, player->getPosition().y));
        this->addChild(texiao,5);
        CCActionInterval * moveto=CCMoveTo::create(1/Time, ccp(player->getPosition().x, player->getPosition().y));//enemy
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(Fire::AttackName));
        CCFiniteTimeAction *playerAct=CCSequence::create(moveto,fun2,NULL);
        texiao->runAction(playerAct);
    }else if(_actionId==99){
        
        
     //   normalAttack=CCSprite::createWithSpriteFrameName("ptgj_01.png");
        normalAttack = CCSprite::create("attack_img.png");
        normalAttack->setTag(0012);
        // normalAttack->setPosition(ccp(320, 480));
   //     normalAttack->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate("ptgj")));
        //normalAttack=texiao::TX()->normalAttackCreate();
        if(chaIdd/10==1){
            //normalAttack->setRotation(90);
        }
        else if(chaIdd/10==2){
            normalAttack->setRotation(180);
        }
        normalAttack->setPosition(ccp(player->getPosition().x, player->getPosition().y+30));
        //normalAttack->setScale(2.0);
        this->addChild(normalAttack,5);
        float y1;
        float y2;
        float x1;
        float x2;
        float angel;
        x1=player->getPosition().x;
        x2=enemy->getPosition().x;
        y1=player->getPosition().y;
        y2=enemy->getPosition().y;
        angel=(y1-y2)/(x1-x2);
        angel=atanf(angel)/M_PI*180;
        //CData::getCData()->setFiremusic();
        srandom(time(NULL));
        int s2=0;
        s2=rand()%3;
        switch(s2)
        {
            case 0:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
            case 1:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack2.mp3");
                break;
            case 2:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack3.mp3");
                break;
            default:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
        }
        CCActionInterval * moveto=CCMoveTo::create(0.4/Time, ccp(player->getPosition().x, player->getPosition().y+30));//改动 ccp(enemy->getPosition().x, enemy->getPosition().y)
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(Fire::attacked));
        //CCCallFunc * fun3=CCCallFunc::create(this, callfunc_selector(Fire::removeSprite));
        CCFiniteTimeAction *playerAct=CCSequence::create(moveto,fun2,NULL);
        normalAttack->runAction(playerAct);
    }
}
void Fire::attacked(){
    
    this->removeChildByTag(8032,true);
    //label->stopAllActions();
    this->removeChildByTag(999,true);
    if(_actionId==99){
        CCLog("_chaCurrentPower %d",_chaCurrentPower);
        //CCSprite * nl=(CCSprite *)player->getChildByTag(24);
        //normalAttack->removeFromParentAndCleanup(true);
        normalAttack->stopAllActions();
        this->removeChildByTag(0012,true);
        //enemy->removeChildByTag(0012);
        //tx=CCSprite::createWithSpriteFrameName("ptbj_01.png");
        tx=CCSprite::create("attacked_img.png");
        //tx->setPosition(ccp(320, 480));
        
       // tx->runAction(AnimatePacker::getInstance()->getAnimate("ptbj"));
        // tx=texiao::TX()->texiaoCreate();
        tx->setTag(9099);
        tx->setPosition(ccp(70, 75));
        
        char cHp[10]={0};
        sprintf(cHp, "%d",changeHp);
        
        //reduB=CCLabelTTF::create(cHp,"Marker Felt", 30);
        
        reduB=CCLabelAtlas::create(cHp, "number.png", 30, 50, '-');
        reduB->setColor(ccc3(255, 0, 0));
        reduB->setAnchorPoint(ccp(0.5, 0));
        reduB->setPosition(ccp(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
        // reduB->setPosition(enemy->getPosition());
        
        enemy->addChild(reduB);
        
        enemy->addChild(tx);
        CCActionInterval *a_jianxue=CCMoveTo::create(0.45/Time, ccp(reduB->getPosition().x, reduB->getPosition().y+80));
        // CCActionInterval * set_small=CCScaleBy::create(0, 0);
        CCActionInterval * set_big=CCScaleTo::create(0.4/Time, 1.5);
        //CCActionInterval * set_nor=CCScaleTo::create(0.4/Time, 1);
        CCFadeOut *a_jiaxue_fadeout=CCFadeOut::create(0.5f/Time);
        // CCCallFunc * fun3=CCCallFunc::create(this, callfunc_selector(Fire::removeSprite));
        CCCallFunc * reduceBlood=CCCallFunc::create(this, callfunc_selector(Fire::changeBlood));//changeBlood
        CCFiniteTimeAction *jianxueaction=CCSequence::create(set_big,a_jianxue,a_jiaxue_fadeout,reduceBlood,NULL);
        reduB->runAction(jianxueaction);
        
        zhenping(enemy);
        //    CCShaky3D *shake=CCShaky3D::create(0.3/Time, CCSizeMake(2, 2), 5, false);
        //    enemy->runAction(shake);
    }
    else if(_actionId==98)
    {
        
        this->removeChildByTag(8078,true);
        const char * texiaoname1=sk->skills(_skillId);
        //        char txname1[50]="";
        //        sprintf(txname1, "%s.xml",texiaoname1);
        //        AnimatePacker :: getInstance()->freeAnimations(txname1);
        //texiao->removeFromParent();
        //normalAttack->removeFromParent();
        
        //skillList * sk=new skillList();
        const char * texiaoname=sk->skills(_skillId);
        //        char txname[50]="";
        //        sprintf(txname, "%s.xml",texiaoname);
        //AnimatePacker :: getInstance()->loadAnimations(txname);
        char combine[50]="";
        // AnimatePacker :: getInstance()->loadAnimations(txname);
        sprintf(combine, "%s_01.png",texiaoname);
        mz=CCSprite::createWithSpriteFrameName(combine);
        //texiao->setPosition(ccp(320, 480));
        mz->runAction(AnimatePacker::getInstance()->getAnimate(texiaoname));
        //int idnum=sk->skillnums(_skillId);
        
        
        // mz=texiao::TX()->texiaosCreate(texiaoname, idnum);
        mz->setTag(9098);
        
        //mz=texiao::TX()->mingzhongCreate();
        mz->setPosition(ccp(50, 50));
        char cHp[10]={0};
        sprintf(cHp, "%d",changeHp);
        //label->removeFromParentAndCleanup(true);
        // reduB1=CCLabelTTF::create(cHp,"Marker Felt", 30);
        reduB1=CCLabelAtlas::create(cHp, "number.png", 30, 50, '-');
        reduB1->setColor(ccc3(255, 0, 0));
        reduB1->setAnchorPoint(ccp(0.5, 0));
        reduB1->setPosition(ccp(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
        enemy->addChild(reduB1);
        enemy->addChild(mz);
        
        CCActionInterval * delay=CCDelayTime::create(1);        //CCActionInterval *a_jianxue=CCMoveTo::create(0.45, ccp(reduB1->getPosition().x, reduB1->getPosition().y+80));
        CCCallFunc * reduceBlood=CCCallFunc::create(this, callfunc_selector(Fire::changeBlood));
        CCFiniteTimeAction * final=CCSequence::create(delay,reduceBlood,NULL);
        mz->runAction(final);
        //CCActionInterval * set_small=CCScaleTo::create(0, 0);
        CCActionInterval * set_big=CCScaleTo::create(0.2/Time, 1.5);
        CCActionInterval * set_nor=CCScaleTo::create(0.2/Time, 1);
        
        CCFadeOut *a_jiaxue_fadeout=CCFadeOut::create(0.5f/Time);
        //  CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::MeasureEneDead));
        
        
        //changeBlood
        CCFiniteTimeAction *jianxueaction=CCSequence::create(set_big,set_nor,a_jiaxue_fadeout,NULL);
        reduB1->runAction(jianxueaction);
        zhenping(enemy);
        //        CCShaky3D *shake=CCShaky3D::create(0.3/Time, CCSizeMake(2, 2), 5, false);
        //        enemy->runAction(shake);
        
    }
}
void Fire::MeasureEneDead(CCObject * eneTag){
    
    
    if (_actionId==98) {
        enemy->removeChildByTag(9098,true);
        //mz->removeFromParentAndCleanup(true);
        
    }else if(_actionId==99){
        enemy->removeChildByTag(9099,true);
        //tx->removeFromParentAndCleanup(true);
    }
    if(changeHp+currHp<=0){
        
        CCActionInterval * fadeout=CCFadeOut::create(0.2);
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::removeit));
        CCFiniteTimeAction * final=CCSequence::create(fadeout,func,NULL);
        enemy->runAction(final);
    }
    else{
        this->checkOut();
    }
}
void Fire::removeit(){
    CCSprite * xuetiao=(CCSprite *)this->getChildByTag(1000+eneBID);
    enemy->removeFromParentAndCleanup(true);
    this->removeChild(xuetiao,true);
    this->checkOut();
}
void Fire::MutileMeasureEneDead(CCNode * sender){
    CCLog("%d",sender->getTag());
    
    for (int i=0; i<_length; i++) {
        if(_eneBattId[i]==sender->getTag()){
            CCLog("%d",i);
            if(_eneChanHp[i]+_eneCurrHp[i]>0){
                if (max==1) {
                    max=2;
                    this->SimpleAttack();
                }
                
                
                
            }else{
                
                sender->removeFromParentAndCleanup(true);
            }
        }
    }
}
void Fire::MutileChangeBlood(){
    
    
}
void Fire::changeBlood(){
    CCLog("_eneCurrentPower %d",_eneCurrentPower);
    if (_actionId==98) {
        enemy->removeChildByTag(9098,true);
        reduB1->removeFromParentAndCleanup(true);
        const char * texiaoname=sk->skills(_skillId);
    }else if(_actionId==99){
        enemy->removeChildByTag(9099,true);
        reduB->removeFromParentAndCleanup(true);
    }
    CCSprite * blood=(CCSprite *)enemy->getChildByTag(1000+eneBID);
    double percent;
    CCLog("cur %d  change %d",currHp,changeHp);
    if(currHp+changeHp<=0){
        CCActionInterval *  scal=CCScaleTo::create(0.75/Time, 0, 1);
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::MeasureEneDead));
        // CCActionInterval * delay=CCDelayTime::create(0.2);
        CCFiniteTimeAction *Action=CCSequence::create(scal,func,NULL);
        blood->runAction(Action);
        
    }else if(currHp+changeHp>0){
        
        percent=((double)(currHp+changeHp)/(double)totalHp);
        
        CCLog("%f",percent);
        // cout<<currHp/totalHp<<endl;
        //currHp=currHp+changeHp;
        CCActionInterval *  scal=CCScaleTo::create(0.75/Time, percent, 1);
        // CCActionInterval * delay=CCDelayTime::create(0.2);
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(Fire::MeasureEneDead));
        CCFiniteTimeAction *Action=CCSequence::create(scal,func,NULL);
        blood->runAction(Action);
    }
    
}
void Fire::enemiesLoad(){
    
    //敌人武将头像初始化
    
}
void Fire::playerLoad(){
    //玩家武将头像初始化
    
}
void Fire::jsonData(char *json){
    //此处将server端发送的总json数据进行解析
    Json::Reader read;
    Json::Value value;
    if (read.parse(json, value)) {
        std::string out=value["message"].asCString();
        cout<<out<<endl;
        Json::Value data=value["data"];
        Json::Value setData=data["setData"];
        CCLog("%s",json);
        CData::getCData()->setFireJson(setData);
        this->setJson(setData);
        Json::Value startValue=data["startData"];
        Json::Value array;
        
        const char * name;
        int nengliang;
        int battleId;
        int pinzhi;
        int level;
        float chaCurrentHp;
        float chaTotalHp;
        int icon;
        int chaId;
        
        char tag[2];
        for (int i=0; i<startValue.size(); i++) {
            pos=startValue[i]["chaPos"].asInt();
            
            battleId=startValue[i]["chaBattleId"].asInt();
            
            direction=startValue[i]["chaDirection"].asInt();
            
            level=startValue[i]["chaLevel"].asInt();
            icon=startValue[i]["chaIcon"].asInt();
            pinzhi=startValue[i]["difficulty"].asInt();
            name=startValue[i]["chaName"].asCString();
            nengliang=startValue[i]["chaCurrentPower"].asInt();
            chaTotalHp=startValue[i]["chaTotalHp"].asDouble();
            chaCurrentHp=startValue[i]["chaCurrentHp"].asDouble();
            chaId=startValue[i]["chaId"].asInt();
            
            
            this->setBlood(chaCurrentHp, chaTotalHp, pos,direction);
            CCLog("%d",pinzhi);
            sprintf(tag, "%d%d",direction,pos);
            cout<<name<<endl;
            if(direction==1){
                CCLog("%d",pinzhi);
                if(pos>=1&&pos<=3){
                    CCLog("%d",pinzhi);
                    
                    
                    CCSprite *player1 = CCSprite::create();
                    
                    switch (pinzhi) {
                        case 1:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 2:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 3:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 4:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                        default:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                    }
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    CCSprite *player111=CCSprite::create(iconname);
                    //                    CCSprite *player111=CCSprite::create("qs_0001.png");
                    player111->setScale(0.38);
                    player111->setAnchorPoint(ccp(0, 0));
                    player1->setTag(direction*10+pos);
                    player111->setPosition(ccp(0, 5));
                    player1->setPosition(ccp(size.width/2+(pos-2)*150, size.height/2-70));
                    player1->addChild(player111);
                    char  pinz[40]="";

                    this->addChild(player1);
                    
                    CCSprite * xuetiao =CCSprite::create("PK_blood.png");
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setAnchorPoint(ccp(0, 1));
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setPosition(ccp(2, 5));
                    player1->addChild(xuetiao,2);
                    player1->setScale(0.6);
                    
                }
                
                if (pos>3&&pos<=6) {
                    
                    
                    
                    CCSprite *player1 = CCSprite::create();
                    
                    switch (pinzhi) {
                        case 1:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 2:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 3:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 4:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                        default:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                    }
                    
                    
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    CCSprite *player111=CCSprite::create("qs_0001.png");
                    CCSprite *player111=CCSprite::create(iconname);
                    player111->setScale(0.38);
                    player111->setAnchorPoint(ccp(0, 0));
                    player1->setTag(direction*10+pos);
                    player1->setPosition(ccp(size.width/2+(pos-5)*150, size.height/2-190));
                    player1->addChild(player111);
                    char  pinz[40]="";
                    this->addChild(player1);
                    
                    CCSprite * xuetiao =CCSprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(ccp(0, 1));
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setPosition(ccp(2, 5));
                    player1->addChild(xuetiao,2);
                    player1->setScale(0.6);
                    
                }
                if(pos>6&&pos<=9){
                    
                    
                    CCSprite *player1 = CCSprite::create();
                    
                    switch (pinzhi) {
                        case 1:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 2:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 3:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 4:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                        default:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                    }
                    
                    
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    CCSprite *player111=CCSprite::create("qs_0001.png");
                    CCSprite *player111=CCSprite::create(iconname);
                    player111->setScale(0.38);
                    player1->setTag(direction*10+pos);
                    player1->setPosition(ccp(size.width/2+(pos-8)*150, size.height/2-310));
                    player111->setAnchorPoint(ccp(0, 0));
                    player1->addChild(player111);
                    char  pinz[40]="";
                    this->addChild(player1);
                    
                    CCSprite * xuetiao =CCSprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(ccp(0, 1));
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setPosition(ccp(2, 5));
                    player1->addChild(xuetiao,2);
                    player1->setScale(0.6);
                    
                }
                
            }else if(direction==2){
                
                
                
                CCSprite *ene1 = CCSprite::create();
                
                switch (pinzhi) {
                    case 1:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                    case 2:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                    case 3:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                    case 4:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                        
                    default:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                        
                }
                
                ene1->setScale(0.9);
                
                if(pos>=1&&pos<=3){
                    
                    
                    
                    
                    
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    CCSprite *  ene111=CCSprite::create("qs_0001.png");
                    CCSprite *  ene111=CCSprite::create(iconname);
                    ene111->setScale(0.38);
                    ene1->setTag(direction*10+pos);
                    
                    ene1->setPosition(ccp(size.width/2+(pos-2)*150, size.height/2+65));
                    ene111->setAnchorPoint(ccp(0, 0));
                    ene1->addChild(ene111);
                    char  pinz[40]="";
                    this->addChild(ene1);
                    CCSprite * xuetiao =CCSprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(ccp(0, 1));
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setPosition(ccp(2, 5));
                    ene1->addChild(xuetiao,2);
                    ene1->setScale(0.6);
                    
                }
                if (pos>3&&pos<=6) {
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    
                    //                    CCSprite * ene111=CCSprite::create("qs_0001.png");
                    CCSprite * ene111=CCSprite::create(iconname);
                    ene111->setScale(0.38);
                    ene1->setTag(direction*10+pos);
                    
                    ene1->setPosition(ccp(size.width/2+(pos-5)*150, size.height/2+190));
                    ene111->setAnchorPoint(ccp(0, 0));
                    ene1->addChild(ene111);
                    this->addChild(ene1);
                    char  pinz[40]="";
                    CCSprite * xuetiao =CCSprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(ccp(0, 1));
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setPosition(ccp(2, 5));
                    ene1->addChild(xuetiao,2);
                    ene1->setScale(0.6);
                }
                if(pos>6&&pos<=9){
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    CCSprite *   ene111=CCSprite::create("qs_0001.png");
                    CCSprite *   ene111=CCSprite::create(iconname);
                    ene111->setScale(0.38);
                    ene1->setTag(direction*10+pos);
                    
                    ene1->setPosition(ccp(size.width/2+(pos-8)*150, size.height/2+310));
                    ene111->setAnchorPoint(ccp(0, 0));
                    ene1->addChild(ene111);
                    this->addChild(ene1);
                    char  pinz[40]="";
                    CCSprite * xuetiao =CCSprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(ccp(0, 1));
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setPosition(ccp(2, 5));
                    ene1->addChild(xuetiao,2);
                    ene1->setScale(0.6);
                }
                
            }
            
            
        }
    }
}
void Fire::setBlood(float curB, float nowB, int i,int dir){
    //此处初始化敌方武将血条
}
void Fire::removeSprite(CCNode *sender){
    sender->removeFromParent();
}
void  Fire::setJson(Json::Value json){
    _json=json;
    int coin;
    
    coin=json["star"].asInt();
    CCLog("%d %d",coin,_json["star"].asInt());
}
Json::Value  Fire::getJson(){
    int star=_json["star"].asInt();
    CCLog("%d",star);
    return _json;
}
int Fire::getStar(){
    return NULL;
}
int Fire::result(){
    return battleresult;
}

CCSprite * Fire::moveup(){
    updown=CCSprite::create("smalljiantou.png");
    CCActionInterval * up=CCMoveBy::create(0.5/Time, ccp(updown->getPosition().x, updown->getPosition().y+20));
    CCActionInterval * down=CCMoveBy::create(0.5/Time, ccp(updown->getPosition().x, updown->getPosition().y-20));
    CCFiniteTimeAction * final=CCSequence::create(up,down,NULL);
    CCRepeatForever * rep=CCRepeatForever::create((CCActionInterval *)final);
    updown->runAction(rep);
    return updown;
}



skill * Fire::returnskills(int skillId){
    //    const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("skill.json").c_str();
    //    ifstream ifs;
    //    ifs.open(path);
    //    assert(ifs.is_open());
    Json::Reader read;
    Json::Value root;
    Json::Value data;
    Json::Value row;
    char skillss[40]="";
    sprintf(skillss, "%d",skillId);
    skill * skills=new skill();
    skills->autorelease();
    
    
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("skill.json");
    CCString* str = CCString::createWithContentsOfFile(path.c_str());
    
    
    if(read.parse(str->getCString(), root)){
        data=root[skillss];
        
        
        skills->releaseEffect=data["releaseEffect"].asInt();
        skills->throwEffectId=data["throwEffectId"].asInt();
        skills->bearEffect=data["bearEffect"].asInt();
    }
    //    ifs.close();
    return skills;
}


void Fire::onExit()
{
    AnimatePacker :: getInstance()->freeAnimations ("qishouTX.xml");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName ("result_attacked.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName ("jn_name.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName ("begin1.plist");
    
    CCLayer::onExit();
    
    //    player_dic->removeAllObjects();
    //    player_dic->release();
    
}

void Fire::recv_4501(){
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(4501);
    CData::getCData()->m_dictionary->removeObjectForKey(4501);
    
    if(revMsg){
        
        this->unschedule(schedule_selector(Fire::recv_4501));
        char* data=revMsg->data;
        Json::Reader read;
        Json::Value value;
        if(read.parse(data, value))
        {
            
            if (value["result"].asBool()) {
                CData::getCData()->setdata(data);
                CData::getCData()->setczorzy(true);
                initFireData();
            }
            else
            {

            }
            
            CCLog("%s",data);
        }
    }
    
}





