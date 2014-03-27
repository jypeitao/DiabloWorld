#ifndef Client_LayerLogin_h
#define Client_LayerLogin_h
#include"cocos2d.h"
#include"cocos-ext.h"
#include "SocketClient.h"
#include "CData.h"
#include "LodingLayer.h"
#include "TeXiao.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

class LayerLogin:public CCLayer
{
    
public:
    
    CREATE_FUNC(LayerLogin);
    virtual bool init();
    virtual void onExit();
    ~LayerLogin();
    
    CCSprite * texiao;
    bool hasRole;
    Loading * load;

    CCSprite * logo;
    CCSize winSize;
    
    char * denglu1;
    
    void removeLoader();
   
    void receiveLoginData();
    void sendPersonalData();
    void receivePersonalData();
    
    void receiveCityData();
    void jiumiaoshanyou();
    void firefly();
    void callNull1();
    void callNull2();
    void zhenping();
    char * sendData;
private:
    
    void initUI();
    void loadRes();
    
    // bool init();
   
    void menuItemCallbackLogin(CCObject* pSender);
    void menuItemCallbackStart(CCObject* pSender);
    void menuItemCallbackSelector(CCObject* pSender);
    
    
    
    
    
    
    //CCLabelTTF *label1;
    //CCLabelTTF *label2;
    CCMenuItemImage *url1,*url2;
    CCSprite *pSpriteDialogLogin;
    EditBox* editBoxUsername;
    EditBox* editBoxPassword;
    
};
#endif
