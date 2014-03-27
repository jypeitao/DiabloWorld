#include "MyTableView.h"

bool TableView::init(){
    if(!cocos2d::extension::CCTableView::init()){
        return false;
    }
    return true;
}
//传参
cocos2d::extension::CCTableView * TableView::sendInfo(int line, CCSize size,CCSize contentsize){
    _line=line;
    _size=size;
    this->setTouchEnabled(true);
    printf("init");
    _contentsize=contentsize;
    this->setContentSize(_contentsize);
    tableView=cocos2d::extension::CCTableView::create(this, _contentsize);
    

    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
    return tableView;
//    this->setPosition(ccp(0,0));
//    this->setAnchorPoint(ccp(0, 0));
//    this->addChild(tableView);
}
CCSize TableView::cellSizeForTable(cocos2d::extension::CCTableView *view){
    return  _size;
}
cocos2d::extension::CCTableViewCell * TableView::tableCellAtIndex(cocos2d::extension::CCTableView *tableView, unsigned int idx){
    cocos2d::extension::CCTableViewCell *cell=tableView->dequeueCell();
    if(!cell){
        printf("cell");
        cell= new cocos2d::extension::CCTableViewCell();
        cell->autorelease();
        CCSprite *icon=CCSprite::create("Icon.png");
        cell->addChild(icon);
        printf("cell1");
    }
    return cell;
}

unsigned int TableView::numberOfCellsInTableView(cocos2d::extension::CCTableView *table){
    return _line;
}
void TableView::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell *cell){
    
}