//
//  friendemploy.cpp
//  wx
//
//  Created by guoyahui on 13-6-26.
//
//

#include "friendemploy.h"
#include "CData.h"
#include "SocketManager.h"
#include "json.h"
#include <limits>
#include "CustomPop.h"
#include "homePage.h"


bool friendemploy::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    arrPassLevel = CCArray::create();
    arrPassLevel->retain();
    
    arrUserLevel = CCArray::create();
    arrUserLevel->retain();
    
    arrAllUser = CCArray::create();
    arrAllUser->retain();
    
    indexAllUser = 0;
    indexPassLevel = 0;
    indexUserLevel = 0;
    
    finishAllUserData = false;
    finishPassLevelData = false;
    finishUserLevelData = false;
    
    this->setTouchEnabled(true);
    size = CCDirector::sharedDirector()->getWinSize();
    selectIndex = -1;
    
    
    CCSprite* bkg = CCSprite::create("zjm_bkg.png");//zjm_bkg.png
    bkg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bkg);
    CCSprite* ebkg = CCSprite::create("employ_bkg.png");
    ebkg->setPosition(ccp(size.width/2, size.height/2-5));
    this->addChild(ebkg);
    btn2 = CCMenuItemImage::create("kong.png", "kong.png");
//    btn2->setAnchorPoint(ccp(0, 0));
    btn2->setTag(TAB_USER_LEVEL);
    btn2->setScale(1.3);   
    
    menu = CCMenu::create(btn2,NULL);
    menu->alignItemsHorizontallyWithPadding(0);
    menu->setPosition(ccp(100, 567));
    this->addChild(menu);
    
    tableView = CCTableView::create(this, CCSizeMake(0,0));
    //tableView->setContentSize(CCSizeMake(420, 600)) ;
    tableView->setViewSize(CCSizeMake(420,490));//420,490
    
    
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setAnchorPoint(ccp(0, 0));
    //tableView->setContentOffset(ccp(0,0));
    tableView->setPosition(ccp(30,150));//30,150
    tableView->setDelegate(this);
    this->addChild(tableView);
    changeTab(btn2);
//    tableView->reloadData();

//    send_302();
    
    return true;
}



void friendemploy::send_employ(friendinfo* info)
{
    CCLog("friendemploy::send_employ");
    
    load = Loading::create();
    this->addChild(load, 9999);
    
    
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    root["friendid"] = info->userid ;

    
    
    string json_file=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 2301);
    this->schedule(schedule_selector(friendemploy::rec_info));

    //    tableView->reloadData();
}


