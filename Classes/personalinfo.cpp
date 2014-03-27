//
//  personalinfo.cpp

#include "personalinfo.h"
#include "CData.h"
#include "hcitemdata.h"
#include "LayerLogin.h"
#include "message.h"
#include "SocketManager.h"
#include "CustomPop.h"
#include "homePage.h"

bool personalinfo::init()
{
    if(!CCLayerColor::init())
    {
        return false;
    }
     size = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);

    lock = false;
    
    this->setTouchEnabled(true);
    dragingsp = goodsItem::create();
    this->addChild(dragingsp,1000);
    dragingsp->setVisible(false);
    draging = false;
    readdraging = false;
    
    tooltip = tiplayer::create();
    
    CCSize tmpsz = tooltip->getContentSize();
    tooltip->setPosition(ccp((size.width-tmpsz.width)/2, 350));
    this->addChild(tooltip,1111);
    tooltip->setVisible(false);
    
    CCSprite *bkgInfo=CCSprite::create("zjm_bkg.png");
    bkgInfo->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bkgInfo);
    bj = CCSprite::create("personalinfo_bkg.png");
    bj->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bj);
    
    ccColor3B color = ccc3(30, 30, 10);
    shang = CCLabelTTF::create("", "hycc.ttf", 22);//Helvetica
    shang->setPosition(ccp(185, 390));
    shang->setColor(color);
    this->addChild(shang);
    
    
    fang = CCLabelTTF::create("", "hycc.ttf", 22);
    fang->setPosition(ccp(247, 390));;
    fang->setColor(color);
    this->addChild(fang);
    
    
    min = CCLabelTTF::create("", "hycc.ttf", 22);
    min->setPosition(ccp(302, 390));
    min->setColor(color);
    this->addChild(min);
    
    itemArr = CCDictionary::create();
    itemArr->retain();
    CCSize sz;
    int kk;
    
    for (int i = 0; i < 10; i++) {
        goodsItem * item = goodsItem::create();
        sz = item->getContentSize();
        kk = sz.width-45;

        itemArr->setObject(item, i+7);
        
        
        item->setAnchorPoint(ccp(0, 1));
        item->setPosition(ccp(((size.width - kk*5)/6 + kk) * (i%5 + 1) -kk-20,   -80 * (i/5) + 290));
        this->addChild(item);
        
    }
    

    
    e1 = goodsItem::create();
    e1->setPosition(ccp(size.width/2-140, size.height/2+150));
    this->addChild(e1);
    
    e2 = goodsItem::create();
    e2->setPosition(ccp(size.width/2-140, size.height/2+50));
    this->addChild(e2);

    e3 = goodsItem::create();
    e3->setPosition(ccp(size.width/2-140, size.height/2-30));
    this->addChild(e3);

    e4 = goodsItem::create();
    e4->setPosition(ccp(size.width/2+140, size.height/2+150));
    this->addChild(e4);

    e5 = goodsItem::create();
    e5->setPosition(ccp(size.width/2+140, size.height/2+50));
    this->addChild(e5);

    e6 = goodsItem::create();
    e6->setPosition(ccp(size.width/2+140, size.height/2-30));
    this->addChild(e6);

    itemArr->setObject(e1, 1);
    itemArr->setObject(e2, 2);
    itemArr->setObject(e3, 3);
    itemArr->setObject(e4, 4);
    itemArr->setObject(e5, 5);
    itemArr->setObject(e6, 6);
    
    
    loading =Loading::create();
    this->addChild(loading,999);
    
//    return true;
    
    send_203();

//    refresh_203();
//    refresh_204();

    return true;
}


