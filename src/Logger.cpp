/* 
 * Parser Logger
 * @author ECHOES Technologies (FPO)
 * @date 25/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "Logger.h"

using namespace std;

Logger logger;

Logger::Logger() : Wt::WLogger()
{
    addField("datetime", false);
    addField("message", false);
#ifdef NDEBUG
   setFile("/var/log/echoes-alert/parser.log");
#endif
}

Wt::WLogEntry Logger::entry(const string& type) const
{
    return Wt::WLogger::entry(type) << timestamp << sep;
}

Logger::~Logger()
{
}

