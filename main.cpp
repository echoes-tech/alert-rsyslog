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

#include "Logger.h"
#include "Conf.h"
#include "StructuredData.h"
#include "SyslogInsert.h"

using namespace std;

SessionPool* SessionPool::instance = 0;
string SessionPool::credentials = "";
boost::mutex SessionPool::mutex;

#define SOFTWARE_NAME "ECHOES Alert - Rsyslog Parser"
#define SOFTWARE_VERSION "0.1.0"

/*
 * 
 */
int main(int argc, char** argv) {
    int res = EXIT_FAILURE;

    logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << SOFTWARE_NAME << "\" swVersion=\"" << SOFTWARE_VERSION << "\"] (re)start";

    // Loading conf
    Conf conf;
    logger.setType(conf.getCriticity());
    if (conf.getDBPort() != 0)
    {
        string input = "";
        // Temporary(FPO): to stop regulary the parser to clear the memory
        unsigned short i = 0;

        // Setting the session
        Session *session = new Session(conf.getSessConnectParams());

        while (!getline(cin, input).eof())
        {
            if (input.compare(""))
            {
                // Temporary(FPO): to stop regulary the parser to clear the memory
                if (++i > 1000)
                {
                    logger.entry("debug") << "[Main] Delete session + new Session";
                    i = 0;
                    delete session;
                    session = new Session(conf.getSessConnectParams());
                }

                // Processing the Syslog Insertion and detection Structured Data
                SyslogInsert syslogInsert(input, *session);

                StructuredData sd(syslogInsert.getSD(), syslogInsert.getSLOWtDBOPtr(), *session);
            }
            else
                logger.entry("warning") << "[Main] Input is empty";
        }
        
        delete session;
        session = NULL;

        res = EXIT_SUCCESS;
    }
    else
        logger.entry("fatal") << "[Main] The database port mustn't be 0";

    logger.entry("info") << "[origin enterpriseId=\"40311\" software=\"" << SOFTWARE_NAME << "\" swVersion=\"" << SOFTWARE_VERSION << "\"] stop";

    return res;
}

