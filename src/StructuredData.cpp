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

StructuredData::StructuredData(istream &input)
{
    // Retrieve SD given by rsyslog
    setContent(input);
    splitSDElements();
}

StructuredData::StructuredData(const StructuredData& orig)
{
    setContent(orig.getContent());
    setSDElementsPtr(orig.getSDElementsPtr());
}

void StructuredData::setContent(istream& input)
{
    getline(input, _content);

    return;
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

void StructuredData::splitSDElements()
{
    // Warning : this method doesn't work well if the value of SD-Params can contain the chars '[' ']'
    
    string sdTmp(_content);
    vector<string> sSDElements;
    SDElementPtr sdElementPtr;

    // SD-Element example : [prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"][res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]
    
    boost::erase_all(sdTmp, "[");
    
    // Example : prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"]res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"]

    boost::split(sSDElements, sdTmp, boost::is_any_of("]"), boost::token_compress_on);
    // Examples :
    // prop@40311 ver=2 probe=0 token="abcdefghijklmo0123456789"
    // res1@40311 offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"

    for (unsigned i = 0; i < sSDElements.size(); ++i)
    {
        sdElementPtr.reset( new SDElement(sSDElements[i]) );

        addSDElementPtr(sdElementPtr);
    }
    
    return;
}

void StructuredData::setSDElementsPtr(vector<SDElementPtr> sdElementsPtr) {
    _sdElementsPtr = sdElementsPtr;
}

void StructuredData::addSDElementPtr(SDElementPtr sdElementPtr)
{
    _sdElementsPtr.push_back(sdElementPtr);

    return;
}

vector<SDElementPtr> StructuredData::getSDElementsPtr() const
{
    return _sdElementsPtr;
}

StructuredData::~StructuredData()
{
}



