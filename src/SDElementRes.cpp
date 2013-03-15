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

SDElementRes::SDElementRes(SDElement& sdElement) : SDElement(sdElement) {
    detectResKeys();
}

SDElementRes::SDElementRes(const SDElementRes& orig) : SDElement(orig)  {
    setOffset(orig.getOffset());
    setIDPlugin(orig.getIDPlugin());
    setIDAsset(orig.getIDAsset());
    setIDSource(orig.getIDSource());
    setIDSearch(orig.getIDSearch());
    setValueNum(orig.getValueNum());
    setLotNumber(orig.getLotNumber());
    setLineNumber(orig.getLineNumber());
}

void SDElementRes::detectResKeys()
{   
    for (unsigned i(0); i < _sdParamsPtr.size(); ++i)
    {
        if(_sdParamsPtr[i]->getKey().compare("offset"))
        {
            try
            {
                setOffset(boost::lexical_cast<unsigned>(_sdParamsPtr[i]->getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
                std::cout << "** Offset is not an unsigned on SD-Element Res **\n";
            }
        }
        else
        {
            // 2-1-1-2-1-1

            vector<string> sIDs;
            string keyTmp = _sdParamsPtr[i]->getKey();
            boost::split(sIDs, keyTmp, boost::is_any_of("-"), boost::token_compress_on);
            
            try
            {
                setIDPlugin(boost::lexical_cast<int>(sIDs[0]));
                setIDAsset(boost::lexical_cast<int>(sIDs[1]));
                setIDSource(boost::lexical_cast<int>(sIDs[2]));
                setIDSearch(boost::lexical_cast<int>(sIDs[3]));
                setValueNum(boost::lexical_cast<int>(sIDs[4]));
                setLotNumber(boost::lexical_cast<int>(sIDs[5]));
                setLineNumber(boost::lexical_cast<int>(sIDs[6]));
            }
            catch (boost::bad_lexical_cast &)
            {
                std::cout << "** IDs is not an unsigned on SD-Element Res **\n";
            }
        }
    }
    
    return;
}

void SDElementRes::setOffset(unsigned offset) {
    _offset = offset;

    return;
}

unsigned SDElementRes::getOffset() const {
    return _offset;
}

void SDElementRes::setIDPlugin(unsigned idPlugin) {
    _idPlugin = idPlugin;

    return;
}

unsigned SDElementRes::getIDPlugin() const {
    return _idPlugin;
}

void SDElementRes::setIDAsset(unsigned idAsset) {
    _idAsset = idAsset;

    return;
}

unsigned SDElementRes::getIDAsset() const {
    return _idAsset;
}

void SDElementRes::setIDSource(unsigned idSource) {
    _idSource = idSource;

    return;
}

unsigned SDElementRes::getIDSource() const {
    return _idSource;
}

void SDElementRes::setIDSearch(unsigned idSearch) {
    _idSearch = idSearch;

    return;
}

unsigned SDElementRes::getIDSearch() const {
    return _idSearch;
}

void SDElementRes::setValueNum(unsigned valueNum) {
    _valueNum = valueNum;

    return;
}

unsigned SDElementRes::getValueNum() const {
    return _valueNum;
}

void SDElementRes::setLotNumber(unsigned lotNumber) {
    _lotNumber = lotNumber;

    return;
}

unsigned SDElementRes::getLotNumber() const {
    return _lotNumber;
}

void SDElementRes::setLineNumber(unsigned lineNumber) {
    _lineNumber = lineNumber;

    return;
}

unsigned SDElementRes::getLineNumber() const {
    return _lineNumber;
}

SDElementRes::~SDElementRes() {
}

