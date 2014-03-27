#ifndef __client1__GameOver__
#define __client1__GameOver__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "zhuangtaiLoad.h"
#include "message.h"
#include "SocketClient.h"
#include "LayerLogin.h"
#include "CData.h"
#include "LodingLayer.h"
//#include "scrollViewTest.h"
#include "homePage.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class GameOver:public cocos2d::CCLayer{
public:
    
    //    GameOver();
    ~GameOver();
    //    static GameOver * gameover();
    virtual bool init();
    void goBackToHome();//返回主界面
    void win();//胜利
    void faild();//失败
    void shake();//震屏
    void star1();//1X
    void star2();//2X
    void star3();//3X
    void gasRun();//活力减少动画
    void zhaomuwujiang();
    void checkoutkapai();
    int coin;//货币
    int exp;//经验值
    int star;//星级
    int _power;//能量
    CCSize size;
    CCSprite * qs;
    int kpcount;
    int icon;
    Loading * load;
    CCSprite * huoli;
    int itemcount;
    int huoli1;
    CCSprite * faguang;
    CCSprite * gm;
    CCSprite * gm2;
    void guangmang(char * kapainame);
    void receiveGoHomeBack();
    void zhenping();
    void  repateFire(CCNode * sender);
    CREATE_FUNC(GameOver);
};
#endif /* defined(__client1__GameOver__) */
