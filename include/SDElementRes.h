/**
 * @file SDElementRes.h
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

#ifndef SDELEMENTRES_H
#define	SDELEMENTRES_H

#include "SDElement.h"
#include "SDParamRes.h"

class SDElementRes : public SDElement {
    public:
        SDElementRes(const std::string &content);
        SDElementRes(const SDElementRes& orig);
        virtual ~SDElementRes();

        unsigned getOffset() const;
        unsigned getLineNumber() const;
        unsigned getLotNumber() const;
        std::vector<SDParamRes> getSDParamsRes() const;

    private:
        unsigned _offset;
        unsigned _lineNumber;
        unsigned _lotNumber;
        std::vector<SDParamRes> _sdParamsRes;

        void detectResKeys();
        void setOffset(unsigned offset);
        void setLineNumber(unsigned lineNumber);
        void setLotNumber(unsigned lotNumber);
        void addSDParamRes(const SDParamRes &sdParamRes);
        void setSDParamsRes(std::vector<SDParamRes> sdParamsRes);
};

#endif	/* SDELEMENTRES_H */
