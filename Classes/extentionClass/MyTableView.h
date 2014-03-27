#ifndef __Client__MyTableView__
#define __Client__MyTableView__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCTableView.h"
#include "CCTableViewCell.h"
#include "CCScrollView.h"
using namespace cocos2d;
using namespace CocosDenshion;

class TableView:public cocos2d::extension::CCTableView,public cocos2d::extension::CCTableViewDelegate,public cocos2d::extension::CCTableViewDataSource{
  
public:
    int _line;//行数
    CCSize _size;//table的尺寸
    virtual bool init();
    virtual CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell * tableCellAtIndex(cocos2d::extension::CCTableView *table,unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *view);
    virtual void tableCellTouched(cocos2d::extension::CCTableView *table,cocos2d::extension::CCTableViewCell *cell);
    cocos2d::extension::CCTableView *tableView;
    CCSize _contentsize;
    cocos2d::extension::CCTableView * sendInfo(int line,CCSize size,CCSize contentsize);//传参函数
    cocos2d::extension::CCTableViewDelegate *delegate;
    cocos2d::extension::CCTableViewDataSource *dataSouce;
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView *view){
        
    }
    
    
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView *view){
        
    }

    CREATE_FUNC(TableView);
};
#endif /* defined(__Client__MyTableView__) */
