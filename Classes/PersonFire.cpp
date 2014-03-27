#include "PersonFire.h"

PersonFire::PersonFire(){
    
}
PersonFire::~PersonFire(){
    
}
void PersonFire::setInfo(int chaBattleId, const char *chaName, int chaPos, int chaLevel, int chaDirection, int chaIcon, int chaCurrentHp, int chaTotalHp, int chaId){
    this->_chaBattleId=chaBattleId;
    this->_chaName=chaName;
    this->_chaPos=chaPos;
    this->_chaLevel=chaLevel;
    this->_chaDirection=chaDirection;
    this->_charIcon=chaIcon;
    this->_chaCurrentHp=chaCurrentHp;
    this->_chaTotalHp=chaTotalHp;
    this->_chaId=chaId;
    
    
}
int PersonFire::getChaId(){
    return _chaId;
}
int PersonFire::getChaTotalHp(){
    return _chaTotalHp;
}
int PersonFire::getChaCurrentHp(){
    return _chaCurrentHp;
}
int PersonFire::getChaIcon(){
    return _charIcon;
}
int PersonFire::getChaDirection(){
    return _chaDirection;
}
int PersonFire::getChaLevel(){
    return _chaLevel;
}
int PersonFire::getChaPos(){
    return _chaPos;
}
const char*  PersonFire::getChaName(){
    return _chaName;
}
int PersonFire::getChaBattleId(){
    return _chaBattleId;
}
