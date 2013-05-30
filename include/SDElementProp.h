/* 
 * Header of SD-Element Propertie Parser
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

#ifndef SDELEMENTPROP_H
#define	SDELEMENTPROP_H

#include "SDElement.h"


class SDElementProp : public SDElement
{
    public:
        SDElementProp(const SDElement& sdElement, const long long &syslogID, Session &session);
        SDElementProp(const SDElementProp& orig);
        std::string getToken() const;
        bool isValidToken(Session &session) const;
        unsigned getProbeID() const;
        unsigned getVersion() const;
        Wt::Dbo::ptr<Probe> getProbeWtDBOPtr() const;
        virtual ~SDElementProp();

    private:
        unsigned _probeID, _version;
        std::string _token;
        Wt::Dbo::ptr<Probe> _probeWtDBOPtr;

        void detectPropKeys(Session &session);
        void setToken(std::string token);
        void setProbeID(unsigned probeID);
        void setVersion(unsigned version);
        void findProbeWtDBOPtr(Session &session, unsigned probeID);
        void setProbeWtDBOPtr(Wt::Dbo::ptr<Probe>  probeWtDBOPtr);
        void updateSyslog(long long syslogID, Session &session);
};

#endif	/* SDELEMENTPROP_H */

