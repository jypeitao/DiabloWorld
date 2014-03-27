#include "CData.h"
//#include "CCFileUtils.h"
#include "SimpleAudioEngine.h"
static CData *cdata;
CData::CData()
{
    selectwjID=0;
    m_tunshi_dic=CCDictionary::create();
    m_tunshi_dic->retain();
    m_dictionary = cocos2d::CCDictionary::create();
    m_dictionary->retain();
    m_newlevel_dic=CCDictionary::create();
    m_newlevel_dic->retain();
    
    m_config_goods_dic = CCDictionary::create();
    m_config_goods_dic->retain();
    
    m_config_hero_dic = CCDictionary::create();
    m_config_hero_dic->retain();
    
    m_config_monster_dic = CCDictionary::create();
    m_config_monster_dic->retain();
    
    m_config_map_level_dic = CCDictionary::create();
    m_config_map_level_dic->retain();
    
    index=0;
    JH=0;
    is_yy = true;
    is_yx = true;
    battleCityId = -1;
    levelMapOffsetY = 1;
    isArenaFire = false;
    
}
void CData::writeFile(std::string filename, std::string value)
{
    std::string Background = value;
    const char * groundName = Background.c_str();
    std::string doPath = "";//CCFileUtils::sharedFileUtils()->getWriteablePath();
    std::string filenamea = filename;
    std::string filepath = doPath + filename;
    FILE *fp = fopen(filepath.c_str(),"w");
    fputs(groundName,fp);
    fclose(fp);
}
void CData::setmidindex(int mid){
    _mid=mid;
}
int CData::getmidindex(){
    return _mid;
}
//更具关键字读取手机中的内容
std::string CData::readFile(std::string filename)
{
    std::string doPath ="";// CCFileUtils::sharedFileUtils()->getWriteablePath();
    std::string filenamea = filename;
    std::string filepath = doPath + filename;
    FILE *fp1 = fopen(filepath.c_str(),"r");
    char* pchBuf = NULL;
    
    int len = 0;
    if (fp1 == NULL) {
        return "nologin";
    }
    fseek(fp1 , 0, SEEK_END);
    len = ftell(fp1);
    
    rewind(fp1);
    pchBuf = (char*)malloc(sizeof(char)*len+1);
    
    if (!pchBuf)
        
    {
        //        CCLOG("内存不够!\n");
        exit(0);
    }
    
    len = fread(pchBuf,sizeof(char),len,fp1);
    pchBuf[len] = '\0';
    std::string getground = pchBuf;
    fclose(fp1);
    free(pchBuf);
    
    std::stringstream ss(getground);
    std::string pucter;
    //    std::string aaaaaa = "6";
    for (int i=0 ;i < 1 ;i++)
    {
        getline(ss,pucter,',');
    }
    return pucter.c_str() ;
    
}
void CData::setChatFlag(bool flag){
    _chatFlag=flag;
}
bool CData::getChatFlag(){
    return _chatFlag;
}
void CData::setczorzy(bool flag){
    _flag=flag;
}
void CData::setSZnum(int level){
    if(level>=1&&level<3){
        _sznum=1;
    }else if(level>=3&&level<5){
        _sznum=2;
    }else if(level>=5&&level<10){
        _sznum=3;
    }else if(level>=10&&level<15){
        _sznum=4;
    }else if(level>=15&&level<20){
        _sznum=5;
    }else if(level>=20&&level<25){
        _sznum=6;
    }else if(level>=25&&level<30){
        _sznum=7;
    }else if(level>=30&&level<=100){
        _sznum=8;
    }
    
}
int CData::backSZnum(){
    return _sznum;
}
bool CData::getczorzy(){
    return _flag;
}

CData* CData::getCData()
{
    if(!cdata)
        cdata = new CData();
    
    return cdata;
}
void CData::setdata(char *data)
{
    this->data = data;
}
void CData::setZGBagInfo(const char *str){
    zgjson=str;
    
}

