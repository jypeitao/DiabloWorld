#include "cocos2d.h"
#include "LanguageManager.h"
#include "MyXmlParser.h"
static LanguageManager *pLanguageManager=NULL;
LanguageManager* LanguageManager::sharLanguageManager()
{
    if(!pLanguageManager)
    {
        pLanguageManager = new LanguageManager();
    }
    return pLanguageManager;
}
LanguageManager::LanguageManager()
{
    type = CCApplication::sharedApplication()->getCurrentLanguage();
    parser = MyXmlParser::create("language.xml");
}
const char* LanguageManager::getTextByName(char *pName)
{
    char *pType = NULL;
    switch(type)
    {
        case kLanguageChinese:pType = "zh";break;
        default: /*kLanguageEnglish:*/pType = "en";
    }
    CCString *name = CCString::createWithFormat("%s-%s",pName,pType);
    return ((CCString*)parser->getData()->objectForKey(name->m_sString))->m_sString.data();
}

