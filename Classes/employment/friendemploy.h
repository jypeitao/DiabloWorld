
#ifndef __wx__friendemploy__
#define __wx__friendemploy__

#define  TAB_PASS_LEVEL 1
#define  TAB_USER_LEVEL 2
#define  TAB_ALL_USER 3

#define ADD_MORE_TAG 99999


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

//#include "friendinfo.h"
#include "LodingLayer.h"
#include "friendemploycell.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class friendemploy:public CCLayer,public CCTableViewDelegate,public CCTableViewDataSource
{
    
public:
    CREATE_FUNC(friendemploy);
    
    void send_employ(friendinfo* info);
private:
    
    virtual bool init();
    
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    //处理触摸事件，可以计算点击的是哪一个子项
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    //每一项的宽度和高度
    virtual CCSize cellSizeForTable(CCTableView *table);
    //生成列表每一项的内容
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    //一共多少项
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void rec_info();
    void changeTab(CCObject* sender);
    void send_302();
    void rec_302();
    
    
private:
    
    
    
    
    
    Loading* load;
CCTableView* tableView;
    CCSize size;
    
    int selectIndex;
    CCMenuItemImage* btn1;
    CCMenuItemImage* btn2;
    CCMenuItemImage* btn3;
    CCMenu* menu;
    
    bool istouch;
    
    bool istouchex;
    
//    vector<friendinfo> vec;

    CCArray* arrPassLevel;
    CCArray* arrUserLevel;
    CCArray* arrAllUser;
    
    int indexPassLevel;
    int indexUserLevel;
    int indexAllUser;
    
    
    bool finishPassLevelData;
    bool finishUserLevelData;
    bool finishAllUserData;
    
    
    float offsetTable;
    
    
    FriendEmployCell* tmpCell;
    
    int tmpid;
    
};


#endif /* defined(__wx__friendemploy__) */
