/**
 * @file Conf.h
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

#ifndef CONF_H
#define	CONF_H

#include <boost/config.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "Logger.h"

class Conf {
    public:
        Conf();
        Conf(const Conf& orig);
        virtual ~Conf();

        std::string getDBHost() const;
        unsigned getDBPort() const;
        std::string getDBName() const;
        std::string getDBUser() const;
        std::string getDBPassword() const;
        std::string getSessConnectParams() const;
        unsigned short getCriticity() const;

    protected:
        std::string _dbHost, _dbName, _dbUser, _dbPassword, _sessConnectParams;
        unsigned _dbPort;
        unsigned short _criticity;

        void setDBport(unsigned dbPort);
        void setDBpassword(std::string dbPassword);
        void setDBuser(std::string dbUser);
        void setDBname(std::string dbName);
        void setDBhost(std::string dbHost);
        void setSessConnectParams
        (
                std::string dbHost,
                unsigned dbPport,
                std::string dbName,
                std::string dbUser,
                std::string dbPassword
        );
        void setCriticity(unsigned short criticity);
};

#endif	/* CONF_H */
