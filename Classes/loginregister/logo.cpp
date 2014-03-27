#include "logo.h"
//#include "LayerLogin.h"

bool logo::init()
{
    bool flag = false;
    if (!Layer::init())
    {
        return false;
    }
    flag = true;
    Size winSize = Director::getInstance()->getWinSize();
    Sprite *sprite = Sprite::create("Default.png");
    sprite->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(sprite);
    FadeOut *out = FadeOut::create(2.0f);
    CallFunc *call = CallFunc::create(CC_CALLBACK_0(logo::replace,this));
    FiniteTimeAction *finite = Sequence::create(out, call, NULL);
    sprite->runAction(finite);
    return flag;
}

void logo::replace()
{
//    Scene *scene = Scene::create();
//    Layer *layer = LayerLogin::create();
//    scene->addChild(layer);
//    Director::getInstance()->replaceScene(scene);
}