void friendemploy::send_302()
{
    
    load = Loading::create();
    this->addChild(load, 9999);
    
    
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    root["tag"] = selectIndex;
    switch (selectIndex) {
        case TAB_ALL_USER:

            root["index"] = indexAllUser;
            break;
        case TAB_PASS_LEVEL:
 
            root["index"] = indexPassLevel;
            break;
        case TAB_USER_LEVEL:
   
            root["index"] = indexUserLevel;
            break;
        default:
            CustomPop::show("好友界面错误！");
            return;
            break;
    }
    string json_file=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 302);
    CCLog("%s",json_file.c_str());
    this->schedule(schedule_selector(friendemploy::rec_302)); 
}
void friendemploy::rec_302()
{
   
    
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(302);
    CData::getCData()->m_dictionary->removeObjectForKey(302);
    
    //CCLog("%s",revMsg->data);
    if(revMsg)
    {
        
        load->removeFromParent();
        
        this->unschedule(schedule_selector(friendemploy::rec_302));
        
        
        char* data=revMsg->data;
        CCLog("%s",data);
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;
        Json::Value list;
        
        
        if(read.parse(data, root))
        {
            
            jsonData=root["data"];
            list = jsonData["friendlist"];
            
            switch (selectIndex)
            {
                case TAB_ALL_USER:
                    indexAllUser = jsonData["end"].asInt();
                    finishAllUserData = !jsonData["sp"].asBool();
                    
                    for (int i = 0; i<list.size(); i++) {
                        friendinfo* info = new friendinfo();
                        info->autorelease();
                        info->userid = list[i]["chaid"].asInt();
                        info->name = list[i]["rolename"].asString();
                        info->skill = list[i]["skill"].asString();
                        info->price = list[i]["price"].asInt();
                        info->rank = list[i]["rank"].asInt();
                        info->skill = list[i]["skill"].asString();
                        info->level = list[i]["level"].asInt();
                        info->guyong = list[i]["guyong"].asBool();
                        arrAllUser->addObject(info);
                    }
                    break;
                case TAB_PASS_LEVEL:
                    indexPassLevel = jsonData["end"].asInt();
                    finishPassLevelData = !jsonData["sp"].asBool();
                    
                    for (int i = 0; i<list.size(); i++) {
                        friendinfo* info = new friendinfo();
                        info->autorelease();
                        info->userid = list[i]["chaid"].asInt();
                        info->name = list[i]["rolename"].asString();
                        info->skill = list[i]["skill"].asString();
                        info->price = list[i]["price"].asInt();
                        info->rank = list[i]["rank"].asInt();
                        info->skill = list[i]["skill"].asString();
                        info->level = list[i]["level"].asInt();
                        info->guyong = list[i]["guyong"].asBool();
                        arrPassLevel->addObject(info);
                        
                    }
                    break;
                case TAB_USER_LEVEL:
                    indexUserLevel = jsonData["end"].asInt();
                    finishUserLevelData= !jsonData["sp"].asBool();
                    
                    for (int i = 0; i<list.size(); i++) {
                        friendinfo* info = new friendinfo();
                        info->autorelease();
                        info->userid = list[i]["chaid"].asInt();
                        info->name = list[i]["rolename"].asString();
                        info->skill = list[i]["skill"].asString();
                        info->price = list[i]["price"].asInt();
                        info->rank = list[i]["rank"].asInt();
                        info->skill = list[i]["skill"].asString();
                        info->level = list[i]["level"].asInt();
                        info->guyong = list[i]["guyong"].asBool();
                        arrUserLevel->addObject(info);
                    }
                    break;
                default:
                    CustomPop::show("好友界面错误！");
                    return;
                    break;
            }

            
        }
//        float h ;
//        h = tableView->getContentSize().height;
        tableView->reloadData();
        float h1 = tableView->getContentSize().height;
        tableView->setContentOffset(ccp(0, offsetTable-h1));
        offsetTable = h1;
    }

    
    
}



void friendemploy::changeTab(CCObject* sender)
{
    CCMenuItemImage* btn = (CCMenuItemImage*)sender;
    if(btn)
    {
       int index = btn->getTag();
        
        if(selectIndex == index)
        {
            btn->selected();
            return;
        }
        offsetTable = 490;
        selectIndex = index;
        
                
        switch (selectIndex) {
            case TAB_PASS_LEVEL:
//                btn1->unselected();
                btn2->unselected();
//                btn3->unselected();
//                btn1->selected();
                arrPassLevel->removeAllObjects();
                if (arrPassLevel->count()<1) {
                    finishPassLevelData = false;
                    indexPassLevel = 0;
                    send_302();
                }
                break;
            case TAB_USER_LEVEL:
//                btn1->unselected();
//                btn2->unselected();
//                btn3->unselected();
                btn2->selected();
                arrUserLevel->removeAllObjects();
                if (arrUserLevel->count()<1) {
                    finishUserLevelData = false;
                    indexUserLevel = 0;
                    send_302();
                }
                break;
            case TAB_ALL_USER:
//                btn1->unselected();
                btn2->unselected();
//                btn3->unselected();
//                btn3->selected();
                if (arrAllUser->count()<1) {
                    finishAllUserData = false;
                    indexAllUser = 0;
                    send_302();
                }
                break;
                
            default:
                break;
        }
        
        
        
//         tableView->reloadData();
    
        
        
       

    }
}

void friendemploy::rec_info()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(2301);
    CData::getCData()->m_dictionary->removeObjectForKey(2301);

    if(revMsg)
    {
        
        load->removeFromParent();
        
        this->unschedule(schedule_selector(friendemploy::rec_info));
        
        
        char* data=revMsg->data;
        CCLog("%s",data);
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;
        Json::Value list;
        
        
        if(read.parse(data, root))
        {
            
//            jsonData=root["data"];
            
            bool  ischenggong = root["result"].asBool();
            
            if (ischenggong) {
                CustomPop::show("雇佣英雄成功！");
                
                CCNotificationCenter::sharedNotificationCenter()->postNotification("refresh_zhuangtai");
                
            }
            else{
                string out = root["messge"].asCString();
                CustomPop::show(out.c_str());
            }
                        
        }
        }
    
    

    
}



 void friendemploy::scrollViewDidScroll(CCScrollView* view)
{
    
}
 void friendemploy::scrollViewDidZoom(CCScrollView* view)
{
    
}



