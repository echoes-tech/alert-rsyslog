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
    vector<string> sIDs;

    boost::split(sIDs, _key, boost::is_any_of("-"), boost::token_compress_on);

    try
    {
        setIDPlugin(boost::lexical_cast<long long>(sIDs[0]));
        setIDAsset(boost::lexical_cast<long long>(sIDs[1]));
        setIDSource(boost::lexical_cast<long long>(sIDs[2]));
        setIDSearch(boost::lexical_cast<long long>(sIDs[3]));
        setValueNum(boost::lexical_cast<int>(sIDs[4]));
        setLotNumber(boost::lexical_cast<unsigned>(sIDs[5]));
        setLineNumber(boost::lexical_cast<unsigned>(sIDs[6]));
    }
    catch (boost::bad_lexical_cast &)
    {
        logger.entry("error") << "[SDParamRes] All IDs are not the right type on SD-Element Res";
    }
}

SDParamRes::SDParamRes(const SDParamRes& orig) : SDParam(orig)
{
    setIDPlugin(orig.getIDPlugin());
    setIDAsset(orig.getIDAsset());
    setIDSource(orig.getIDSource());
    setIDSearch(orig.getIDSearch());
    setValueNum(orig.getValueNum());
    setLotNumber(orig.getLotNumber());
    setLineNumber(orig.getLineNumber());
}

SDParamRes::~SDParamRes()
{
}

void SDParamRes::setIDPlugin(long long idPlugin)
{
    _idPlugin = idPlugin;

    return;
}

long long SDParamRes::getIDPlugin() const
{
    return _idPlugin;
}

void SDParamRes::setIDAsset(long long idAsset)
{
    _idAsset = idAsset;

    return;
}

long long SDParamRes::getIDAsset() const
{
    return _idAsset;
}

void SDParamRes::setIDSource(long long idSource)
{
    _idSource = idSource;

    return;
}

long long SDParamRes::getIDSource() const
{
    return _idSource;
}

void SDParamRes::setIDSearch(long long idSearch)
{
    _idSearch = idSearch;

    return;
}

long long SDParamRes::getIDSearch() const
{
    return _idSearch;
}

void SDParamRes::setValueNum(int valueNum)
{
    _valueNum = valueNum;

    return;
}

int SDParamRes::getValueNum() const
{
    return _valueNum;
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

