/* 
 * SD-Element Propertie Parser
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

#include "SDElementProp.h"

using namespace std;

SDElementProp::SDElementProp(SDElement& sdElement) : SDElement(sdElement) {
    detectPropKeys();
}

SDElementProp::SDElementProp(const SDElementProp& orig) : SDElement(orig) {
    setProbeVersion(orig.getProbeVersion());
    setToken(orig.getToken());
}

void SDElementProp::detectPropKeys()
{   
    for (unsigned i(0); i < _sdParamsPtr.size(); ++i)
    {
        if(_sdParamsPtr[i]->getKey().compare("probe"))
        {
            try
            {
                setProbeVersion(boost::lexical_cast<unsigned>(_sdParamsPtr[i]->getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
                std::cout << "** Probe version is not an unsigned on SD-Element Prop **\n";
            }
        }
        else if (_sdParamsPtr[i]->getKey().compare("token"))
        {
            setToken(_sdParamsPtr[i]->getValue());
        }
    }
    
    return;
}

void SDElementProp::setToken(string token) {
    _token = token;

    return;
}

string SDElementProp::getToken() const {
    return _token;
}

void SDElementProp::setProbeVersion(unsigned probeVersion) {
    _probeVersion = probeVersion;

    return;
}

unsigned SDElementProp::getProbeVersion() const {
    return _probeVersion;
}

SDElementProp::~SDElementProp() {
}

