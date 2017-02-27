/**
 * @file StructuredData.h
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

#ifndef StructuredData_H
#define	StructuredData_H

#include <tools/Enums.h>
#include <tools/Session.h>

#include "SDElement.h"
#include "SDElementProp.h"
#include "SDElementRes.h"

class StructuredData {
    public:
        StructuredData(const std::string &content, Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
        StructuredData(const StructuredData& orig);
        virtual ~StructuredData();

        std::string getContent() const;
        std::vector<SDElementRes> getSDElementsRes() const;
        SDElementProp getSDElementProp() const;

    private:
        std::string _content;
        boost::optional<SDElementProp> _sdElementProp;
        std::vector<SDElementRes> _sdElementsRes;

        void setContent(std::string content);
        void splitSDElements(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
        void setSDElementsRes(std::vector<SDElementRes> _sdElementsRes);
        void addSDElementRes(const SDElementRes &sdElementRes);
        void setSDElementProp(SDElementProp sdElementProp);
        void createIVAs(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
};

#endif	/* StructuredData_H */
