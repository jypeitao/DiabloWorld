
#include "MyXmlParser.h"
#include "string.h"
#include <string>
MyXmlParser* MyXmlParser::create(const char *filename)
{
    MyXmlParser *parser = new MyXmlParser();
    parser->initWithFilename(filename);
    return parser;
}
bool MyXmlParser::initWithFilename(const char *filename)
{
    dic = CCDictionary::create();
    dic->retain();
    CCSAXParser *parser = new CCSAXParser();
    parser->setDelegator(this);
    parser->init("UTF_8");
    parser->parse(filename);
}
void MyXmlParser::startElement(void *ctx, const char *name, const char **atts)
{
    CCLog("star=%s",name);
    startName = name;
}
void MyXmlParser::endElement(void *ctx, const char *name)
{
    CCLog("end=%s",name);
}
void MyXmlParser::textHandler(void *ctx, const char *s, int len)
{
    if(dic->objectForKey(startName))
    {
        return;
    }
    const std::string text = std::string(s,0,len);
    dic->setObject( CCString::create(text), startName);
}
CCDictionary* MyXmlParser::getData()
{
    return dic;
}
