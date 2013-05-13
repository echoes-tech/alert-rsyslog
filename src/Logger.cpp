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
    addField("type", false);
    addField("message", false);
#ifdef NDEBUG
   setFile("/var/log/echoes-alert/parser.log");
#endif
}

Logger::~Logger()
{
}

Wt::WLogEntry Logger::entry(const string& type) const
{
    return Wt::WLogger::entry(type) << timestamp << sep << type << sep;
}

void Logger::setType(unsigned short type)
{
    switch (type)
    {
        case DEBUG:
            logger.configure("*");
            break;
        case INFO:
            logger.configure("* -debug");
                break;
        case WARNING:
            logger.configure("* -debug -info");
            break;
        case SECURE:
            logger.configure("* -debug -info -warning");
            break;
        case ERROR:
            logger.configure("* -debug -info -warning -secure");
            break;
        case FATAL:
            logger.configure("* -debug -info -warning -secure -error");
            break;
        default:
            logger.configure("* -debug");
            break;            
      }

    return;
}

