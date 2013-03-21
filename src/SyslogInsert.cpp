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

SyslogInsert::SyslogInsert(const string &content, Session *session) {
    // Retrieve Syslog Insertion given by rsyslog
    setContent(content);

    if(_content.compare(""))
    {
        detectSD();
        sqlInsert(session);
    }
    else
        Wt::log("error") << "[SyslogInsert] Content is empty";
}

SyslogInsert::SyslogInsert(const SyslogInsert& orig) {
    setContent(orig.getContent());
    setSD(orig.getSD());
    setID(orig.getID());
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

void SyslogInsert::detectSD()
{
    if(_content.compare(""))
    {
        // TODO: renforcer la regex en détectant l'ensemble de l'insertion
        boost::regex e(".*', '(\\[.+\\])', '.*");
        boost::smatch what;

        if (boost::regex_match(_content, what, e, boost::match_extra))
        {
            if (what.size() == 2) {
                setSD(what[1]);
            }
            else
            {
                Wt::log("error") << "[SyslogInsert] Bad number of Structured Data";
            }
        }
        else
        {
            Wt::log("error") << "[SyslogInsert] No Structured Data found";
        }
    }
    else
    {
        Wt::log("error") << "[SyslogInsert] No Structured Data is set";
    }

    return;
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

void SyslogInsert::sqlInsert(Session *session)
{   
    try
    {
        Wt::Dbo::Transaction transaction(*session);
        
        session->execute(_content);
        setID(session->query<int>("select currval('\"T_SYSLOG_SLO_SLO_ID_seq\"')"));

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        Wt::log("error") << "[SyslogInsert] " << e.what();
    }
    
    return;
}

SyslogInsert::~SyslogInsert() {
}

