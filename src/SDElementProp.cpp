/**
 * @file SDElementProp.cpp
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

#include "SDElementProp.h"

using namespace std;

SDElementProp::SDElementProp(const string &content, Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session) : SDElement(content)
{
    detectPropKeys(session);
    updateSyslog(sloWtDBOPtr, session);
}

SDElementProp::SDElementProp(const SDElementProp& orig) : SDElement(orig)
{
    setProbeID(orig.getProbeID());
    setProbeWtDBOPtr(orig.getProbeWtDBOPtr());
    setToken(orig.getToken());
    setVersion(orig.getVersion());
}

SDElementProp::~SDElementProp()
{
}

void SDElementProp::detectPropKeys(Echoes::Dbo::Session &session)
{
    for (unsigned i(0); i < _sdParams.size(); ++i)
    {
        if (!_sdParams[i].getKey().compare("ver"))
        {
            try
            {
                setVersion(boost::lexical_cast<unsigned>(_sdParams[i].getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
                logger.entry("error") << "[SDElementProp] Version is not an unsigned on SD-Element Prop";
            }
        }
        else if (!_sdParams[i].getKey().compare("probe"))
        {
            try
            {
                setProbeID(boost::lexical_cast<long long>(_sdParams[i].getValue()));
                findProbeWtDBOPtr(_probeID, session);
            }
            catch (boost::bad_lexical_cast &)
            {
                logger.entry("error") << "[SDElement] Probe ID is not an unsigned on SD-Element Prop";
            }
        }
        else if (!_sdParams[i].getKey().compare("token"))
        {
            setToken(_sdParams[i].getValue());
        }
    }

    return;
}

void SDElementProp::setToken(string token)
{
    _token = token;

    return;
}

string SDElementProp::getToken() const
{
    return _token;
}

bool SDElementProp::isValidToken(Echoes::Dbo::Session &session) const
{
    bool res = false;

    if(_probeWtDBOPtr)
    {
        try
        {
            Wt::Dbo::Transaction transaction(session);
            if (_token.compare(_probeWtDBOPtr->asset->group->token.toUTF8()))
                logger.entry("error") << "[SDElementProp] Token not matching group token.";
            else
                res = true;
            transaction.commit();
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << "[SDElementProp] " << e.what();
        }
    }
    else
        logger.entry("error") << "[SDElementProp] Probe doesn't exist.";

    return res;
}

void SDElementProp::setVersion(unsigned version)
{
    _version = version;

    return;
}

unsigned SDElementProp::getVersion() const
{
    return _version;
}

void SDElementProp::setProbeID(long long probeID)
{
    _probeID = probeID;

    return;
}

long long SDElementProp::getProbeID() const
{
    return _probeID;
}

void SDElementProp::findProbeWtDBOPtr(const long long probeID, Echoes::Dbo::Session &session)
{
    try
    {
        Wt::Dbo::Transaction transaction(session);
        setProbeWtDBOPtr(session.find<Echoes::Dbo::Probe>().where("\"PRB_ID\" = ?").bind(probeID).limit(1));
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        setProbeWtDBOPtr(Wt::Dbo::ptr<Echoes::Dbo::Probe>());
        logger.entry("error") << "[SDElementProp] " << e.what();
    }

    return;
}

void SDElementProp::setProbeWtDBOPtr(Wt::Dbo::ptr<Echoes::Dbo::Probe> probeWtDBOPtr)
{
    _probeWtDBOPtr = probeWtDBOPtr;
}

Wt::Dbo::ptr<Echoes::Dbo::Probe> SDElementProp::getProbeWtDBOPtr() const
{
    return _probeWtDBOPtr;
}

void SDElementProp::updateSyslog(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session)
{
    try
    {
        Wt::Dbo::Transaction transaction(session);

        if (isValidToken(session))
        {
            sloWtDBOPtr.modify()->version = _version;
            sloWtDBOPtr.modify()->probe = _probeWtDBOPtr;
        }
        else
            sloWtDBOPtr.modify()->state = 3;

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << "[SDElementProp] " << e.what();           
    }
}