//处理触摸事件，可以计算点击的是哪一个子项
void friendemploy::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("点击了  %d",cell->getIdx());
    if (cell->getChildByTag(ADD_MORE_TAG))
    {
        send_302();
    }
    else
    {
        if (selectIndex != TAB_ALL_USER) {
            tmpCell = (FriendEmployCell*)cell;
            tmpCell->changeState();
            tmpid = cell->getIdx();
        }

    }
}
//每一项的宽度和高度
 CCSize friendemploy::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(420, 90);
}
//生成列表每一项的内容
 CCTableViewCell* friendemploy::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    
    
    
    FriendEmployCell *cell = NULL;// table->dequeueCell();
    
    
//    if(!cell)
//    {
//        cell = new CCTableViewCell();
//        
//        cell->autorelease();
        
        cell =new FriendEmployCell();

        
//        CCScale9Sprite* spp = CCScale9Sprite::create("employfriend_item_bkg.png");
        int w = 420;
        int h = 80;
//        spp->setContentSize(CCSizeMake(w, h));
//        spp->setAnchorPoint(ccp(0, 0));
//        cell->addChild(spp);
        
        bool isLast = false;
        switch (selectIndex) {
            case TAB_ALL_USER:
                if(!finishAllUserData)
                {
                    indexAllUser == idx ? isLast = true : isLast = false;
                }
                break;
            case TAB_PASS_LEVEL:
                
                if(!finishPassLevelData)
                {
                indexPassLevel == idx ? isLast = true : isLast = false;
                }
                break;
            case TAB_USER_LEVEL:
                if(!finishUserLevelData)
                {
                indexUserLevel == idx ? isLast = true : isLast = false;
                }
                break;
            default:
                
                break;
        }
        
        if(isLast)
        {
            CCTableViewCell* cell1 = new CCTableViewCell();
            cell1->autorelease();
            CCLabelTTF* addmore = CCLabelTTF::create("加载更多数据.....", "hycc.ttf", 18);
            addmore->setPosition(ccp(195, h/2));
            addmore->setTag(ADD_MORE_TAG);
            cell1->addChild(addmore);
            
            return cell1;

        }
        
        
        
        friendinfo* info;
        
        
        switch (selectIndex) {
            case TAB_ALL_USER:
                info = (friendinfo*)arrAllUser->objectAtIndex(idx);
                break;
            case TAB_PASS_LEVEL:
                info = (friendinfo*)arrPassLevel->objectAtIndex(idx);
                break;
            case TAB_USER_LEVEL:
                info = (friendinfo*)arrUserLevel->objectAtIndex(idx);
                break;
            default:
               
                break;
        }
        
        cell->setFriendInfo(info);
        
        return cell;
        
}
//一共多少项
 unsigned int friendemploy::numberOfCellsInTableView(CCTableView *table)
{
    
    switch (selectIndex) {
        case TAB_PASS_LEVEL:
            
            if (finishPassLevelData) {
                return arrPassLevel->count();
            }
            
            return arrPassLevel->count() + 1 ;
            
            
            break;
            
        case TAB_USER_LEVEL:
            
            if (finishUserLevelData) {
                return arrUserLevel->count();
            }
            
            return arrUserLevel->count() + 1;
            
            break;
            
        case TAB_ALL_USER:
            
            if (finishAllUserData) {
                return arrAllUser->count();
            }
            
            return arrAllUser->count() + 1;
            
            break;
            
            
        default:
            break;
    }
    
    return 0;
}

void friendemploy::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}

bool friendemploy::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    istouch=tableView->ccTouchBegan(touch, event);
    istouchex = menu->ccTouchBegan(touch, event);
    if(istouch || istouchex)
    {
        return true;
    }
    else
    {
        return false;
    }
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void friendemploy::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if(istouch){
        
        tableView->ccTouchMoved(touch, event);
    
    }
    if (istouchex) {
        menu->ccTouchMoved(touch, event);
    }
    
}
void friendemploy::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    if (istouch) {
        tableView->ccTouchEnded(touch, event);
        
        
        
        
    }
    
    if (istouchex) {
        menu->ccTouchEnded(touch, event);
        
        
    }
    istouch=false;
    istouchex = false;
    
}


