#include "startAnimate.h"
#include "xuanren.h"

bool startAnimate::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("guild.plist");
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    str1=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bgk1.png"));
    str1->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(str1);
    
    str2=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("words.png"));
    str2->setPosition(ccp(winSize.width/2-60, winSize.height/2+160));
    str2->setVisible(false);
    this->addChild(str2);
    
    str3=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("words1.png"));
    str3->setPosition(ccp(winSize.width/2-10, winSize.height/2+90));
    str3->setVisible(false);
    this->addChild(str3);
    
    str4=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bgk2.png"));
    str4->setPosition(ccp(winSize.width/2, winSize.height/2));
    str4->setVisible(false);
    this->addChild(str4);
    
    str7=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("words2.png"));
    str7->setPosition(ccp(winSize.width/2-60, winSize.height/2+160));
    str7->setVisible(false);
    this->addChild(str7);
    
    str5=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bgk3.png"));
    str5->setPosition(ccp(winSize.width/2, winSize.height/2));
    str5->setVisible(false);
    this->addChild(str5);
    
    str8=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("words3.png"));
    str8->setPosition(ccp(winSize.width/2-60, winSize.height/2+160));
    str8->setVisible(false);
    this->addChild(str8);
    
    str6=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bgk4.png"));
    str6->setPosition(ccp(winSize.width/2, winSize.height/2));
    str6->setVisible(false);
    this->addChild(str6);
    
    CCMenuItemImage *item=CCMenuItemImage::create("start_xr.png", "start_xr1.png", this, SEL_MenuHandler(&startAnimate::callbackSelectRole));
    CCMenu *menu=CCMenu::create();
    menu->addChild(item);
    menu->setPosition(ccp(winSize.width/2, 70));
    this->addChild(menu);
    round=0;
    
    CCActionInterval *fadein=CCFadeIn::create(1.5);
    CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(startAnimate::animateDesc));
    CCFiniteTimeAction * final=CCSequence::create(fadein,func,NULL);
    str1->runAction(final);

    return true;
}

void startAnimate::kong()
{
    str1->setVisible(true);
}

void startAnimate::animateDesc()
{
    
    if(round==0)
    {   
        str2->setVisible(true);
        CCActionInterval *fin=CCFadeIn::create(2);
        str2->runAction(fin);
        CCActionInterval *fadeout=CCFadeOut::create(0.7);
        CCActionInterval *delay=CCDelayTime::create(0.7);
        CCActionInterval *moveTo=CCMoveTo::create(0.7, ccp(str2->getPosition().x, str2->getPosition().y));
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(startAnimate::animateDesc));
        CCFiniteTimeAction * final=CCSequence::create(delay,moveTo,fadeout,func,NULL);
        str2->runAction(final);
    }
    else if(round==1)
    {
        CCActionInterval * fadeout=CCFadeOut::create(0.1);
        str3->setVisible(true);
        CCActionInterval * delay=CCDelayTime::create(1.5);
        CCActionInterval * moveto=CCMoveTo::create(0.7, ccp(str3->getPosition().x, str3->getPosition().y));
        CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(startAnimate::animateTwo));
        CCFiniteTimeAction * final=CCSequence::create(delay,moveto,fadeout,func,NULL);
        str3->runAction(final);
    }
    round++;
}

void startAnimate::animateTwo()
{
    CCFadeOut *out=CCFadeOut::create(1.0);
    str1->runAction(out);
    str4->setVisible(true);
    CCActionInterval *fadein=CCFadeIn::create(1);
    str4->runAction(fadein);
    
    CCActionInterval *fadeout=CCFadeOut::create(1.5);
    CCActionInterval *delay=CCDelayTime::create(1.5);
    str7->setVisible(true);
    CCActionInterval *moveTo=CCMoveTo::create(0.7, ccp(str7->getPosition().x, str7->getPosition().y));
    CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(startAnimate::animateThree));
    CCFiniteTimeAction * final=CCSequence::create(delay,moveTo,fadeout,func,NULL);
    str7->runAction(final);

}

void startAnimate::animateThree()
{
    CCFadeOut *out=CCFadeOut::create(1.0);
    str4->runAction(out);
    str5->setVisible(true);
    CCFadeIn *fadein=CCFadeIn::create(2.5);
    str5->runAction(fadein);
    str8->setVisible(true);
    CCFadeIn *in=CCFadeIn::create(1.0);
    str8->runAction(in);
    CCActionInterval * fadeout=CCFadeOut::create(2);
    CCActionInterval * delay=CCDelayTime::create(1.5);

    CCCallFunc * func=CCCallFunc::create(this, callfunc_selector(startAnimate::animateFour));
    CCFiniteTimeAction * final=CCSequence::create(delay,fadeout,func,NULL);
    str8->runAction(final);
}

void startAnimate::animateFour()
{
    CCFadeOut *out=CCFadeOut::create(2.0);
    str5->runAction(out);
    str6->setVisible(true);
    CCFadeIn *fadein=CCFadeIn::create(1.0);
    str6->runAction(fadein);
    CCFadeOut *fadeout=CCFadeOut::create(2.5);
    CCActionInterval *delay=CCDelayTime::create(2);
    CCCallFunc *func=CCCallFunc::create(this, callfunc_selector(startAnimate::callbackSelectRole));
    CCFiniteTimeAction *final=CCSequence::create(delay,fadeout,func,NULL);
    str6->runAction(final);
}

void startAnimate::callbackSelectRole(CCObject *pSender)
{
    CCScene *scene=CCScene::create();
    CCLayer *xr=xuanren::create();
    scene->addChild(xr);
    CCDirector::sharedDirector()->replaceScene(scene);
}

startAnimate::~startAnimate()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("guild.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("guild.png");
}
