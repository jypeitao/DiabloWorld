
#include "ArenaWindow.h"
//#include "json/json.h"
#include "CData.h"
#include "SocketManager.h"
#include "CustomPop.h"
#include "FireWork.h"

bool ArenaWindow::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bkg = CCSprite::create("zjm_bkg.png");
    bkg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bkg);
    
    CCSprite *jfbkg=CCSprite::create("arenawindow_bkg.png");
    jfbkg->setPosition(ccp(size.width/2, size.height/2-5));
    this->addChild(jfbkg);

    CData::getCData()->isArenaFire = false;
    
    send_3700();
    
    return true;
}

void ArenaWindow::send_3700()
{
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    
    
    string json_file=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 3700);
    this->schedule(schedule_selector(ArenaWindow::recv_3700));
    load = Loading::create();
    this->addChild(load, 9999);

}

void ArenaWindow::clk_battle(CCNode* sender)
{
    int tid =  sender->getTag();
    
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    root["tid"] = tid;
    
    string json_file=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 3704);
    this->schedule(schedule_selector(ArenaWindow::recv_3704));
    load = Loading::create();
    this->addChild(load, 9999);

    }

void ArenaWindow::recv_3704()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(3704);
    CData::getCData()->m_dictionary->removeObjectForKey(3704);
    
    if(revMsg){
        
        load->removeFromParent();
        this->unschedule(schedule_selector(ArenaWindow::recv_3704));
        char* data=revMsg->data;
        
        
        Json::Reader read;
        Json::Value value;
        if(read.parse(data, value))
        {
            
            if (value["result"].asBool()) {
                
                CData::getCData()->setdata(data);
                CData::getCData()->setczorzy(true);
//                CData::getCData()->battleCityId = this->item->bid;
                CCScene *scene=Fire::scene();
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
                CData::getCData()->isArenaFire = true;

                
            }
            else
            {
                CustomPop::show(value["message"].asString().c_str());
            }
            
        
        }
        
    }
}

void ArenaWindow::recv_3700()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(3700);
    CData::getCData()->m_dictionary->removeObjectForKey(3700);
    
    
    if(revMsg)
    {
        load->removeFromParent();
        
        this->unschedule(schedule_selector(ArenaWindow::recv_3700));
        char* data=revMsg->data;
        CCLog("%s",data);
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;
        Json::Value petlist;
        
        
        if(read.parse(data, root)){
            
            CCSprite* sp = CCSprite::create();
            
            jsonData=root["data"];
            petlist=jsonData["dsList"];
            
            int sptimes = jsonData["sptimes"].asInt();
            
            char titlechar[100] = "";
            sprintf(titlechar, "当前排名：%d  今日挑战剩余次数：%d",jsonData["ranking"].asInt(),jsonData["sptimes"].asInt());
            CCLabelTTF* titel = CCLabelTTF::create(titlechar, "hycc.ttf", 22,CCSizeMake(400, 0),kCCTextAlignmentCenter);
            titel->setColor(ccc3(255, 219, 160));
            titel->setPosition(ccp(size.width/2, 600));
            this->addChild(titel);
            
            int len = petlist.size();
            
            for (int i=0; i<len; i++) {
                
                CCScale9Sprite* item = CCScale9Sprite::create("arena_item_bkg.png");
                item->setContentSize(CCSizeMake(410, 85));
                char rank[10] = "";
                sprintf(rank, "%d",jsonData["dsList"][i]["ranking"].asInt());
                CCLabelTTF* ranking = CCLabelTTF::create(rank, "hycc.ttf", 20,CCSizeMake(200, 0),kCCTextAlignmentCenter);
                //ranking->setColor(ccc3(255, 219, 160));
                ranking->setPosition(ccp(37, 42));
                item->addChild(ranking);
                
                CCLabelTTF* nickname = CCLabelTTF::create(jsonData["dsList"][i]["nickname"].asString().c_str(), "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentLeft);
                nickname->setColor(ccc3(255, 219, 160));
                nickname->setAnchorPoint(ccp(0, 0));
                nickname->setPosition(ccp(85, 30));
                item->addChild(nickname);
                
                char levelchar[10] = "";
                sprintf(levelchar, "%d级",jsonData["dsList"][i]["level"].asInt());
                CCLabelTTF* level = CCLabelTTF::create(levelchar, "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentLeft);
                level->setAnchorPoint(ccp(0, 0));
                level->setColor(ccc3(255, 219, 160));
                level->setPosition(ccp(180, 30));
                item->addChild(level);
                
                if (sptimes != 0) {
                    CCMenuItemImage* ok = CCMenuItemImage::create("arena_btn_bat_1.png", "arena_btn_bat_2.png", this, menu_selector(ArenaWindow::clk_battle));
                    ok->setTag(jsonData["dsList"][i]["characterId"].asInt());
                    CCMenu* menu = CCMenu::create();
                    menu->setAnchorPoint(ccp(0, 0));
                    menu->setPosition(ccp(370, 40));
                    menu->addChild(ok);
                    item->addChild(menu);
                }
                
                
                CCSprite* qsbkg = CCSprite::create("common_qs_bkg_4.png");
                qsbkg->setScale(1.0);
                
                int pro = jsonData["dsList"][i]["profession"].asInt();
                
                char prochar[20] = "";
                sprintf(prochar, "qs_%04d.png",pro);
                
                CCSprite* headsp = CCSprite::create(prochar);
                headsp->setScale(0.18);
                headsp->setAnchorPoint(ccp(0, 0));
                qsbkg->addChild(headsp);
                
                qsbkg->setPosition(ccp(265, 38));
                item->addChild(qsbkg);
                
                
                
                item->setAnchorPoint(ccp(0.5, 1));
                item->setPosition(ccp(0,-i*82));//82
                sp->addChild(item);

            }
            sp->setPosition(ccp(size.width/2, 560));
            this->addChild(sp);
        }
    }

}