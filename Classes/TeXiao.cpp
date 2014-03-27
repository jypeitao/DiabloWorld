#include "TeXiao.h"

static texiao * tx=NULL;

//bool texiao::init(){
//    if(!CCSprite::init()){
//        return  false;
//    }
//    this->texiaoCreate();
//    return true;
//}
texiao::texiao(){
    //加载图片缓存
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("result_attacked.plist");
    
}
texiao::~texiao(){
    
}
texiao * texiao::TX(){
    if (!tx) {
        tx= new texiao();
    }
    return tx;
}
CCSprite * texiao::lingqucg(){
    CCArray *lqcg=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("lq_lq_01.png");
    CCSprite *lq=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=8; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "lq_lq_%02d.png",i);
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(allnames);
        //CCString::createWithFormat("zxj_%02d.png",i)->getCString()
        
        lqcg->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(lqcg,0.15f)));
    lq->runAction(Action);
    return lq;

}
CCSprite * texiao::duoqucg(){
    CCArray *dqsb=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("lq_cg_01.png");
    CCSprite *dq=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "lq_cg_%02d.png",i);
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(allnames);
        //CCString::createWithFormat("zxj_%02d.png",i)->getCString()
        
        dqsb->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(dqsb,0.15f)));
    dq->runAction(Action);
    return dq;
}
CCSprite * texiao::duoqusb(){
    CCArray *dqcg=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("lq_sb_01.png");
    CCSprite *dq=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "lq_sb_%02d.png",i);
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(allnames);
        //CCString::createWithFormat("zxj_%02d.png",i)->getCString()
        
        dqcg->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(dqcg,0.15f)));
    dq->runAction(Action);
    return dq;
}
CCSprite * texiao::yanwu(){
    CCArray *yanwu=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ef_01.png");
    CCSprite *yw=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=22; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "ef_%02d.png",i);
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(allnames);
        //CCString::createWithFormat("zxj_%02d.png",i)->getCString()
        
        yanwu->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(yanwu,0.083f)));
    yw->runAction(Action);
    return yw;

}
CCSprite * texiao::dayan(){
    CCArray *daya=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("dy_00016.png");
    CCSprite *yw=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=16;i<=62; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "dy_%05d.png",i);
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(allnames);
        daya->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(daya,0.0417f)));
    yw->runAction(Action);
    return yw;
}
CCSprite * texiao::texiaosCreate(const char *name, int num){
    char names[20]="";
    sprintf(names, "%s_01.png",name);
    CCArray *zuixingArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(names);//"zxj_01.png"
    CCSprite *zxjsp=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=num; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "%s_%02d.png",name,i);
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(allnames);
        //CCString::createWithFormat("zxj_%02d.png",i)->getCString()
        
        zuixingArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(zuixingArr,0.125f)));
    zxjsp->runAction(Action);
    return zxjsp;
}
//受伤特效
CCSprite * texiao:: texiaoCreate(){

    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("result_00001.png");
    CCSprite *tzsp=CCSprite::createWithSpriteFrame(pFrame);
    CCArray * kneif=CCArray::create();
  
            for (int i=2;i<=8; i++)
            {

                CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("result_%05d.png",i)->getCString());
                
                kneif->addObject(spf);
                
            }


    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(kneif,0.2f)));
    tzsp->runAction(Action);
    return tzsp;

    
}
CCSprite * texiao::beginyanwu(){
    CCArray *touzhiArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("begin_yw_01.png");
    CCSprite *tzsp=CCSprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=16; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("begin_yw_%02d.png",i)->getCString());
        
        touzhiArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(touzhiArr,0.125f)));
    tzsp->runAction(Action);
    return tzsp;
}
//投掷特效
CCSprite * texiao:: touzhiCreate(){

    CCArray *touzhiArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tz-01.png");
    CCSprite *tzsp=CCSprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=8; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tz-%02d.png",i)->getCString());
        
        touzhiArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(touzhiArr,0.2f)));
    tzsp->runAction(Action);
    return tzsp;
}
//投掷命中特效
CCSprite * texiao::mingzhongCreate(){
    CCArray *mingzhongArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("mz-01.png");
    CCSprite *mzsp=CCSprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=7; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("mz-%02d.png",i)->getCString());
        
        mingzhongArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(mingzhongArr,0.2f)));
    mzsp->runAction(Action);
    return mzsp;

}
//普通攻击
CCSprite * texiao::normalAttackCreate(){
    CCArray *mingzhongArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("n_attack_01.png");
    CCSprite *mzsp=CCSprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=5; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("n_attack_%02d.png",i)->getCString());
        
        mingzhongArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(mingzhongArr,0.1f)));
    mzsp->runAction(Action);
    return mzsp;

}
//醉醒技
CCSprite * texiao::zuixingji(){
    CCArray *zuixingArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("zxj_01.png");
    CCSprite *zxjsp=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=10; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("zxj_%02d.png",i)->getCString());
        
        zuixingArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(zuixingArr,0.1f)));
    zxjsp->runAction(Action);
    return zxjsp;

}
//太极八卦
CCSprite * texiao::taijibagua(){
    CCArray *tjbgArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tjbg_01.png");
    CCSprite *tjbgsp=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=12; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tjbg_%02d.png",i)->getCString());
        
        tjbgArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(tjbgArr,0.1f)));
    tjbgsp->runAction(Action);
    return tjbgsp;
}
//天公怒
CCSprite * texiao::tiangongnu(){
    CCArray *tgnArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tgn_01.png");
    CCSprite *tgnsp=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tgn_%02d.png",i)->getCString());
        
        tgnArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(tgnArr,0.1f)));
    tgnsp->runAction(Action);
    return tgnsp;
}
//遇神诛神
CCSprite * texiao::yushenzhushen(){
    CCArray *yszsArr=CCArray::create();
    CCSpriteFrame *pFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("yszs_01.png");
    CCSprite *yszssp=CCSprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        
        CCSpriteFrame *spf=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("yszs_%02d.png",i)->getCString());
        
        yszsArr->addObject(spf);
        
    }
    
    CCActionInterval * Action=CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(yszsArr,0.1f)));
    yszssp->runAction(Action);
    return yszssp;
}
//CCSprite * texiao::huangquezhen(){
//    
//}
//CCSprite * texiao::kunshouzhidou(){
//    
//}//困兽之斗
//CCSprite * texiao::luandaozhan(){
//    
//}//乱刀斩
//CCSprite * texiao::meirenji(){
//    
//}//美人计
//CCSprite * texiao::pojunji(){
//    
//}//破军计
//CCSprite * texiao::qubingji(){
//    
//}//屈兵计
//CCSprite * texiao::shengdongjixi_mz(){
//    
//}//声东击西-命中
//CCSprite * texiao::shengdongjixi_tz(){
//    
//}//声东击西-投掷
//CCSprite * texiao::shijizhou(){
//    
//}//狮子吼
//CCSprite * texiao::shuangfuzhishang_cz(){
//    
//}//双斧之伤-出招
//CCSprite * texiao::shuangfuzhishang_mz(){
//    
//}//双斧之伤-命中
//CCSprite * texiao::shuangjizhishang_cz(){
//    
//}//双戟之伤-出招
//CCSprite * texiao::texiao::shuangjizhishang_mz(){
//    
//}//双戟之伤-命中
//CCSprite * texiao::shuanglianzhishang_cz(){
//    
//}//双廉之伤-出招
//CCSprite * texiao::shuanglianzhishang_mz(){
//    
//}//双廉之伤-命中
//CCSprite * texiao::shuangqiangzhishang_cz(){
//    
//}//双枪之伤-出招
//CCSprite * texiao::shuangqiangzhishang_mz()
//{
//    
//}//双枪之伤-命中
//CCSprite * texiao::shuangrenzhishang_cz(){
//    
//}//双刃之伤-出招
//CCSprite * texiao::shuangrenzhishang_mz(){
//    
//}//双刃之伤-命中
//CCSprite * texiao::shuijisanqianli(){
//    
//}//水击三千里
//CCSprite * texiao::touxi(){
//    
//}//偷袭
//CCSprite * texiao::wanlibingfeng(){
//    
//}//万里冰封
//CCSprite * texiao::xiefengzhen(){
//    
//}//邪风阵
//CCSprite * texiao::yehuoliaoyuan(){
//    
//}//野火燎原
//移除方法
void texiao::removeSprite(CCNode *sender){
    this->removeFromParentAndCleanup(true);
}
