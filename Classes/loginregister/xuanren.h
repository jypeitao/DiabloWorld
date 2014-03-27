#ifndef __client1__xuanren__
#define __client1__xuanren__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
//#include "CCEditBox.h"
#include "json.h"
#include "LodingLayer.h"
//需要发送创建人物 数据  角色名称
using namespace cocos2d;
using namespace CocosDenshion;
class xuanren:public cocos2d::CCLayer{
public:
    ~xuanren();
    virtual void onExit();
    
    int flag;
    //CCSprite * kuang;
    Loading * load;
    CCMenuItemImage *selectBtn;
    CCSprite *touxiang1;
    CCSprite *touxiang2;
    CCSprite *touxiang3;
    CCLabelTTF * mingcheng;
    CCLabelTTF *jineng;
    CCLabelTTF * jieshao;
    CCSize size;
    CCSprite *renwu;
    CCMenuItemImage *btn1;
    CCMenuItemImage *btn2;
    CCMenuItemImage *btn3;
    cocos2d::extension::CCEditBox * enterUsrName;
    virtual bool init();
    static CCScene *scene();
    void receiveRoleInfo();
    void EnterName();
    void FirstPerson();
    void SecondPerson();
    void ThridPerson();
    void replacScene();
    void reloadUsrName();
    void receiveHomeInfo();
    void enterHomePage();
     void receiveCityData();
//    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
//    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
//    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
//    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    CREATE_FUNC(xuanren);
};


#endif /* defined(__client1__xuanren__) */