configMonsterItem* CData::getConfigOfMonster(int tempid)
{
    if(m_config_monster_dic->count() < 1)
    {
        //   const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("hero.json").c_str();
        //        ifstream ifs;
        //        ifs.open(path);
        //        assert(ifs.is_open());
        
        Json::Reader reader;
        Json::Value root;
        Json::Value items;
        
        Json::Value::Members members;
        
        //        Json::Value::iterator it;
        Json::Value::Members::iterator it;
        
        string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("monster.json");
        CCString* str = CCString::createWithContentsOfFile(path.c_str());
        
        if(reader.parse(str->getCString(), root)){
            
            members = root.getMemberNames();
            it = members.begin();
            while (it != members.end()) {
                
                items = root[std::string(*it)];
                
                configMonsterItem * item= new configMonsterItem();
                char inttostr[20]="";
                sprintf(inttostr, "%d",tempid);
                
                
                
                item->id = items["id"].asInt();
                item->nickname = items["nickname"].asString();//" : "蛮夷邪士",
                                
                m_config_monster_dic->setObject(item, item->id);
                
                it++;
            }
            
                      
        }
        
    }
    
    
    return (configMonsterItem*)m_config_monster_dic->objectForKey(tempid);

}

configHeroItem*  CData::getConfigOfHero(int tempid)
{
    
    if(m_config_hero_dic->count() < 1)
    {
     //   const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("hero.json").c_str();
//        ifstream ifs;
//        ifs.open(path);
//        assert(ifs.is_open());
        
        Json::Reader reader;
        Json::Value root;
        Json::Value items;
        
        Json::Value::Members members;
        
        //        Json::Value::iterator it;
        Json::Value::Members::iterator it;
        
        string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("hero.json");
        CCString* str = CCString::createWithContentsOfFile(path.c_str());
        
        if(reader.parse(str->getCString(), root)){
            
            members = root.getMemberNames();
            it = members.begin();
            while (it != members.end()) {
                
                items = root[std::string(*it)];
                
                configHeroItem * item= new configHeroItem();
                char inttostr[20]="";
                sprintf(inttostr, "%d",tempid);
                item->DexGrowth = items["DexGrowth"].asInt();//" : 970,
                item->StrGrowth = items["StrGrowth"].asInt();//" : 2925,
                item->VitGrowth = items["VitGrowth"].asInt();//" : 2100,
                item->WisGrowth = items["WisGrowth"].asInt();//" : 1026,
                item->attrType = items["attrType"].asInt();//" : 3,
                item->baseQuality = items["baseQuality"].asInt();//" : 5,
                item->coin = items["coin"].asInt();//" : 50000,
                item->descript = items["descript"].asString();//" : "会释放邪恶法术的士兵，攻击力较高防御较低，擅长远程群体攻击。",
                item->icon = items["icon"].asInt();//" : 378,
                item->id = items["id"].asInt();// : 35107,
                item->level = items["level"].asInt();//" : 103,
                item->nickname = items["nickname"].asString();//" : "蛮夷邪士",
                item->ordSkill = items["ordSkill"].asInt();//" : 5107,
                item->resourceid = items["resourceid"].asInt();//" : 5107,
                item->skill = items["skill"].asInt();//" : 710303,
                item->soulcount = items["soulcount"].asInt();//" : 100,
                item->soulrequired = items["soulrequired"].asInt();//" : 41004094,
                item->type = items["type"].asInt();//" : 220000,
                item->xy = items["xy"].asInt();//" : -1

                m_config_hero_dic->setObject(item, item->id);
                
//                item->bodytype=items["bodyType"].asInt();
//                item->name=items["name"].asString();
//                item->pinzhi=items["baseQuality"].asInt();
//                item->des=items["description"].asString();
//                item->tempid = items["id"].asInt();
//                item->bodytype = items["bodytype"].asInt();
//                
//                m_config_goods_dic->setObject(item, item->tempid);
                
                it++;
            }
            
//            ifs.close();
            
        }
        
    }
    
    
    return (configHeroItem*)m_config_hero_dic->objectForKey(tempid);
    
}

