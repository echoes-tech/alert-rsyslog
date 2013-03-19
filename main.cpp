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

#include "Conf.h"
#include "StructuredData.h"
#include "SyslogInsert.h"

using namespace std;

SessionPool* SessionPool::instance = 0;
string SessionPool::credentials = "";
boost::mutex SessionPool::mutex;

/*
 * 
 */
int main(int argc, char** argv) {
    int res = EXIT_SUCCESS;
    Conf *conf = NULL;
    Session *session = NULL;

    // Loading conf
    conf = new Conf();
    if (conf->getDBPort() != 0)
    {    
        // Setting the session
        session = new Session(conf->getSessConnectParams());

        // Processing the Syslog Insertion and detection Structured Data
        SyslogInsert *syslogInsert = new SyslogInsert(cin, session);

        StructuredData *sd = new StructuredData(syslogInsert->getSD(), syslogInsert->getID(), session);
    }
    else
    {
        res = EXIT_FAILURE;
    }
  
    return res;
}

