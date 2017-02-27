/**
 * @file main.cpp
 * @author Thomas Saquet, Florent Poinsaut
 * @date 
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Alert - rsyslog is a part of the Alert software
 * Copyright (C) 2013-2017
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 * 
 */

#include "Logger.h"
#include "Conf.h"
#include "StructuredData.h"
#include "SyslogInsert.h"

using namespace std;

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
        Echoes::Dbo::Session *session = new Echoes::Dbo::Session(conf.getSessConnectParams());

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
                    session = new Echoes::Dbo::Session(conf.getSessConnectParams());
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
