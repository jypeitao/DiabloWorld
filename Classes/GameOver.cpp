#include "GameOver.h"
#include "FireWork.h"
#include "json.h"
#include "zhuangtaiLoad.h"
#include "SocketManager.h"

static const char * ads[25]={0};
static int kp[10]={0};
bool GameOver::init(){
    if(!CCLayer::init()){
        return false;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.mp3",true);
    kpcount=1;
    for (int i=0; i<10; i++) {
        kp[i]=0;
    }
    size=CCDirector::sharedDirector()->getWinSize();
    //Fire::fire()->result();
    int result=CData::getCData()->getFireResult();
    
    printf("result is :%d\n",result);
    //Fire::fire()->getJson();
    Json::Value value=CData::getCData()->getFireJson();
    Json::Value kapai;
    int i=0;
    //    CCLog(value);
    itemcount=value["item"][i].asInt();
    CCLog("%d",itemcount);
    //itemcount=item[i];
    //CCLog("%s",value.asString().c_str());
    coin=value["coin"].asInt();
    star=value["star"].asInt();
    huoli1=value["huoli"].asInt();
    printf("huo li%d\n",huoli1);
    exp=value["exp"].asInt();
    kapai=value["petres"];
    for (int i=0; i<kapai.size(); i++) {
        kp[i]=kapai[i].asInt();
    }
    
    
    
    CCSprite *bkg=CCSprite::create("fireresult_bkg.png");
    bkg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bkg);
    
    
    ccColor3B black = ccc3(0, 0, 0);
    ccColor3B ycolor = ccc3(120, 80, 20);
    
    
    char tmp[50] = "";
    sprintf(tmp, "+ %d",exp);
    
    CCLabelTTF* weittf = CCLabelTTF::CCLabelTTF::create(tmp, "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentCenter);
    weittf->setPosition(ccp(120, 395));
    weittf->setColor(ycolor);
    bkg->addChild(weittf);
    
    char tmp1[50] = "";
    sprintf(tmp1, "+ %d",coin);
    
    CCLabelTTF* goldttf = CCLabelTTF::CCLabelTTF::create(tmp1, "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentCenter);
    goldttf->setPosition(ccp(240, 395));
    goldttf->setColor(ycolor);
    bkg->addChild(goldttf);
    
    char tmp2[50] = "";
    sprintf(tmp2, "%d",huoli1);
    
    CCLabelTTF* huolittf = CCLabelTTF::CCLabelTTF::create(tmp2, "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentCenter);
    huolittf->setPosition(ccp(358, 395));
    huolittf->setColor(ycolor);
    bkg->addChild(huolittf);
    
    
    
    
    if(result==1)
    {
        this->win();
    }else if(result==2){
        this->faild();
    }
    

    char kpsname[50]="";
    if(kp[0]!=0){
        gm2=CCSprite::create("base_add.png");
        gm2->setOpacity(GLubyte(0));
        
        gm2->setScale(1.5);
        gm2->setRotation(-150);
        gm2->setPosition(ccp(320, 480));
        this->addChild(gm2,4);
        gm=CCSprite::create("base_add.png");
        gm->setOpacity(GLubyte(0));
        gm->setPosition(ccp(320, 480));
        this->addChild(gm,4);
        faguang=CCSprite::create("faguang.png");
        faguang->setOpacity(GLubyte(0));
        
        faguang->setPosition(ccp(320, 480));
        this->addChild(faguang,6);
        sprintf(kpsname, "qs_%d.png",kp[0]);
        qs=CCSprite::create(kpsname);
        qs->setVisible(false);
        qs->setOpacity(GLubyte(0));
        this->addChild(qs,5);
        this->guangmang(kpsname);
    }
    return  true;
}
void GameOver::checkoutkapai(){
    if(kp[kpcount]!=0){
        char kpsname[50]="";
        
        sprintf(kpsname, "qs_%d.png",kp[kpcount]);
        this->guangmang(kpsname);
    }else{
        
    }
    kpcount++;
}
void GameOver::guangmang(char * kapainame){
    CCDelayTime * delaytime=CCDelayTime::create(0.5);
    CCDelayTime * delaytime2=CCDelayTime::create(0.5);
    CCDelayTime * delaytime3=CCDelayTime::create(0.5);
    CCDelayTime * delaytime4=CCDelayTime::create(1);
    CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(GameOver::checkoutkapai));
    CCFadeIn * fadein=CCFadeIn::create(0.33);
    CCFadeIn * fadein2=CCFadeIn::create(0.33);
    CCFadeIn * fadein3=CCFadeIn::create(0.33);
    
    //    CCFadeIn * fadein4=CCFadeIn::create(0.33);
    CCFadeOut * fadeout1=CCFadeOut::create(0.27);
    CCFadeOut * fadeout2=CCFadeOut::create(0.27);
    CCFadeOut * fadeout3=CCFadeOut::create(0.27);
    CCFadeOut * fadeout4=CCFadeOut::create(0.27);
    CCSequence *seq=CCSequence::create(delaytime,fadein,delaytime3,fadeout1,func,NULL);
    CCSequence *seq2=CCSequence::create(delaytime2,fadein2,delaytime3,fadeout2,NULL);
    CCSequence *seq3=CCSequence::create(fadein3,delaytime4,fadeout3,NULL);
    CCSequence *seq4=CCSequence::create(fadeout4,delaytime4,fadeout4,NULL);
    //    qs->setScaleX(1.7);
    //    qs->setScaleY(1.86);
    qs->initWithFile(kapainame);
    qs->setOpacity(GLubyte(0));
    qs->setPosition(ccp(size.width/2, size.height/2));
    qs->runAction(seq3);
    
    
    
    //    qs->setOpacityModifyRGB(true);
    //    qs->setColor(ccc3(0, 0, 0));
    
    faguang->runAction(seq4);
    
    
    
    
    
    
    
    gm->setOpacity(GLubyte(0));
    gm->setScale(3);
    
    gm->runAction(seq2);
    CCRotateBy * rote=CCRotateBy::create(24, 360);
    gm->runAction(CCRepeatForever::create(rote));
    
    
    
    gm2->setOpacity(GLubyte(0));
    
    gm2->setScale(1.5);
    gm2->setRotation(-150);
    gm2->setPosition(ccp(320, 480));
    gm2->runAction(seq);
    CCRotateBy * rote2=CCRotateBy::create(24, -360);
    gm2->runAction(CCRepeatForever::create(rote2));
    
}
void GameOver::win(){
    star1();
    CCSprite *_star1=CCSprite::create("starbg.png");
    
    //    _star1->setAnchorPoint(ccp(0, 0));
    _star1->setPosition(ccp(size.width/2+60, size.height/2+160));
    this->addChild(_star1,3);
    
    CCSprite *_star2=CCSprite::create("starbg.png");
    //    _star2->setAnchorPoint(ccp(0, 0));
    _star2->setPosition(ccp(size.width/2+115, size.height/2+160));
    this->addChild(_star2,3);
    CCSprite *_star3=CCSprite::create("starbg.png");
    //    _star3->setAnchorPoint(ccp(0, 0));
    _star3->setPosition(ccp(size.width/2+175, size.height/2+160));
    this->addChild(_star3,3);
    Json::Reader reader;
    Json::Value root;
    Json::Value items;
    
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("item.json");
    CCString* str = CCString::createWithContentsOfFile(path.c_str());
    if(reader.parse(str->getCString(), root)){
        
        char inttostr[20]="";
        sprintf(inttostr, "%d",itemcount);
        if(itemcount!=0){
            items=root[inttostr];
            icon=items["icon"].asInt();
        }
        
    }
    //************************************掉落
    if(itemcount!=0){
        CCSprite *baowu1;
        char iconnum[40]="";
        CCLog("%d",icon);
        if(icon >=6000 && icon<= 6056)
        {
            icon = 6000;
            sprintf(iconnum, "qs_%d.png",icon);
            baowu1 = CCSprite::create(iconnum);
            baowu1->setVisible(true);
            baowu1->setScale(0.19);
            baowu1->setPosition(ccp(120, 305));
            this->addChild(baowu1,3);
        }
        else
        {
            sprintf(iconnum, "item_%d.png",icon);
            baowu1=CCSprite::create(iconnum);
            baowu1->setPosition(ccp(120, 305));
            this->addChild(baowu1,3);
        }
        
        
        
        
        
    }
    //    CCLabelTTF *goback=CCLabelTTF::create("返  回", "Marker Felt", 30);
    //    goback->setPosition(ccp(78, 35));
    CCMenuItemImage * btn2=CCMenuItemImage::create("common_btn_return_1.png", "common_btn_return_2.png",this,menu_selector(GameOver::goBackToHome));
    btn2->setScale(1.3);
    //    btn2->addChild(goback);
    //    btn2->setPosition(ccp(0, -165));
    CCMenu *menu =CCMenu::create(btn2,NULL);
    menu->setPosition(ccp(size.width/2, 198));
    this->addChild(menu,3);
}
void GameOver::repateFire(CCNode * sender){
    CData::getCData()->setyinxiao();
    
}
void GameOver::star1(){
    printf("star %d\n",star);
    if(star==1){
        CCSprite *star1=CCSprite::create("zjm_star.png");
        //        star1->setAnchorPoint(ccp(0, 0));
        star1->setPosition(ccp(size.width/2, size.height/2-200));
        
        this->addChild(star1,4);
        
        
        CCActionInterval * setbig=CCScaleTo::create(0.0001, 5);
        star1->runAction(setbig);
        //        CCActionInterval * fadeout=CCFadeOut::create(0.0001);
        //        star1->runAction(fadeout);
        CCActionInterval * fadein=CCFadeIn::create(0.1);
        star1->runAction(fadein);
        CCActionInterval * setsmall=CCScaleTo::create(0.1, 1);
        star1->runAction(setsmall);
        CCActionInterval * moveto=CCMoveTo::create(0.2, ccp(size.width/2+60, size.height/2+160));
        
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(GameOver::gasRun));
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(GameOver::zhenping));
        CCFiniteTimeAction *playerAct=CCSequence::create(moveto,func,fun2,NULL);
        star1->runAction(playerAct);
        
        
    }
    else if (star==2||star==3){
        CCSprite *star1=CCSprite::create("zjm_star.png");
        //        star1->setAnchorPoint(ccp(0, 0));
        star1->setPosition(ccp(size.width/2, size.height/2-200));
        //star1->setPosition(ccp(280, 680));
        this->addChild(star1,4);
        
        
        CCActionInterval * setbig=CCScaleTo::create(0.0001, 5);
        star1->runAction(setbig);
        //        CCActionInterval * fadeout=CCFadeOut::create(0.0001);
        //        star1->runAction(fadeout);
        CCActionInterval * fadein=CCFadeIn::create(0.2);
        star1->runAction(fadein);
        CCActionInterval * setsmall=CCScaleTo::create(0.2, 1);
        star1->runAction(setsmall);
        CCActionInterval * moveto=CCMoveTo::create(0.2, ccp(size.width/2+60, size.height/2+160));
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(GameOver::zhenping));
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(GameOver::star2));
        CCFiniteTimeAction *playerAct=CCSequence::create(moveto,func,fun2,NULL);
        star1->runAction(playerAct);
    }
    
}
void GameOver::star2(){
    if(star==2){
        CCSprite *star2=CCSprite::create("zjm_star.png");
        //        star2->setAnchorPoint(ccp(0, 0));
        star2->setPosition(ccp(size.width/2,size.height/2-200));
        this->addChild(star2,4);
        
        
        CCActionInterval * setbig=CCScaleTo::create(0.0001, 5);
        star2->runAction(setbig);
        //        CCActionInterval * fadeout=CCFadeOut::create(0.0001);
        //        star2->runAction(fadeout);
        CCActionInterval * fadein=CCFadeIn::create(0.2);
        star2->runAction(fadein);
        CCActionInterval * setsmall=CCScaleTo::create(0.2, 1);
        star2->runAction(setsmall);
        CCActionInterval * moveto=CCMoveTo::create(0.2, ccp(size.width/2+115, size.height/2+160));
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(GameOver::zhenping));
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(GameOver::gasRun));
        CCFiniteTimeAction *playerAct=CCSequence::create(moveto,func,fun2,NULL);
        star2->runAction(playerAct);
        
    }
    else if (star==3){
        CCSprite *star2=CCSprite::create("zjm_star.png");
        //        star2->setAnchorPoint(ccp(0, 0));
        star2->setPosition(ccp(size.width/2,size.height/2-200));
        this->addChild(star2,4);
        
        
        CCActionInterval * setbig=CCScaleTo::create(0.0001, 5);
        star2->runAction(setbig);
        //        CCActionInterval * fadeout=CCFadeOut::create(0.0001);
        //        star2->runAction(fadeout);
        CCActionInterval * fadein=CCFadeIn::create(0.2);
        star2->runAction(fadein);
        CCActionInterval * setsmall=CCScaleTo::create(0.2, 1);
        star2->runAction(setsmall);
        CCActionInterval * moveto=CCMoveTo::create(0.2, ccp(size.width/2+115, size.height/2+160));
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(GameOver::zhenping));
        CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(GameOver::star3));
        CCFiniteTimeAction *playerAct=CCSequence::create(moveto,func,fun2,NULL);
        star2->runAction(playerAct);
    }
}
void GameOver::star3(){
    
    CCSprite *star3=CCSprite::create("zjm_star.png");
    //    star3->setAnchorPoint(ccp(0, 0));
    star3->setPosition(ccp(size.width/2,size.height/2-200));
    this->addChild(star3,4);
    
    
    CCActionInterval * setbig=CCScaleTo::create(0.0001, 5);
    star3->runAction(setbig);
    //    CCActionInterval * fadeout=CCFadeOut::create(0.0001);
    //    star3->runAction(fadeout);
    CCActionInterval * fadein=CCFadeIn::create(0.2);
    star3->runAction(fadein);
    CCActionInterval * setsmall=CCScaleTo::create(0.2, 1);
    star3->runAction(setsmall);
    CCActionInterval * moveto=CCMoveTo::create(0.2, ccp(size.width/2+175, size.height/2+160));
    CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(GameOver::zhenping));
    CCCallFunc * fun2=CCCallFunc::create(this, callfunc_selector(GameOver::gasRun));
    CCFiniteTimeAction *playerAct=CCSequence::create(moveto,func,fun2,NULL);
    star3->runAction(playerAct);
}
void GameOver::gasRun(){
    
}
void GameOver::faild(){
    CCSprite *bg=CCSprite::create("firefaild.png");
    bg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bg);
    ccColor3B ycolor = ccc3(120, 80, 20);
    char tmp[50] = "";
    sprintf(tmp, "+ %d",exp);
    
    CCLabelTTF* weittf = CCLabelTTF::CCLabelTTF::create(tmp, "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentCenter);
    weittf->setPosition(ccp(120, 395));
    weittf->setColor(ycolor);
    bg->addChild(weittf);
    char tmp1[50] = "";
    sprintf(tmp1, "+ %d",coin);
    
    CCLabelTTF* goldttf = CCLabelTTF::CCLabelTTF::create(tmp1, "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentCenter);
    goldttf->setPosition(ccp(240, 395));
    goldttf->setColor(ycolor);
    bg->addChild(goldttf);
    char tmp2[50] = "";
    sprintf(tmp2, "%d",huoli1);
    
    CCLabelTTF* huolittf = CCLabelTTF::CCLabelTTF::create(tmp2, "hycc.ttf", 18,CCSizeMake(200, 0),kCCTextAlignmentCenter);
    huolittf->setPosition(ccp(358, 395));
    huolittf->setColor(ycolor);
    bg->addChild(huolittf);

    CCMenuItemImage * btn2=CCMenuItemImage::create("common_btn_return_1.png", "common_btn_return_2.png",this,menu_selector(GameOver::goBackToHome));
    btn2->setScale(1.3);
    //    btn2->addChild(fanhui);
    //    btn2->setPosition(ccp(0, -165));
    CCMenu *menu =CCMenu::create(btn2,NULL);
    menu->setPosition(ccp(size.width/2, 198));
    this->addChild(menu,5);
}
void GameOver::shake(){
    CData::getCData()->setyinxiao();
    
}
void GameOver::goBackToHome(){
    CData::getCData()->setyinxiao();
    
    //    load=Loading::create();
    //    this->addChild(load,9999);
    
    
    CCScene *newscene=CCScene::create();//homepage  beginAni
    homePage* hp = homePage::create();
    newscene->addChild(hp);
    
    CCDirector::sharedDirector()->replaceScene(newscene);
    
    
    this->removeFromParent();
}
void GameOver::receiveGoHomeBack(){
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(4500);
    CData::getCData()->m_dictionary->removeObjectForKey(4500);
    
    if(revMsg){
        this->unschedule(schedule_selector(GameOver::receiveGoHomeBack));
        
        CData::getCData()->cityData = revMsg->data;
        printf("%s---------------------",revMsg->data);
        
        
        load->removeFromParent();
        
        
        CCScene *homePage=CCScene::create();//homepage  beginAni
        homePage->addChild(homePage::create());
        //        CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5, homePage));
        CCDirector::sharedDirector()->replaceScene(homePage);
        
        
        this->removeFromParent();
        
        
    }
}
void GameOver::zhenping(){

}
void GameOver::zhaomuwujiang(){
    
    // CCDirector::sharedDirector()->popScene();
}

GameOver::~GameOver()
{
    //    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}