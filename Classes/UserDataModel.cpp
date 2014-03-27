#include "UserDataModel.h"



UserData* UserData::instance = NULL;

UserData::UserData()
{
    
    characterId = 100;

}
UserData* UserData::getInstance()
{
    if(instance == NULL)
    {
        instance = new UserData();
    }
    return instance;
}

int UserData::test()
{
    return -1;
}