void personalinfo::refresh_203()
{
    const char * jsondata=CData::getCData()->getZGBagInfo();
    CCLog("%s",jsondata);
    Json::Reader read;
    Json::Value root;
    Json::Value data;
    Json::Value equip;
    Json::Value item;
    
    e1->clData();
    e2->clData();
    e3->clData();
    e4->clData();
    e5->clData();
    e6->clData();
    
    if(read.parse(jsondata, root)){
        data=root["data"];
        equip=data["equip"];
        CCLog("%d",equip.size());
        for (int i=0; i<equip.size(); i++) {
            hcitemdata * tmp = new hcitemdata();
            tmp->tempid = equip[i]["item"]["tempid"].asInt();
            //CCLog("%d",tmp->tempid);
            tmp->itemid = equip[i]["item"]["itemid"].asInt();
            CCLog("%d",tmp->itemid);
            tmp->exp = equip[i]["exp"].asInt();
            CCLog("%d",tmp->exp);
            switch (equip[i]["pos"].asInt()) {
                case 1:
                   
                    e1->setData(tmp);
                    break;
                case 2:
                    
                    e2->setData(tmp);
                    break;
                case 3:
                    
                    e3->setData(tmp);
                    break;
                case 4:
                    
                    e4->setData(tmp);
                    break;
                case 5:
                    
                    e5->setData(tmp);
                    break;
                case 6:
                    
                    e6->setData(tmp);
                    break;
                    
                default:
                    break;
            }
            
            
        }
        
        char a[10] = "";
        
        sprintf(a, "%d",data["attack"].asInt());
        shang->setString(a);
        sprintf(a, "%d",data["minjie"].asInt());
        min->setString(a);
        sprintf(a, "%d",data["fangyu"].asInt());
        fang->setString(a);
        
        
        this->removeChild(headsp);
        headsp = CCSprite::create();
        headsp->setScale(0.38);
        int sex = CData::getCData()->getSex();
        if(sex == 1)
        {
            headsp->initWithFile("qs_0001.png");
        }
        else if (sex == 2)
        {
            headsp->initWithFile("qs_0002.png");
        }
        else
        {
            headsp->initWithFile("qs_0003.png");
        }
        //CCSize sz= bigcardbkg->getContentSize();
        //headsp->setPosition(ccp(sz.width/2, sz.height/2));
        headsp->setPosition(ccp(size.width/2, 510));
        bj->addChild(headsp);
  
    }

}

void personalinfo::refresh_204()
{
    
    loading->removeFromParent();
    
    goodsItem * tmpgoodsitem;
    hcitemdata *tmpitemdata;
    
    for (int i = 0; i < 10; i++) {
         tmpgoodsitem =(goodsItem*) itemArr->objectForKey(i+7);
         tmpgoodsitem->clData();
    }
    Json::Reader read;
    Json::Value root;
    Json::Value data;
    Json::Value equip;
    Json::Value item;
    const char *jsondata1= CData::getCData()->getEquipInfo();
     CCLog("%s",jsondata1);
    if (read.parse(jsondata1,root)) {
        data = root["data"];
        equip = data["itemlist"];
        for (int j = 0; j<equip.size(); j++) {
            tmpitemdata = new hcitemdata();
            tmpitemdata->tempid = equip[j]["tempid"].asInt();
            tmpitemdata->itemid = equip[j]["itemid"].asInt();
            tmpitemdata->exp = equip[j]["exp"].asInt();
//            tmpitemdata->icon = equip[j]["icon"].asInt();
//            tmpitemdata->num = equip[j]["stack"].asInt();
            
            tmpgoodsitem =(goodsItem*) itemArr->objectForKey(j+7);
            if(tmpgoodsitem)
            {
                tmpgoodsitem->setData(tmpitemdata);
            }
            else{
                CCLog("物品太多了！！！！");
            }
            
        }
    }

}


void personalinfo::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}


