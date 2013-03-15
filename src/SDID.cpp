/* 
 * SD-ID Parser
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

#include "SDID.h"

using namespace std;

SDID::SDID(const string &name, const unsigned &privateEntrepriseNumber) {
    setName(name);
    setPrivateEntrepriseNumber(privateEntrepriseNumber);
}

SDID::SDID(const SDID& orig) {
    setName(orig.getName());
    setPrivateEntrepriseNumber(orig.getPrivateEntrepriseNumber());
}

void SDID::setName(const string name)
{
    _name = name;
    return;
}
 
string SDID::getName() const
{
    return _name;
}

void SDID::setPrivateEntrepriseNumber(const unsigned privateEntrepriseNumber)
{
    _privateEntrepriseNumber = privateEntrepriseNumber;
    return;
}
 
unsigned SDID::getPrivateEntrepriseNumber() const
{
    return _privateEntrepriseNumber;
}


SDID::~SDID() {
}