int CData::getLevelMapNum()
{
    if(m_config_map_level_dic->count() <1)
    {
        getConfigOfMapLevel(1000);
    }
    
    int num = ceil(( m_config_map_level_dic->count() )/3);
    
    return num;
}

MapItem* CData::getConfigOfMapLevel(int levelid)
{
    if(m_config_map_level_dic->count()<1)
    {
    
    Json::Reader read;
    Json::Value root;
    Json::Value data;
    
    Json::Value list;
    
    
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("map.json");
    CCString* str = CCString::createWithContentsOfFile(path.c_str());
    int sz = 0;
    if(read.parse(str->getCString(), root)){
        data = root["data"];
        sz = data.size();
        
        
        for (int i = 0; i < sz; i++) {
            
            
            MapItem *item = new MapItem();
//            item->autorelease();
            item->nickname = data[i]["name"].asString();
            item->desc = data[i]["desc"].asString();
            item->bid = data[i]["id"].asInt();
            item->exp = data[i]["exp"].asInt();
            item->coin = data[i]["coin"].asInt();
          //  item->itemId = root[i]["dropicon"].asInt();
            
            
            
            list = data[i]["mconfig"];
            CCDictionary* dic = CCDictionary::create();
           
            int  len =list.size();
            for (int ei = 0; ei < len; ei++)
            {
                int iiiiid = list[ei].asInt();
                configMonsterItem* hitem =CData::getCData()->getConfigOfMonster(iiiiid);
                if(hitem != NULL)
                {
                    dic->setObject(hitem, hitem->nickname);
                    
                }
                else{
                    char iii[100] = "";
                    sprintf(iii, "怪物id不存在  %d",iiiiid);
                    CCLog(iii);
                }
                
            }
            
            char chars[500] = "";
            
            int how = dic->count();
            CCArray* arr = dic->allKeys();
            switch (how) {
                case 1:
                    sprintf(chars, "【%s】",((CCString*)(arr->objectAtIndex(0)))->getCString());
                    break;
                case 2:
                    sprintf(chars, "【%s】\n【%s】",((CCString*)(arr->objectAtIndex(0)))->getCString(),((CCString*)(arr->objectAtIndex(1)))->getCString());
                    break;
                case 3:
                    sprintf(chars, "【%s】  【%s】\n【%s】",((CCString*)(arr->objectAtIndex(0)))->getCString(),((CCString*)(arr->objectAtIndex(1)))->getCString(),((CCString*)(arr->objectAtIndex(2)))->getCString());
                    break;
                    
                default:
                    if(how >= 4)
                    {
                        sprintf(chars, "【%s】  【%s】\n【%s】  【%s】",((CCString*)(arr->objectAtIndex(0)))->getCString(),
                                ((CCString*)(arr->objectAtIndex(1)))->getCString(),
                                ((CCString*)(arr->objectAtIndex(2)))->getCString(),((CCString*)(arr->objectAtIndex(3)))->getCString());
                    }
                    break;
            }
            
            item->enemydesc = chars;
            
            CCLog(item->enemydesc.c_str());
            m_config_map_level_dic->setObject(item, item->bid);
        }
        
        
    }
    }
    
    return (MapItem*)m_config_map_level_dic->objectForKey(levelid);

}


