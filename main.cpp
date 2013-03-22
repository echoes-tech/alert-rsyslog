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
    int res = EXIT_FAILURE;
    Conf *conf = NULL;
    Session *session = NULL;
    string input = "";

    Wt::log("info") << "[origin enterpriseId=\"40311\" software=\"ECHOES Alert - Rsyslog Parser\" swVersion=\"0.1.0.beta3\"] (re)start";
    
    // Loading conf
    conf = new Conf();
    if (conf->getDBPort() != 0)
    {
        SyslogInsert *syslogInsert = NULL;
        StructuredData *sd = NULL;

        // Setting the session
        session = new Session(conf->getSessConnectParams());

        getline(cin, input);

        while (input.compare("EOF"))
        {
            // Processing the Syslog Insertion and detection Structured Data
            syslogInsert = new SyslogInsert(input, session);

            sd = new StructuredData(syslogInsert->getSD(), syslogInsert->getID(), session);

            delete sd;
            delete syslogInsert;

            getline(cin, input);
        }

        delete session;

        res = EXIT_SUCCESS;
    }

    delete conf;

    Wt::log("info") << "[origin enterpriseId=\"40311\" software=\"ECHOES Alert - Rsyslog Parser\" swVersion=\"0.1.0.beta3\"] stop";
    
    return res;
}