bool personalinfo::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    if(lock)
    {
        return false;
    }

    CCPoint touchPoint=convertTouchToNodeSpace(touch);
    if (touchPoint.y < 80 || touchPoint.y > size.height - 180) {
        return false;
    }

    goodsItem* item;
    int len = itemArr->count();
    
    for (int i = 1; i<=len; i++) {
        item =(goodsItem*) itemArr->objectForKey(i);
        if(item && item->boundingBox().containsPoint(touchPoint))
        {
            if(draging)
            {
                CustomPop::show("错误！");
            }
            else
            {
                if(item->itemdata)
                {
                    readdraging = true;
                    readydragingsp = item;
                    dragingindex = i;
                    tooltip->setVisible(true);
                    tooltip->setData(item->itemdata);
                   
                    //Setting position of tip
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
            
            
            break;
        }
    }
    return true;
}

void personalinfo::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    tooltip->setVisible(false);
    CCPoint touchPoint=convertTouchToNodeSpace(touch);
    
    if (readdraging) {
        draging = true;
        dragingsp->setData(readydragingsp->itemdata);
        dragingsp->setVisible(true);
        dragingsp->setPosition(touchPoint);
        readdraging = false;
    }
    
    
    
    if(draging)
    {
        dragingsp->setPosition(touchPoint);
    }
//    if(istouch){
//        
//        btnsMenu->ccTouchMoved(touch, event);
//    }
}
void personalinfo::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCPoint touchPoint=convertTouchToNodeSpace(touch);

    
    readdraging = false;
    
    tooltip->setVisible(false);
    
    if(draging)
    {
        
        draging = false;
//        dragingsp->setVisible(false);
        
//        acceptsp = NULL;
        goodsItem* item;
        int len = itemArr->count();
        
        for (int i = 1; i<=len; i++) {
            item =(goodsItem*) itemArr->objectForKey(i);
            if(item && item->boundingBox().containsPoint(touchPoint))
            {
                acceptsp = item;
                acceptindex = i;
                break;
            }
        }
        
        if(acceptsp)
        {
            
            if(dragingindex > 6)
            {
                if(acceptindex > 6)
                {
                    if(dragingindex != acceptindex && acceptsp->itemdata)
                    {
                        //物品吞噬
                        loading =Loading::create();
                        this->addChild(loading,999);

                        send_212();
                        
                    }
                }
                else
                {
                    loading =Loading::create();
                    this->addChild(loading,999);

                    send_210();

                }
                
            }
            else
            {
                if(acceptindex > 6)
                {
                    if(acceptsp->itemdata)
                    {
                        
                    }
                    else
                    {
                        //脱下装备
                        loading =Loading::create();
                        this->addChild(loading,999);

                        send_215();
                    }
                }
            }
            
            draging = false;
            dragingsp->setVisible(false);
            
            acceptsp = NULL;
            
        }
        else{
            
        }
        

    }
    
    

}

void personalinfo::send_203()
{

    int characterId=CData::getCData()->getCharactorId();
    Json::FastWriter writer;
    Json::Value sendMessage;
    sendMessage["characterId"]=characterId;
    std::string json_file_zg=writer.write(sendMessage);
       
    SocketManager::getInstance()->sendMessage(json_file_zg.c_str(), 203);
    this->schedule(schedule_selector(personalinfo::rec_203));
}

void personalinfo::rec_203()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(203);
    CData::getCData()->m_dictionary->removeObjectForKey(203);
    //CCLog("%s",revMsg);
    if(revMsg){
        char * data=revMsg->data;
        CCLog("%s",data);
        CData::getCData()->setZGBagInfo(data);
        this->unschedule(schedule_selector(personalinfo::rec_203));
        
        send_204();
        
    }

}

void personalinfo::send_204()
{
    int characterId=CData::getCData()->getCharactorId();
    Json::FastWriter writer;
    Json::Value sendMessage;
    sendMessage["characterId"]=characterId;
    std::string json_file_zg=writer.write(sendMessage);
    
    SocketManager::getInstance()->sendMessage(json_file_zg.c_str(), 204);
    this->schedule(schedule_selector(personalinfo::rec_204));

}

