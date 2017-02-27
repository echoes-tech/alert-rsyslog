/**
 * @file SDElementProp.h
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
