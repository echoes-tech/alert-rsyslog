/* 
 * Syslog Insertion
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

#include "SyslogInsert.h"

using namespace std;

SyslogInsert::SyslogInsert(const string &content, Session &session)
{
    // Retrieve Syslog Insertion given by rsyslog
    setContent(content);
    setSD("");

    if(_content.compare(""))
    {
        if(detectSD())
        {
            sqlInsert(session);
        }
    }
    else
        logger.entry("error") << "[SyslogInsert] Content is empty";
}

SyslogInsert::SyslogInsert(const SyslogInsert& orig)
{
    setContent(orig.getContent());
    setSD(orig.getSD());
    setID(orig.getID());
}

SyslogInsert::~SyslogInsert()
{
}

void SyslogInsert::setContent(string content)
{
    _content = content;

    return;
}

string SyslogInsert::getContent() const
{
    return _content;
}

bool SyslogInsert::detectSD()
{
    bool res = false;
    if(_content.compare(""))
    {
        // TODO: renforcer la regex en détectant l'ensemble de l'insertion
        boost::regex e(".*', '(\\[.+\\])', '.*");
        boost::smatch what;

        if (boost::regex_match(_content, what, e, boost::match_extra))
        {
            if (what.size() == 2) {
                setSD(what[1]);
                res = true;
            }
            else
            {
                logger.entry("error") << "[SyslogInsert] Bad number of Structured Data";
            }
        }
        else
        {
            logger.entry("error") << "[SyslogInsert] No Structured Data found";
        }
    }
    else
    {
        logger.entry("error") << "[SyslogInsert] No Structured Data is set";
    }

    return res;
}

void SyslogInsert::setSD(string sd) {
    _sd = sd;

    return;
}

string SyslogInsert::getSD() const {
    return _sd;
}

void SyslogInsert::setID(long long id) {
    _id = id;

    return;
}

long long SyslogInsert::getID() const {
    return _id;
}

void SyslogInsert::sqlInsert(Session &session)
{
    try
    {
        Wt::Dbo::Transaction transaction(session);
        
        session.execute("INSERT INTO \"T_SYSLOG_SLO\"\n"
"  (\n"
"    version,\n"
"    \"SLO_APP_NAME\",\n"
"    \"SLO_HOSTNAME\",\n"
"    \"SLO_SD\",\n"
"    \"SLO_RCPT_DATE\",\n"
"    \"SLO_SENT_DATE\",\n"
"    \"SLO_PRI\",\n"
"    \"SLO_MSG_ID\",\n"
"    \"SLO_PROC_ID\",\n"
"    \"SLO_STATE\"\n"
"  ) values (\n"
            + _content +
"  ) RETURNING \"SLO_ID\";");
        setID(session.query<long long>("select currval('\"T_SYSLOG_SLO_SLO_ID_seq\"')"));

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[SyslogInsert] " << e.what();
    }
    
    return;
}