void personalinfo::rec_204()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(204);
    CData::getCData()->m_dictionary->removeObjectForKey(204);
    if(revMsg){
        char * data=revMsg->data;
        CCLog("%s",data);
        CData::getCData()->setEquipInfo(data);
        this->unschedule(schedule_selector(personalinfo::rec_204));
        
        refresh_203();
        refresh_204();
        
        lock = false;
    }
}

void personalinfo::send_210()
{
    lock = true;
    int characterID = CData::getCData()->getCharactorId();
    Json::FastWriter  writer;
    
    Json::Value person;
    
    person["characterId"]=characterID;
    person["itemid"]= dragingsp->itemdata->itemid;
    
    
    std::string  json_file=writer.write(person);
        
  
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 210);
    

    
    this->schedule(schedule_selector(personalinfo::rec_210));
    

}

void personalinfo::rec_210()
{
    Message* revMsg = (Message*)CData::getCData()->m_dictionary->objectForKey(210);
    CData::getCData()->m_dictionary->removeObjectForKey(210);
    
    if(revMsg)
    {
        this->unschedule(schedule_selector(personalinfo::rec_210));
        char * data = revMsg->data;
        
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;

        
        if(read.parse(data, root)){
            bool result=root["result"].asBool();
            
            if(result)
            {
                send_203();
            }
            else
            {
               CustomPop::show(root["message"].asString().c_str());
                loading->removeFromParent();
                lock = false;
            }
        }
         
    }
    
}

void personalinfo::send_212()
{
    lock = true;
    int characterID = CData::getCData()->getCharactorId();
    Json::FastWriter  writer;
    
    Json::Value person;
    
    person["characterId"]=characterID;
    person["itemid"]= acceptsp->itemdata->itemid;
    person["toitemid"] = dragingsp->itemdata->itemid;
    
    std::string  json_file=writer.write(person);
    
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 212);

    
    this->schedule(schedule_selector(personalinfo::rec_212));

}

void personalinfo::rec_212()
{
    Message* revMsg = (Message*)CData::getCData()->m_dictionary->objectForKey(212);
    CData::getCData()->m_dictionary->removeObjectForKey(212);
    
    if(revMsg)
    {
        this->unschedule(schedule_selector(personalinfo::rec_212));
        char * data = revMsg->data;
        
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;
        
        
        if(read.parse(data, root)){
            bool result=root["result"].asBool();
            if(result)
            {
                send_203();
            }
            else
            {
                CustomPop::show(root["message"].asString().c_str());
                loading->removeFromParent();
                 lock = false;
            }
        }
        
    }

}

void personalinfo::send_215()
{
    lock = true;
    int characterID = CData::getCData()->getCharactorId();
    Json::FastWriter  writer;
    
    Json::Value person;
    
    person["characterId"]=characterID;
    person["itemid"]= dragingsp->itemdata->itemid;
    
    std::string  json_file=writer.write(person);
    
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 215);
    
    this->schedule(schedule_selector(personalinfo::rec_215));

}

void personalinfo::rec_215()
{
    Message* revMsg = (Message*)CData::getCData()->m_dictionary->objectForKey(215);
    CData::getCData()->m_dictionary->removeObjectForKey(215);
    
    if(revMsg)
    {
        this->unschedule(schedule_selector(personalinfo::rec_215));
        char * data = revMsg->data;
        
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;
        
        
        if(read.parse(data, root)){
            bool result=root["result"].asBool();
            if(result)
            {
                send_203();
            }
            else
            {
                CustomPop::show(root["message"].asString().c_str());
                loading->removeFromParent();
                 lock = false;
            }
        }
        
    }

}


void personalinfo::onExit()
{
    CCLog("personalinfo onExit");
    CCLayerColor::onExit();
}

personalinfo::~personalinfo()
{
    CCLog("personalinfo destroy");
}






