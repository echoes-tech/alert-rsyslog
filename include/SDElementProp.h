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
        SDElementProp(const std::string &content, Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
        SDElementProp(const SDElementProp& orig);
        virtual ~SDElementProp();

        std::string getToken() const;
        bool isValidToken(Echoes::Dbo::Session &session) const;
        long long getProbeID() const;
        unsigned getVersion() const;
        Wt::Dbo::ptr<Echoes::Dbo::Probe> getProbeWtDBOPtr() const;

    private:
        unsigned _version;
        long long _probeID;
        std::string _token;
        Wt::Dbo::ptr<Echoes::Dbo::Probe> _probeWtDBOPtr;

        void detectPropKeys(Echoes::Dbo::Session &session);
        void setToken(std::string token);
        void setProbeID(long long probeID);
        void setVersion(unsigned version);
        void findProbeWtDBOPtr(const long long probeID, Echoes::Dbo::Session &session);
        void setProbeWtDBOPtr(Wt::Dbo::ptr<Echoes::Dbo::Probe> probeWtDBOPtr);
        void updateSyslog(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
};

#endif	/* SDELEMENTPROP_H */

