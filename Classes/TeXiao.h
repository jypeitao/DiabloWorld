#ifndef __client1__TeXiao__
#define __client1__TeXiao__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
class texiao:public cocos2d::CCSprite{
public:
    //virtual bool init();
    texiao();
    ~texiao();
   static texiao * TX();
    CCSpriteBatchNode * touzhi;
    CCSprite * texiaosCreate(const char * name,int num);
    CCSprite * texiaoCreate();
    CCSprite * yanwu();
    CCSprite * dayan();
    CCSprite * beginyanwu();
    CCSprite * touzhiCreate();
    CCSprite * lingqucg();
    CCSprite * duoqucg();
    CCSprite * duoqusb();
    CCSprite * mingzhongCreate();
    CCSprite * normalAttackCreate();
    CCSprite * taijibagua();//太极八卦
    CCSprite * tiangongnu();//天公怒
    CCSprite * zuixingji();//醉醒技
    CCSprite * yushenzhushen();//遇神诛神
    CCSprite * huangquezhen();//黄雀阵
    CCSprite * kunshouzhidou();//困兽之斗
    CCSprite * luandaozhan();//乱刀斩
    CCSprite * meirenji();//美人计
    CCSprite * pojunji();//破军计
    CCSprite * qubingji();//屈兵计
    CCSprite * shengdongjixi_mz();//声东击西-命中
    CCSprite * shengdongjixi_tz();//声东击西-投掷
    CCSprite * shijizhou();//狮子吼
    CCSprite * shuangfuzhishang_cz();//双斧之伤-出招
    CCSprite * shuangfuzhishang_mz();//双斧之伤-命中
    CCSprite * shuangjizhishang_cz();//双戟之伤-出招
    CCSprite * shuangjizhishang_mz();//双戟之伤-命中
    CCSprite * shuanglianzhishang_cz();//双廉之伤-出招
    CCSprite * shuanglianzhishang_mz();//双廉之伤-命中
    CCSprite * shuangqiangzhishang_cz();//双枪之伤-出招
    CCSprite * shuangqiangzhishang_mz();//双枪之伤-命中
    CCSprite * shuangrenzhishang_cz();//双刃之伤-出招
    CCSprite * shuangrenzhishang_mz();//双刃之伤-命中
    CCSprite * shuijisanqianli();//水击三千里
    CCSprite * touxi();//偷袭
    CCSprite * wanlibingfeng();//万里冰封
    CCSprite * xiefengzhen();//邪风阵
    CCSprite * yehuoliaoyuan();//野火燎原
    void removeSprite(CCNode * sender);
    CREATE_FUNC(texiao);
};
#endif /* defined(__client1__TeXiao__) */
