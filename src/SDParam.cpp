/* 
 * SD-Param Parser
 * @author ECHOES Technologies (FPO)
 * @date 15/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "SDParam.h"

using namespace std;

SDParam::SDParam(const string &content) {
    setContent(content);
    splitKeyValue();
}

SDParam::SDParam(const SDParam& orig) {
    setContent(orig.getContent());
    setKey(orig.getKey());
    setValue(orig.getValue());
}

void SDParam::setContent(string content)
{
    _content = content;

    return;
}

string SDParam::getContent() const
{
    return _content;
}

void SDParam::splitKeyValue()
{
    string KeyValueTmp(_content), valueTmp;
    vector<string> sKeyValue;
    
    //4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"

    boost::split(sKeyValue, KeyValueTmp, boost::is_any_of("="), boost::token_compress_on);
    setKey(sKeyValue[0]);
    
    //"U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"
    valueTmp = sKeyValue[1];
    
    if (boost::starts_with(valueTmp, "\"") && boost::ends_with(valueTmp, "\"") )
    {
        boost::erase_head(valueTmp, 1);
        boost::erase_tail(valueTmp, 1);
    }
    
    setValue(valueTmp);
    
    return;
}

void SDParam::setKey(string key)
{
    _key = key;
}

string SDParam::getKey() const
{
    return _key;
}

void SDParam::setValue(std::string value) {
    _value = value;
}

std::string SDParam::getValue() const {
    return _value;
}

SDParam::~SDParam() {
}

