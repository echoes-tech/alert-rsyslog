/* 
 * SD-Element Parser
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

#include "SDElement.h"

using namespace std;

SDElement::SDElement(string &content) {
    _sdIDPtr = NULL;
    
    setContent(content);
    detectSDID();
    splitSDParams();
}

SDElement::SDElement(const SDElement& orig) {
    setContent(orig.getContent());
    setSDIDPtr(orig.getSDIDPtr());
    setSDParamPtr(orig.getSDParamsPtr());
}

void SDElement::setContent(string content)
{
    _content = content;

    return;
}

string SDElement::getContent() const
{
    return _content;
}

void SDElement::detectSDID()
{
    if(_content.compare(""))
    {
        boost::regex e("^(\\w+)@(\\d+)");
        boost::smatch what;

        if (boost::regex_match(_content, what, e, boost::match_extra))
        {
            if (what.size() == 3) {
                try
                {
                    setSDIDPtr( new SDID(what[1], boost::lexical_cast<unsigned>(what[2])) );
                }
                catch (boost::bad_lexical_cast &)
                {
                    std::cout << "** Probe version is not an unsigned on SD-Element Prop **\n";
                }
            }
            else
            {
                std::cout << "** Bad number of elements on SD-Element Prop **\n";
            }
        }
        else
        {
            std::cout << "** No Match found **\n";
        }
    }
    else
    {
        std::cout << "** No SD-Element Prop found **\n";
    }

    return;
}

void SDElement::setSDIDPtr(SDID *sdIDPtr)
{
    _sdIDPtr = sdIDPtr;

    return;
}

SDID* SDElement::getSDIDPtr() const
{
    return _sdIDPtr;
}

void SDElement::splitSDParams()
{
    string sdParamsTmp(_content);
    vector<string> sSDParams;
    unsigned i = 0;
    SDParamPtr sdParamPtr;
    
    //offset=2 4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE" 4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"

    boost::split(sSDParams, sdParamsTmp, boost::is_any_of(" "), boost::token_compress_on);
    //offset=2
    //4-1-3-4-1-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"
    //4-1-3-4-2-1-1="U3VjaCBJbnN0YW5jZSBjdXJyZW50bHkgZXhpc3RzIGF0IHRoaXMgT0lE"

    for (i = 0; i < sSDParams.size(); ++i)
    {
        sdParamPtr.reset( new SDParam(sSDParams[i]) );

        addSDParamPtr(sdParamPtr);
    }
    
    return;
}

void SDElement::setSDParamPtr(vector<SDParamPtr> sdParamsPtr)
{
    _sdParamsPtr = sdParamsPtr;

    return;
}


void SDElement::addSDParamPtr(SDParamPtr sdParamPtr)
{
    _sdParamsPtr.push_back(sdParamPtr);
    return;
}

vector<SDParamPtr> SDElement::getSDParamsPtr() const
{
    return _sdParamsPtr;
}

SDElement::~SDElement() {
    delete(_sdIDPtr);
}

