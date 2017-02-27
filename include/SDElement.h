/**
 * @file SDElement.h
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

#ifndef SDELEMENT_H
#define	SDELEMENT_H

#include <tools/Session.h>

#include "SDID.h"
#include "SDParam.h"

class SDElement {
    public:
        SDElement(const std::string &content);
        SDElement(const SDElement& orig);
        virtual ~SDElement();

        std::string getContent() const;
        SDID getSDID() const;
        std::string getSDParamsString() const;
        std::vector<SDParam> getSDParams() const;

    protected:
        std::string _content, _sdParamsString;
        boost::optional<SDID> _sdID;
        std::vector<SDParam> _sdParams;

        void setContent(std::string content);
        void detectSDID();
        void setSDID(SDID sdID);
        void setSDParamsString(std::string sdParamsString);
        void splitSDParams();
        void addSDParam(const SDParam &sdParam);
        void setSDParam(std::vector<SDParam> sdParams);

};

#endif	/* SDELEMENT_H */
