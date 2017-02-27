/**
 * @file SDID.h
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

#ifndef SDID_H
#define	SDID_H

#include "Logger.h"

class SDID {
    public:
        SDID(const std::string &name, const unsigned &privateEntrepriseNumber);
        SDID(const SDID& orig);
        virtual ~SDID();

        std::string getName() const;
        unsigned getPrivateEntrepriseNumber() const;

    private:
        std::string _name;
        unsigned _privateEntrepriseNumber;

        void setName(std::string name);
        void setPrivateEntrepriseNumber(unsigned privateEntrepriseNumber);
};

#endif	/* SDID_H */
