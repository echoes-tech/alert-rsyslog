/**
 * @file SyslogInsert.h
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

#ifndef SYSLOGINSERT_H
#define	SYSLOGINSERT_H

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <tools/Session.h>

#include "Logger.h"

class SyslogInsert {
    public:
        SyslogInsert(const std::string &content, Echoes::Dbo::Session &session);
        SyslogInsert(const SyslogInsert& orig);
        virtual ~SyslogInsert();

        std::string getContent() const;
        std::string getSD() const;
        long long getID() const;
        Wt::Dbo::ptr<Echoes::Dbo::Syslog> getSLOWtDBOPtr() const;

    private:
        std::string _content, _sd;
        long long _id;
        Wt::Dbo::ptr<Echoes::Dbo::Syslog> _sloWtDBOPtr;

        void setContent(std::string input);
        /**
         * Detects the Structured-Data on standard input
         * @param Input
         * @return true if SD detected or false if not
         */
        bool detectSD();
        void setSD(std::string _sd);
        void setID(long long id);
        void setSLOWtDBOPtr(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr);
        void sqlInsert(Echoes::Dbo::Session &session);
};

#endif	/* SYSLOGINSERT_H */
