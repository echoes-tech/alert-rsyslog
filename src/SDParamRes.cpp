/* 
 * SD-Param Result Parser
 * @author ECHOES Technologies (FPO)
 * @date 20/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */
#include "SDParamRes.h"

using namespace std;

SDParamRes::SDParamRes(const SDParam& sdParam) : SDParam(sdParam)
{
    try
    {
        setIdaId(boost::lexical_cast<long long>(_key));
    }
    catch (boost::bad_lexical_cast &)
    {
        logger.entry("error") << "[SDParamRes] All IDs are not the right type on SD-Element Res";
    }
}

SDParamRes::SDParamRes(const SDParamRes& orig) : SDParam(orig)
{
    setIdaId(orig.getIdaId());
}

SDParamRes::~SDParamRes()
{
}

void SDParamRes::setIdaId(long long idaId)
{
    _idaId = idaId;

    return;
}

long long SDParamRes::getIdaId() const
{
    return _idaId;
}

