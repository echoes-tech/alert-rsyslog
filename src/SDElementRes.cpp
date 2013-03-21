/* 
 * SD-Element Result Parser
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

#include "SDElementRes.h"

using namespace std;

SDElementRes::SDElementRes(const SDElement& sdElement) : SDElement(sdElement) {
    setOffset(0);
    detectResKeys();
}

SDElementRes::SDElementRes(const SDElementRes& orig) : SDElement(orig)  {
    setOffset(orig.getOffset());
}

void SDElementRes::detectResKeys()
{   
    SDParamResPtr sdParamResPtr;
    
    for (unsigned i(0); i < _sdParamsPtr.size(); ++i)
    {
        if(!_sdParamsPtr[i]->getKey().compare("offset"))
        {
            try
            {
                setOffset(boost::lexical_cast<unsigned>(_sdParamsPtr[i]->getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
               Wt::log("error") << "[SDElementRes] Offset is not an unsigned on SD-Element Res";
            }
        }
        else if (!boost::starts_with(_sdParamsPtr[i]->getKey(), "res"))
        {
            // 2-1-1-2-1-1
            sdParamResPtr.reset( new SDParamRes(*(_sdParamsPtr[i])) );

            addSDParamResPtr(sdParamResPtr);
        }
    }
    
    return;
}

void SDElementRes::setOffset(unsigned offset)
{
    _offset = offset;

    return;
}

unsigned SDElementRes::getOffset() const
{
    return _offset;
}

void SDElementRes::setSDParamsResPtr(vector<SDParamResPtr> sdParamsResPtr)
{
    _sdParamsResPtr = sdParamsResPtr;

    return;
}


void SDElementRes::addSDParamResPtr(SDParamResPtr sdParamResPtr)
{
    _sdParamsResPtr.push_back(sdParamResPtr);
    return;
}

vector<SDParamResPtr> SDElementRes::getSDParamsResPtr() const
{
    return _sdParamsResPtr;
}

SDElementRes::~SDElementRes()
{
    delete _sdIDPtr;
    _sdIDPtr = NULL;
}

