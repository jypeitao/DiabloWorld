
#ifndef Client_Test_h
#define Client_Test_h
#include "cocos2d.h"
USING_NS_CC;
class MyXmlParser:public CCSAXDelegator
{
public:
    static MyXmlParser* create(const char *filename);
    bool initWithFilename(const char *filename);
    virtual void startElement(void *ctx, const char *name, const char **atts);
    virtual void endElement(void *ctx, const char *name);
    virtual void textHandler(void *ctx, const char *s, int len);
    CCDictionary* getData();
private:
    CCDictionary *dic;
   std::string startName;
    std::string endXmlElement;//用来记录每个key后字段
    std::string currString;//记录每个value的值
};

#endif