configGoodsItem*  CData::getConfigOfGoods(int tempid)
{
    
    if(m_config_goods_dic->count() < 1)
    {
//        const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("itemconfig.json").c_str();
//        ifstream ifs;
//        ifs.open(path);
//        assert(ifs.is_open());
        Json::Reader reader;
        Json::Value root;
        Json::Value items;
        
        Json::Value::Members members;
        
//        Json::Value::iterator it;
        Json::Value::Members::iterator it;
        
        string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("item.json");
        CCString* str = CCString::createWithContentsOfFile(path.c_str());
            
        if(reader.parse(str->getCString(), root)){
            
            members = root.getMemberNames();
            it = members.begin();
            while (it != members.end()) {
                
                items = root[std::string(*it)];
                
                configGoodsItem * item= new configGoodsItem();
                char inttostr[20]="";
                sprintf(inttostr, "%d",tempid);
                
                item->bodytype=items["bodyType"].asInt();
                item->name=items["name"].asString();
                item->pinzhi=items["baseQuality"].asInt();
                item->des=items["description"].asString();
                item->tempid = items["id"].asInt();
                item->icon = items["icon"].asInt();
                item->maxexp = items["maxexp"].asInt();
                item->growTemp = items["growTemp"].asInt();
                item->comprice = items["comprice"].asInt();
                item->compound = items["compound"].asInt();
                
                
                m_config_goods_dic->setObject(item, item->tempid);
                
                it++;
            }
        
         //   ifs.close();
    
        }

    }
    
    
    return (configGoodsItem*)m_config_goods_dic->objectForKey(tempid);
    
}

void CData::setEquipInfo(const char *str)
{
    equipjson = str;
}
void CData::setZGZB(int tag){
    _tag=tag;
}
void CData::setfirstLogin(int login){
    _firstLogin=login;
}
int CData:: getfirstLogin(){
    return _firstLogin;
}
//void CData::sethomepage(){
//    
//}
int CData::getZGZB(){
    return _tag;
}
const char * CData::getZGBagInfo(){
    return zgjson;
}
const char * CData::getEquipInfo()
{
    return equipjson;
}
void CData::setFireJson(Json::Value json){
    _json=json;
}
Json::Value CData::getFireJson(){
    return _json;
}
void CData::setFireResult(int result){
    _result=result;
}
int CData::getFireResult(){
    return _result;
}
char* CData::getdata()
{
    return data;
}
void CData::setgold(int gold){
    this->gold=gold;
}
int CData::getgold(){
    return gold;
}
void CData::setcoin(int coin){
    this->coin=coin;
}
int CData::getcoin(){
    return coin;
}
void CData::setExp(int exp){
    this->exp=exp;
}
int CData::getExp(){
    return exp;
}
void CData::setMaxExp(int exp){
    this->maxexp=exp;
}
int CData::getMaxExp(){
    return maxexp;
}
void CData::setLevel(int level){
    this->level=level;
}
int CData::getLevel(){
    return level;
}
void CData::setIndex(int index){
    this->index=index;
}
int CData::getIndex(){
    return index;
}
void CData::setjianghu(cocos2d::CCNode *jianghu){
    this->JH=jianghu;
}
CCNode * CData::getjianghu(){
    return JH;
}

void CData::setSendVal(char *val)
{
    sendVal = val;
    
}

int CData::getSex()
{
    char * json=CData::getCData()->getSendVal();
    Json::Reader read;
    Json::Value  root;
    Json::Value  data;
    
    //    int characterId;
    
    if(read.parse(json, root)){
        data=root["data"];
        _sex = data["profession"].asInt();
    }

    return _sex;
}

char* CData::getSendVal()
{
    return sendVal;
}

void CData::setyinyue(const char *yinyue)
{
//    if(readFile("yinyue")=="YES")
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(yinyue, true);
    }
}
void CData::setyinxiao()
{
//    if(readFile("yinxiao")=="YES")
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("yx.mp3");
    }
}
void CData::setFiremusic(){
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttacked.mp3");
    }
}
void CData::setTFiremusic(){
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack.mp3");
    }
}
void CData::settzyy()
{
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}
void CData::setCZ_Fire_data(char *jsondata){
    cz_fire_data=jsondata;
}
char * CData::getCZ_Fire_data(){
    return cz_fire_data;
}
void CData::setCZ_info(char *jsondata){
    cz_info=jsondata;
}
char * CData::getCZ_info(){
    return cz_info;
}


int CData::getCharactorId()
{
    return _charactorId;
}
void CData::setCharactorId(int cid)
{
    _charactorId = cid;
}

int CData::getUserId()
{
    return _userId;
}
void CData::setUserId(int uid)
{
    _userId = uid;
}

