/* 
 * StructuredData Parser
 * @author ECHOES Technologies (FPO)
 * @date 14/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "StructuredData.h"

using namespace std;

// Retrieve SD given by this binary
StructuredData::StructuredData(const string &content, const long long &syslogID, Session *session)
{
    setSDElementPropPtr(NULL);
    setContent(content);

    splitSDElements(syslogID, session);
}

StructuredData::StructuredData(const StructuredData& orig)
{
    setContent(orig.getContent());
    setSDElementsResPtr(orig.getSDElementsResPtr());
    setSDElementPropPtr(orig.getSDElementPropPtr());
}

void StructuredData::setContent(string content)
{
    _content = content;

    return;
}
 
string StructuredData::getContent() const
{
    return _content;
}

void StructuredData::splitSDElements(const long long &syslogID, Session *session)
{
    // Warning : this method doesn't work well if the value of SD-Params can contain the chars '[' ']'
    
    string sdTmp(_content);
    vector<string> sSDElements;
    SDElement *sdElement = NULL;

    // SD-Element example : [prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"][res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]
    
    boost::erase_all(sdTmp, "[");
    
    // Example : prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"]res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]

    boost::split(sSDElements, sdTmp, boost::is_any_of("]"), boost::token_compress_on);
    // Examples :
    // prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"
    // res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"

    for (unsigned i = 0; i < sSDElements.size(); ++i)
    {
        sdElement = new SDElement(sSDElements[i] );

        if(sdElement->getSDIDPtr()->getName().compare("prop"))
        {
            setSDElementPropPtr(new SDElementProp(*sdElement, syslogID, session));
        }
        else
        {
            addSDElementResPtr(new SDElementRes(*sdElement));
        }
        
        delete(sdElement);
    }
    
    return;
}

void StructuredData::setSDElementsResPtr(vector<SDElementResPtr> sdElementsResPtr) {
    _sdElementsResPtr = sdElementsResPtr;
}

void StructuredData::addSDElementResPtr(SDElementRes *sdElementResPtr)
{
    SDElementResPtr _sdElementResPtr(sdElementResPtr);

    _sdElementsResPtr.push_back(_sdElementResPtr);

    return;
}

vector<SDElementResPtr> StructuredData::getSDElementsResPtr() const
{
    return _sdElementsResPtr;
}

void StructuredData::setSDElementPropPtr(SDElementProp *sdElementPropPtr) {
    _sdElementPropPtr = sdElementPropPtr;

    return;
}

SDElementProp* StructuredData::getSDElementPropPtr() const {
    return _sdElementPropPtr;
}

StructuredData::~StructuredData()
{
    if (_sdElementPropPtr != NULL)
    {
        delete(_sdElementPropPtr);
    }
}


