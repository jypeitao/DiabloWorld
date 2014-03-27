#ifndef __tsDemo__logo__
#define __tsDemo__logo__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class logo: public Layer
{
public:
    virtual bool init();
    void replace();
    CREATE_FUNC(logo);
};
#endif /* defined(__tsDemo__logo__) */
