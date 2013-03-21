/* 
 * Parser Configuration
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

#include "Conf.h"

using namespace std;

Conf::Conf()
{
    setDBport(0);
    
    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;
    
    // Load the INI file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
    try
    {
        boost::property_tree::read_ini("etc/rsyslog.d/ea-parser.conf", pt);
        setDBhost(pt.get<string>("database.host"));
        setDBport(pt.get<unsigned>("database.port"));
        setDBname(pt.get<string>("database.name"));
        setDBuser(pt.get<string>("database.user"));
        setDBpassword(pt.get<string>("database.password"));
        
    }
    catch (boost::property_tree::ini_parser_error e)
    {
        Wt::log("error") << "[Conf] " << e.what();
    }

    setSessConnectParams(_dBhost, _dBport, _dBname, _dBuser, _dBpassword);
}

Conf::Conf(const Conf& orig) {
    setDBhost(orig.getDBHost());
    setDBport(orig.getDBPort());
    setDBname(orig.getDBName());
    setDBuser(orig.getDBUser());
    setDBpassword(orig.getDBPassword());
    setSessConnectParams(_dBhost, _dBport, _dBname, _dBuser, _dBpassword);
}

string Conf::getDBHost() const
{
    return _dBhost;
}

void Conf::setDBport(unsigned dBport)
{
    _dBport = dBport;

    return;
}

void Conf::setDBhost(std::string dBhost)
{
    _dBhost = dBhost;

    return;
}

unsigned Conf::getDBPort() const
{
    return _dBport;
}

void Conf::setDBname(std::string dBname)
{
    _dBname = dBname;

    return;
}

string Conf::getDBName() const
{
    return _dBname;
}

void Conf::setDBuser(std::string dBuser)
{
    _dBuser = dBuser;

    return;
}

string Conf::getDBUser() const
{
    return _dBuser;
}

void Conf::setDBpassword(std::string dBpassword)
{
    _dBpassword = dBpassword;

    return;
}

string Conf::getDBPassword() const
{
    return _dBpassword;
}

void Conf::setSessConnectParams
(
        string dBhost,
        unsigned dBport,
        string dBname,
        string dBuser,
        string dBpassword
)
{   
    try
    {
        _sessConnectParams = "hostaddr=" + dBhost +
                             " port=" + boost::lexical_cast<string>(dBport) +
                             " dbname=" + dBname +
                             " user=" + dBuser +
                             " password=" + dBpassword;
    }
    catch (boost::bad_lexical_cast &)
    {
         Wt::log("error") << "[Conf] sdPort is not an unsigned";
    }

    return;
}

string Conf::getSessConnectParams() const
{
    return _sessConnectParams;
}

Conf::~Conf() {
}

