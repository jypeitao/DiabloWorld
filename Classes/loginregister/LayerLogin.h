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

class LayerLogin:public Layer
{
    
public:
    
    CREATE_FUNC(LayerLogin);
    virtual bool init();
    virtual void onExit();
    ~LayerLogin();
    
    Sprite * texiao;
    bool hasRole;
    Loading * load;

    Sprite * logo;
    Size winSize;
    
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
   
    void menuItemCallbackLogin(Object* pSender);
    void menuItemCallbackStart(Object* pSender);
    void menuItemCallbackSelector(Object* pSender);
    
    
    
    
    
    
    //LabelTTF *label1;
    //LabelTTF *label2;
    MenuItemImage *url1,*url2;
    Sprite *pSpriteDialogLogin;
    EditBox* editBoxUsername;
    EditBox* editBoxPassword;
    
};
#endif
