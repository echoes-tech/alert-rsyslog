/* 
 * Header of Syslog Insertion
 * @author ECHOES Technologies (FPO)
 * @date 18/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef SYSLOGINSERT_H
#define	SYSLOGINSERT_H

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <tools/SessionPool.h>

#include "Logger.h"

class SyslogInsert {
    public:
        SyslogInsert(const std::string &content, Session &session);
        SyslogInsert(const SyslogInsert& orig);
        virtual ~SyslogInsert();

        std::string getContent() const;
        std::string getSD() const;
        long long getID() const;

    private:
        std::string _content, _sd;
        long long _id;

        void setContent(std::string input);
        void detectSD();
        void setSD(std::string _sd);
        void setID(long long id);
        void sqlInsert(Session &session);
};

#endif	/* SYSLOGINSERT_H */

