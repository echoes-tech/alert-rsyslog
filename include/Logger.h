/**
 * @file Logger.h
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
