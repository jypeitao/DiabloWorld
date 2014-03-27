
#include "MailWindow.h"
#include "SocketManager.h"
#include "CData.h"
#include "json.h"
#include <limits>
#include "MailInfo.h"
#include "MailRead.h"
#include "MailWrite.h"

bool MailWindow::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    arr= CCArray::create();
    arr->retain();
    CCSprite *mbkg=CCSprite::create("zjm_bkg.png");
    mbkg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(mbkg);

    CCSprite* bkg = CCSprite::create("mailwindow_bkg.png");
    bkg->setPosition(ccp(size.width/2, size.height/2-5));
    this->addChild(bkg);

    
    CCMenuItemImage* btn_write= CCMenuItemImage::create("mail_btn_write_1.png", "mail_btn_write_2.png", this, menu_selector(MailWindow::clk_btn_write));
    
    CCMenu* menu = CCMenu::create(btn_write,NULL);
    menu->setPosition(ccp(size.width/2, 180));//ccp(size.width-100, 155)
    this->addChild(menu);

    
    
    int w = 420;
    int h = 430;
    tableView = CCTableView::create(this,CCSizeMake(0, 0));
    
    tableView->setViewSize(CCSizeMake(420, 420));
    //    tableView->setContentSize(CCSizeMake(0, 0)) ;
    tableView->setContentOffset(ccp(0, 400-140));
    tableView->setVerticalFillOrder(kCCTableViewFillBottomUp);
    tableView->setAnchorPoint(ccp(0, 0));
    
    tableView->setPosition(ccp(30,210));
    tableView->setDelegate(this);
    this->addChild(tableView);
    
    
    
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    
    
    string json_file=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 501);
    this->schedule(schedule_selector(MailWindow::rec_501));
    load = Loading::create();
    this->addChild(load, 9999);

    
    return true;
}

void MailWindow::clk_btn_write()
{
    MailWrite::show();
}

void MailWindow::registerWithTouchDispatcher()
{
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
    CCLayer::registerWithTouchDispatcher();
}

bool MailWindow::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    istouch=tableView->ccTouchBegan(touch, event);
    
    if(istouch)
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

void MailWindow::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    if(istouch){
        
        tableView->ccTouchMoved(touch, event);
    }
}
void MailWindow::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    
    if (istouch) {
        tableView->ccTouchEnded(touch, event);
        
        istouch=false;
        
    }
}

void MailWindow::scrollViewDidScroll(CCScrollView* view)
{
    
}
void MailWindow::scrollViewDidZoom(CCScrollView* view)
{
    
}

unsigned int MailWindow::numberOfCellsInTableView(CCTableView *table)
{
    return arr->count();
}

void MailWindow::send_505()
{
    
}

void MailWindow::rec_505()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(505);
    CData::getCData()->m_dictionary->removeObjectForKey(505);
    
    
    if(revMsg)
    {
        
        load->removeFromParent();
        
        this->unschedule(schedule_selector(MailWindow::rec_505));
        
        
        char* data=revMsg->data;
        CCLog("%s",data);
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;

        
        
        if(read.parse(data, root)){
            jsonData=root["data"];
            MailInfo* info = (MailInfo*)(arr->objectAtIndex(tmpid));
            info->isReaded = 1;
            info->content = jsonData["content"].asString();
            
            tableView->reloadData();
            
            MailRead::show(info);
        }

        
        
        
    }

}

//处理触摸事件，可以计算点击的是哪一个子项
void MailWindow::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("点击了  %d",cell->getIdx());

    load = Loading::create();
    this->addChild(load, 9999);
    
    
    Json::FastWriter writer;
    Json::Value root;
    
    root["characterId"]=CData::getCData()->getCharactorId();
    root["mailID"] = ((MailInfo*)(arr->objectAtIndex(cell->getIdx())))->mailId;

    string json_file=writer.write(root);
    SocketManager::getInstance()->sendMessage(json_file.c_str(), 505);
    this->schedule(schedule_selector(MailWindow::rec_505));
    
            tmpCell = (MailRenderer*)cell;
            tmpid = cell->getIdx();
  }
//每一项的宽度和高度
CCSize MailWindow::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(420, 80);
}
//生成列表每一项的内容
CCTableViewCell* MailWindow::tableCellAtIndex(CCTableView *table, unsigned int idx)
{

    MailRenderer *cell = NULL;// table->dequeueCell();
    cell =new MailRenderer();
    cell->setInfo((MailInfo*)(arr->objectAtIndex(idx)));
    return cell;
}


void MailWindow::rec_501()
{
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(501);
    CData::getCData()->m_dictionary->removeObjectForKey(501);
    
    
    if(revMsg)
    {
         load->removeFromParent();
        
        this->unschedule(schedule_selector(MailWindow::rec_501));
        char* data=revMsg->data;
        CCLog("%s",data);
        Json::Reader read;
        Json::Value root;
        Json::Value jsonData;
        Json::Value petlist;
        
        
        if(read.parse(data, root)){
            jsonData=root["data"];
            petlist=jsonData["maillist"];
            
            int len = petlist.size();
            
            for (int i=0; i<len; i++) {
                
                
                MailInfo* info = new MailInfo();
                info->autorelease();
                
                info->mailId = petlist[i]["id"].asInt();
                info->isReaded = petlist[i]["isReaded"].asInt();
                info->sender = petlist[i]["sender"].asString();
                info->title = petlist[i]["title"].asString();
                info->sendTime = petlist[i]["sendTime"].asString();

                arr->addObject(info);
          
            }

        }
         tableView->reloadData();
    }
   
}