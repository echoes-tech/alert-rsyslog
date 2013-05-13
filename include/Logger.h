/* 
 * Header of Parser Logger
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

#ifndef LOGGER_H
#define	LOGGER_H

#include <Wt/WLogger>

class Logger : public Wt::WLogger {
    public:
        Logger();
        virtual ~Logger();

        Wt::WLogEntry entry(const std::string& type) const;
        void setType(unsigned short severity);

    private:
        enum EType
        {
            DEBUG = 1,
            INFO = 2,
            WARNING = 3,
            SECURE = 4,
            ERROR = 5,
            FATAL = 6
        };
};

extern Logger logger;

#endif	/* LOGGER_H */

