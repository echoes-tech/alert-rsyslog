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
        SDElementProp(const std::string &content, Wt::Dbo::ptr<Syslog> sloWtDBOPtr, Session &session);
        SDElementProp(const SDElementProp& orig);
        virtual ~SDElementProp();

        std::string getToken() const;
        bool isValidToken(Session &session) const;
        long long getProbeID() const;
        unsigned getVersion() const;
        Wt::Dbo::ptr<Probe> getProbeWtDBOPtr() const;

    private:
        unsigned _version;
        long long _probeID;
        std::string _token;
        Wt::Dbo::ptr<Probe> _probeWtDBOPtr;

        void detectPropKeys(Session &session);
        void setToken(std::string token);
        void setProbeID(long long probeID);
        void setVersion(unsigned version);
        void findProbeWtDBOPtr(const long long probeID, Session &session);
        void setProbeWtDBOPtr(Wt::Dbo::ptr<Probe> probeWtDBOPtr);
        void updateSyslog(Wt::Dbo::ptr<Syslog> sloWtDBOPtr, Session &session);
};

#endif	/* SDELEMENTPROP_H */

