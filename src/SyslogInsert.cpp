/**
 * @file SyslogInsert.cpp
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

#include <boost/regex.hpp>
#include "SyslogInsert.h"

using namespace std;

SyslogInsert::SyslogInsert(const string &content, Echoes::Dbo::Session &session)
{
    // Retrieve Syslog Insertion given by rsyslog
    setContent(content);
    setSD("");

    if(_content.compare(""))
    {
        if(detectSD())
            sqlInsert(session);
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
    if (_content.compare(""))
    {
        // TODO(FPO): renforcer la regex en détectant l'ensemble de l'insertion
        boost::regex e(".*', '(\\[.+\\])', '.*");
        boost::smatch what;

        if (boost::regex_match(_content, what, e, boost::match_extra))
        {
            if (what.size() == 2)
            {
                setSD(what[1]);
                res = true;
            }
            else
                logger.entry("error") << "[SyslogInsert] Bad number of Structured Data";
        }
        else
            logger.entry("error") << "[SyslogInsert] No Structured Data found";
    }
    else
        logger.entry("error") << "[SyslogInsert] No Structured Data is set";

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

void SyslogInsert::setSLOWtDBOPtr(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr)
{
    _sloWtDBOPtr = sloWtDBOPtr;
}

Wt::Dbo::ptr<Echoes::Dbo::Syslog> SyslogInsert::getSLOWtDBOPtr() const
{
    return _sloWtDBOPtr;
}

void SyslogInsert::sqlInsert(Echoes::Dbo::Session &session)
{
    logger.entry("debug") << "[SyslogInsert] SLO Insertion";
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

    logger.entry("debug") << "[SyslogInsert] Retrieve SLO Ptr for syslog ID: " << _id;
    try
    {
        Wt::Dbo::Transaction transaction(session);    

        setSLOWtDBOPtr(session.find<Echoes::Dbo::Syslog>().where("\"SLO_ID\" = ?").bind(_id).limit(1));

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[SyslogInsert] " << e.what();
    }
    
    try
    {
        Wt::Dbo::Transaction transaction(session);
        
        boost::smatch probeId;
        boost::regex r(".*probe=([0-9]*).*");
        
        boost::regex_search(_sd, probeId, r);
        logger.entry("debug") << "[SyslogInsert] Retrieve PRB ptr for id: " << probeId[1];
        
        const string queryStr =
            " SELECT prb"
            "   FROM " QUOTE("T_PROBE_PRB") " prb"
            "   WHERE"
            "     " QUOTE(TRIGRAM_PROBE ID) " = " + probeId[1];
        
        Wt::Dbo::Query<Wt::Dbo::ptr<Echoes::Dbo::Probe>> queryRes = session.query<Wt::Dbo::ptr<Echoes::Dbo::Probe>> (queryStr);
        
        Wt::Dbo::ptr<Echoes::Dbo::Probe> prbPtr = queryRes.resultValue();
        
        prbPtr.modify()->lastlog = Wt::WDateTime::currentDateTime();
        
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[SyslogInsert] " << e.what();
    }
    return;
}
