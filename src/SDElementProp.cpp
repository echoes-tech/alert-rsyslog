/* 
 * SD-Element Propertie Parser
 * @author ECHOES Technologies (FPO)
 * @date 15/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "SDElementProp.h"

using namespace std;

SDElementProp::SDElementProp(const SDElement& sdElement, const long long &syslogID, Session *session) : SDElement(sdElement)
{
    detectPropKeys(session);
    updateSyslog(syslogID, session);
}

SDElementProp::SDElementProp(const SDElementProp& orig) : SDElement(orig)
{
    setProbeID(orig.getProbeID());
    setProbeWtDBOPtr(orig.getProbeWtDBOPtr());
    setToken(orig.getToken());
    setVersion(orig.getVersion());
}

void SDElementProp::detectPropKeys(Session *session)
{
    for (unsigned i(0); i < _sdParamsPtr.size(); ++i)
    {
        if (boost::equals(_sdParamsPtr[i]->getKey(), "ver"))
        {
            try
            {
                setVersion(boost::lexical_cast<unsigned>(_sdParamsPtr[i]->getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
                logger.entry("error") << "[SDElementProp] Version is not an unsigned on SD-Element Prop";
            }
        }
        else if (boost::equals(_sdParamsPtr[i]->getKey(), "probe"))
        {
            try
            {
                setProbeID(boost::lexical_cast<unsigned>(_sdParamsPtr[i]->getValue()));
                findProbeWtDBOPtr(session, _probeID);
            }
            catch (boost::bad_lexical_cast &)
            {
                logger.entry("error") << "[SDElement] Probe ID is not an unsigned on SD-Element Prop";
            }
        }
        else if (boost::equals(_sdParamsPtr[i]->getKey(), "token"))
        {
            setToken(_sdParamsPtr[i]->getValue());
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

bool SDElementProp::isValidToken(Session *session) const
{
    bool res = false;

    if(_probeWtDBOPtr)
    {
        try
        {   
            Wt::Dbo::Transaction transaction(*session);
            if (_token.compare(_probeWtDBOPtr->organization->token.toUTF8()))
                logger.entry("error") << " [SDElementProp] Token not matching organization token.";
            else
                res = true;
        }
        catch (Wt::Dbo::Exception e)
        {
            logger.entry("error") << " [SDElementProp] " << e.what() ;
        }
    }
    else
        logger.entry("error") << " [SDElementProp] Probe doesn't exist.";

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

void SDElementProp::setProbeID(unsigned probeID)
{
    _probeID = probeID;

    return;
}

unsigned SDElementProp::getProbeID() const
{
    return _probeID;
}

void SDElementProp::findProbeWtDBOPtr(Session *session, unsigned probeID)
{
    try
    {
        Wt::Dbo::Transaction transaction(*session);
        setProbeWtDBOPtr(session->find<Probe>().where("\"PRB_ID\" = ?").bind(boost::lexical_cast<string>(probeID)).limit(1));
        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        setProbeWtDBOPtr(*(new Wt::Dbo::ptr<Probe>()));
        logger.entry("error") << " [SDElementProp] " << e.what();
    }

    return;
}

void SDElementProp::setProbeWtDBOPtr(Wt::Dbo::ptr<Probe> probeWtDBOPtr)
{
    _probeWtDBOPtr = probeWtDBOPtr;
}

Wt::Dbo::ptr<Probe> SDElementProp::getProbeWtDBOPtr() const
{
    return _probeWtDBOPtr;
}

void SDElementProp::updateSyslog(long long syslogID, Session *session)
{
    try 
    {
        Wt::Dbo::Transaction transaction(*session);
        Wt::Dbo::ptr<Syslog> syslogPtr = session->find<Syslog>().where("\"SLO_ID\" = ?").bind(boost::lexical_cast<string>(syslogID)).limit(1);
        
        if(isValidToken(session))
        {
            syslogPtr.modify()->version = _version;
            syslogPtr.modify()->probe = _probeWtDBOPtr;
        }
        else
            syslogPtr.modify()->state = 3;

        transaction.commit();
    }
    catch (Wt::Dbo::Exception e)
    {
        logger.entry("error") << " [SDElementProp] " << e.what();           
    }

}
    
SDElementProp::~SDElementProp()
{
    delete _sdIDPtr;
    _sdIDPtr = NULL;
}

