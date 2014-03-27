#include "MyMenu.h"

void MyMenu::registerWithTouchDispatcher(){
    CCDirector *dir=CCDirector::sharedDirector();
    dir->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    
}
bool MyMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    
    moved = false;
    return CCMenu::ccTouchBegan(touch, event);
    
}
void MyMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if(!moved)
    {
        CCMenu::ccTouchEnded(touch, event);
    }
    
    if (m_pSelectedItem)
    {
        m_pSelectedItem->unselected();
    }

    m_eState = kCCMenuStateWaiting;
   
}
void MyMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    moved = true;
    CCMenu::ccTouchMoved(touch, event);
}