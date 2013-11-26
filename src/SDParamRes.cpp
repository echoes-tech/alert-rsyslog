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
//    vector<string> sIDs;
//
//    boost::split(sIDs, _key, boost::is_any_of("-"), boost::token_compress_on);

    try
    {
        setIdaId(boost::lexical_cast<long long>(_key));
        //FIXME
//        setValueNum(boost::lexical_cast<int>(sIDs[4]));
//        setLotNumber(boost::lexical_cast<unsigned>(sIDs[5]));
//        setLineNumber(boost::lexical_cast<unsigned>(sIDs[6]));
    }
    catch (boost::bad_lexical_cast &)
    {
        logger.entry("error") << "[SDParamRes] All IDs are not the right type on SD-Element Res";
    }
}

SDParamRes::SDParamRes(const SDParamRes& orig) : SDParam(orig)
{
    setIdaId(orig.getIdaId());
    setLotNumber(orig.getLotNumber());
    setLineNumber(orig.getLineNumber());
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

void SDParamRes::setLotNumber(unsigned lotNumber)
{
    _lotNumber = lotNumber;

    return;
}

unsigned SDParamRes::getLotNumber() const
{
    return _lotNumber;
}

void SDParamRes::setLineNumber(unsigned lineNumber)
{
    _lineNumber = lineNumber;

    return;
}

unsigned SDParamRes::getLineNumber() const
{
    return _lineNumber;
}

