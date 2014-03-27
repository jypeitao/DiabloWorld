#ifndef __client1__CData__
#define __client1__CData__

#include <iostream>
#include "cocos2d.h"
#include "json.h"
#include "hcitemdata.h"
#include "myobject.h"

using namespace cocos2d;
using namespace std;


class CData
{
public:
    int selectwjID;
    CCDictionary * m_dictionary;
    CCDictionary * m_newlevel_dic;
    CCDictionary * m_tunshi_dic;
    
    CCDictionary * m_config_goods_dic;
    
    CCDictionary * m_config_hero_dic;
    
    CCDictionary* m_config_monster_dic;
    
    CCDictionary* m_config_map_level_dic;
    
    
    void writeFile(std::string filename, std::string value);
    std::string readFile(std::string filename);
    void setmidindex(int mid);
    int getmidindex();
    static CData* getCData();
    void setCZ_Fire_data(char * jsondata);
    char *  getCZ_Fire_data();
    void setdata(char* data);
    char* getdata();
    void setgold(int gold);
    int getgold();
    void setcoin(int coin);
    int getcoin();
    void setExp(int exp);
    int getExp();
    void setMaxExp(int exp);
    int getMaxExp();
    void setLevel(int level);
    int getLevel();
    void setIndex(int index);
    int getIndex();
    void setTL(int tili);
    int getTL();
    void setZGZB(int tag);
    int getZGZB();
    void setjianghu(CCNode * jianghu);
    bool getczorzy();
    void setczorzy(bool flag);
    void setFireJson(Json::Value json);
    Json::Value getFireJson();
    void setFireResult(int result);
    int getFireResult();
    CCNode * getjianghu();
    
    
    void setZGBagInfo(const char *str);
    const char * getZGBagInfo();
    
    void setEquipInfo(const char *str);
    const char * getEquipInfo();
    
    
    bool getChatFlag();
    void setChatFlag(bool flag);
    void setCZ_info(char * jsondata);
    char * getCZ_info();
    //添加音乐
    void setyinyue(const char* yinyue);
    //添加音效
    void setyinxiao();
    //停止音乐
    
    //判断是否是第一次登陆
    void setfirstLogin(int login);
    //获取第一次登陆
    int getfirstLogin();
    
    void setFiremusic();
//    void sethomepage(homePage * home);
//    homePage * gethomepage();
    void setTFiremusic();
    void settzyy();
    void setSZnum(int level);
    int backSZnum();
    //flinchg
    //城镇开启和完成星级信息
    char *cityData;
    
    int battleCityId;
    
    bool isArenaFire;
    
    
    //获取物品配置
    configGoodsItem * getConfigOfGoods(int tempid);
    
    //获取
    configHeroItem * getConfigOfHero(int tempid);
    
    configMonsterItem* getConfigOfMonster(int tmpid);
    
    MapItem* getConfigOfMapLevel(int levelid);
    
    int getLevelMapNum();
    
    
    double levelMapOffsetY;
    
    
int _flag;
    
    int getCharactorId();
    void setCharactorId(int cid);
    
    int getUserId();
    void setUserId(int uid);
    
    char* getSendVal();
    void setSendVal(char* val);
    
    int getSex();
    
    
    
private:
    
    int _charactorId;
    int _userId;
    
    char * sendVal;
    
    int _sex;
    
    
    
    CData();
    int _firstLogin;
    int _sznum;
    const char * zgjson;
    const char * equipjson;
    int _tag;
    Json::Value _json;
    int _result;
    char * data;
    int gold;
    int coin;
    int exp;
    int maxexp;
    int level;
    int index;
    
    int _mid;
    bool _chatFlag;
    CCNode * JH;
    char * cz_fire_data;
    char * cz_info;
    bool is_yy;
    bool is_yx;
};
#endif /* defined(__client1__CData__) */
