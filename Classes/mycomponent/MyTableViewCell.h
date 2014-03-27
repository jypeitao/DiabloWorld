
#ifndef Client_MyTableViewCell_h
#define Client_MyTableViewCell_h
#include "cocos2d.h"
#include"cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MyTableViewCell:public CCTableViewCell
{
public:
    MyTableViewCell();
    ~MyTableViewCell();
    bool init();
void addChild(CCMenuItem* pMenuItem);
    static MyTableViewCell* create();
    CCMenu *pMenu;
private:
    
};

#endif
