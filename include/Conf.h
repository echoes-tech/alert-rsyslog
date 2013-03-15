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

#include <Wt/WLogger>

class Conf {
    public:
        Conf();
        Conf(const Conf& orig);
        std::string getDBHost() const;
        unsigned getDBPort() const;
        std::string getDBName() const;
        std::string getDBUser() const;
        std::string getDBPassword() const;
        virtual ~Conf();

    protected:
        std::string _dBhost, _dBname, _dBuser, _dBpassword;
        unsigned _dBport;

        void setDBport(unsigned _dBport);
        void setDBpassword(std::string _dBpassword);
        void setDBuser(std::string _dBuser);
        void setDBname(std::string _dBname);
        void setDBhost(std::string _dBhost);
};

#endif	/* CONF_H */

