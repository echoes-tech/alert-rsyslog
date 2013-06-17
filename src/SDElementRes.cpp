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

SDElementRes::SDElementRes(const string &content) : SDElement(content)
{
    setOffset(0);
    detectResKeys();
}

SDElementRes::SDElementRes(const SDElementRes& orig) : SDElement(orig)
{
    setOffset(orig.getOffset());
    setSDParamsRes(orig.getSDParamsRes());
}

SDElementRes::~SDElementRes()
{
}

void SDElementRes::detectResKeys()
{
    for (unsigned i(0); i < _sdParams.size(); ++i)
    {
        if (!_sdParams[i].getKey().compare("offset"))
        {
            try
            {
                setOffset(boost::lexical_cast<unsigned>(_sdParams[i].getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
               logger.entry("error") << "[SDElementRes] Offset is not an unsigned on SD-Element Res";
            }
        }
        else if (!boost::starts_with(_sdParams[i].getKey(), "res"))
        {
            // 2-1-1-2-1-1
            addSDParamRes(SDParamRes(_sdParams[i]));
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

void SDElementRes::setSDParamsRes(vector<SDParamRes> sdParamsRes)
{
    _sdParamsRes = sdParamsRes;

    return;
}


void SDElementRes::addSDParamRes(const SDParamRes &sdParamRes)
{
    _sdParamsRes.push_back(sdParamRes);
    return;
}

vector<SDParamRes> SDElementRes::getSDParamsRes() const
{
    return _sdParamsRes;
}

