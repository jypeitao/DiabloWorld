#ifndef Client_language_h
#define Client_language_h
#include "MyXmlParser.h"
USING_NS_CC;
class LanguageManager
{
public:
     static LanguageManager* sharLanguageManager();
    const char* getTextByName(char *pName);
private:
       LanguageManager();
    ccLanguageType type;
    MyXmlParser* parser;
};
#endif
