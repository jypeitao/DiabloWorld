#ifndef __client1__PersonFire__
#define __client1__PersonFire__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
class PersonFire:public CCObject{
public:
    PersonFire();
    ~PersonFire();
    void setInfo(int chaBattleId, const char *chaName,int chaPos,int chaLevel,int chaDirection,int chaIcon,int chaCurrentHp,int chaTotalHp,int chaId);
    int getChaBattleId();
    const  char * getChaName();
    int getChaPos();
    int getChaLevel();
    int getChaDirection();
    int getChaIcon();
    int getChaCurrentHp();
    int getChaTotalHp();
    int getChaId();
private:
    int _chaBattleId;
    const   char * _chaName;
    int _chaPos;
    int _chaLevel;
    int _chaDirection;
    int _charIcon;
    int _chaCurrentHp;
    int _chaTotalHp;
    int _chaId;
};
#endif /* defined(__client1__PersonFire__) */
