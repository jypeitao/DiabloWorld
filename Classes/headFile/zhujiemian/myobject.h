
#ifndef client1_myobject_h
#define client1_myobject_h

#include <iostream>
#include"cocos2d.h"
using namespace cocos2d;
using namespace std;

class MapItem:public CCObject{
public:
    MapItem(){
        
        nickname = "";
        desc = "";
        bid = 0;
        mapId = 0;
        itemId = 0;
        enemy = "";
        enemydesc = "";
    }
    CCPoint pos;
    string nickname;
    string desc;
    string zj;
    string zjdesc;
    string enemy;
    string enemydesc;
    
    int bid;
    int mapId;
    int img;
    int exp;
    int coin;
    int itemId;
    
//    "x": 320,
//    "y": 580,
//    "id":1005,
//    "mapid":2,
//    "name": "汉中6",
//    "desc": "123",
//    "enemy":"送粮兵",
//    "enemydesc":"运送粮食的兵勇",
//    "zj":"截军粮",
//    "zjdesc":"拦截送往地方以镇压黄巾军的军粮队，赠粮于饥民",
//    "img":1,
//    "exp":100,
//    "coin":1000
    
};


#endif
