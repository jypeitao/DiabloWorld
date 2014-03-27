#ifndef __client1__UserData__
#define __client1__UserData__

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class UserData
{
public:
    static UserData* getInstance();
    int test();
    int characterId;
    string rolename;
    int level;
    int exp;
    int maxexp;
    int gold;
    int coin;
    int tili;
    int tilimax;
    int huoli;
    int huolimax;
    int viplevel;
    
//    characterId	int		角色ID
//    rolename		str     角色的名称
//    level			int		角色的等级
//    exp			int		角色的当前经验值
//    maxexp			int		角色的最大经验值
//    gold			int		黄金的数量
//    coin			int		银子的数量
//    tili			int		当前体力值
//    tilimax		int		最大体力值
//    huoli			int		当前活力值
//    maxhuoli		int		最大活力值
//    viplevel		int		vip等级
    
    
    
    
private:
    UserData();
    static UserData *instance;
    
    
    
    
};



#endif /* defined(__client1__UserData__) */
