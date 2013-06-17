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
#ifdef NDEBUG
        boost::property_tree::read_ini("/etc/rsyslog.d/etc/ea-parser.conf", pt);
#else
        boost::property_tree::read_ini("conf/ea-parser.conf", pt);
#endif
        setDBhost(pt.get<string>("database.host"));
        setDBport(pt.get<unsigned>("database.port"));
        setDBname(pt.get<string>("database.name"));
        setDBuser(pt.get<string>("database.user"));
        setDBpassword(pt.get<string>("database.password"));
        setCriticity(pt.get<unsigned short>("log.criticity"));
    }
    catch (boost::property_tree::ini_parser_error e)
    {
        logger.entry("error") << "[Conf] " << e.what();
    }

    setSessConnectParams(_dbHost, _dbPort, _dbName, _dbUser, _dbPassword);
}

Conf::Conf(const Conf& orig)
{
    setDBhost(orig.getDBHost());
    setDBport(orig.getDBPort());
    setDBname(orig.getDBName());
    setDBuser(orig.getDBUser());
    setDBpassword(orig.getDBPassword());
    setSessConnectParams(_dbHost, _dbPort, _dbName, _dbUser, _dbPassword);
    setCriticity(orig.getCriticity());
}

Conf::~Conf()
{
}

string Conf::getDBHost() const
{
    return _dbHost;
}

void Conf::setDBport(unsigned dbPort)
{
    _dbPort = dbPort;

    return;
}

void Conf::setDBhost(string dbHost)
{
    _dbHost = dbHost;

    return;
}

unsigned Conf::getDBPort() const
{
    return _dbPort;
}

void Conf::setDBname(string dbName)
{
    _dbName = dbName;

    return;
}

string Conf::getDBName() const
{
    return _dbName;
}

void Conf::setDBuser(string dbUser)
{
    _dbUser = dbUser;

    return;
}

string Conf::getDBUser() const
{
    return _dbUser;
}

void Conf::setDBpassword(string dbPassword)
{
    _dbPassword = dbPassword;

    return;
}

string Conf::getDBPassword() const
{
    return _dbPassword;
}

void Conf::setSessConnectParams
(
        string dbHost,
        unsigned dbPort,
        string dbName,
        string dbUser,
        string dbPassword
)
{
    try
    {
        _sessConnectParams = "hostaddr=" + dbHost +
                             " port=" + boost::lexical_cast<string>(dbPort) +
                             " dbname=" + dbName +
                             " user=" + dbUser +
                             " password=" + dbPassword;
    }
    catch (boost::bad_lexical_cast &)
    {
        logger.entry("error") << "[Conf] Cast from unsigned integer to string is impossible for the database port";
    }

    return;
}

string Conf::getSessConnectParams() const
{
    return _sessConnectParams;
}

void Conf::setCriticity(unsigned short criticity)
{
    _criticity = criticity;
    return;
}

unsigned short Conf::getCriticity() const
{
    return _criticity;
}

