/* 
 * Header of Parser Configuration
 * @author ECHOES Technologies (FPO)
 * @date 14/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
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

