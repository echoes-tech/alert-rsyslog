/* 
 * Main
 * @author ECHOES Technologies (FPO)
 * @date 14/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS
 * WITHOUT COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include <tools/Session.h>

#include "Conf.h"
#include "StructuredData.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
//    string token("");
//    unsigned probeVersion;

    Conf *conf = new Conf();

    string connection = "hostaddr=" + conf->getDBHost() +
                        " port=" + boost::lexical_cast<string>(conf->getDBPort()) +
                        " dbname=" + conf->getDBName() +
                        " user=" + conf->getDBUser() +
                        " password=" + conf->getDBPassword();
    
    // Setting the session
//    session = new Session(connection);

    StructuredData *sd = new StructuredData(cin);

//    parseProperties(sd->getSDProp, probeVersion, token);
//    parseAndStoreRes(sd->getSDRes, probeVersion, token);
  
    return 0;
}

