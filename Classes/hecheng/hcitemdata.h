
#ifndef client1_hcitemdata_h
#define client1_hcitemdata_h

#include <iostream>
#include"cocos2d.h"
using namespace cocos2d;
using namespace std;

class hcitemdata:public CCObject{
public:
    hcitemdata(){
        
        itemid = -1;
//        icon = -1;
        tempid = -1;
        num = -1;
        exp =-1;
    }
    int itemid;
//    int icon;
    int tempid;
    int num;
    int exp;
    
};

class configMonsterItem:public CCObject
{
public:
    configMonsterItem()
    {
        id = 0;
        nickname = "";
    };
    
    int id;
    string nickname;
};

class configHeroItem:public CCObject
{
    
public:
    configHeroItem()
    {
        DexGrowth = 0;//" : 970,
        StrGrowth = 0;//" : 2925,
        VitGrowth = 0;//" : 2100,
        WisGrowth = 0;//" : 1026,
        attrType = 0;//" : 3,
        baseQuality = 0;//" : 5,
        coin = 0;//" : 50000,
        descript = "";//" : "会释放邪恶法术的士兵，攻击力较高防御较低，擅长远程群体攻击。",
        icon = 0;//" : 378,
        id = 0;// : 35107,
        level = 0;//" : 103,
        nickname = "";//" : "蛮夷邪士",
        ordSkill = 0;//" : 5107,
        resourceid = 0;//" : 5107,
        skill = 0;//" : 710303,
        soulcount = 0;//" : 100,
        soulrequired = 0;//" : 41004094,
        type = 0;//" : 220000,
        xy = 0;//" : -1

    }
    
    int DexGrowth;//" : 970,
    int StrGrowth;//" : 2925,
    int VitGrowth;//" : 2100,
    int WisGrowth;//" : 1026,
    int attrType;//" : 3,
    int baseQuality;//" : 5,
    int coin;//" : 50000,
    string descript;//" : "会释放邪恶法术的士兵，攻击力较高防御较低，擅长远程群体攻击。",
    int icon;//" : 378,
    int id;// : 35107,
    int level;//" : 103,
    string nickname;//" : "蛮夷邪士",
    int ordSkill;//" : 5107,
    int resourceid;//" : 5107,
    int skill;//" : 710303,
    int soulcount;//" : 100,
    int soulrequired;//" : 41004094,
    int type;//" : 220000,
    int xy;//" : -1
    
    
};


class configGoodsItem:public CCObject{
public:
    configGoodsItem(){
        icon=0;
        itemid=0;
        tempid=0;
        name="";
        pinzhi=0;
        stack=0;
        bodytype=0;
        des="";
        maxexp = 0;
        growTemp = 0;
        comprice = 0;
        compound = 0;
    }
    int stack;
    int pinzhi;
    int bodytype;
    int icon;
    int itemid;
    int tempid;
    string name;
    string des;
    int maxexp;
    int growTemp;
    int comprice;
    int compound;
    
};
class heroItemData:public CCObject
{
public:
    heroItemData(){
        index =0;
        petId =0;
        m_mane="";
        tpid  =0;
        level =0;
        pinzhi=0;
        sz    =0;
        pos=0;
//        icons=0;
        sj    =0;
        hp    =0;
        wg    =0;
        wf=0;
        bj    =0;
        shb   =0;
        jn    ="";
        exp   =0;
        maxexp=0;
        jnicon=0;
        mj=0;
    };
    int index;          //索引
    int petId;          //宠物ID
    string m_mane;      //名字
    int tempid;
    int tpid;           //类型ID 主公1 宠物2 好友3
    int level;          //等级
    int pinzhi;         //品质
    bool sz;            //是否上阵
    int pos;            //位置
//    int icons;          //icon
    int  sj;             //身价
    int  hp;            //血量
    int  wg;            //物理攻击
    int mj;
    int  wf;            //宠物的物防
    int  bj;            //宠物的暴击值
    int  shb;           //宠物的闪避
    string jn;          //宠物的技能
    int  exp;           //宠物的当前经验
    int maxexp;         //宠物的最大经验值
    int jnicon;         //技能icon
};


#endif
