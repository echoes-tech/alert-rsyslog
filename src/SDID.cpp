/**
 * @file SDID.cpp
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

#include "SDID.h"

using namespace std;

SDID::SDID(const string &name, const unsigned &privateEntrepriseNumber)
{
    setName(name);
    setPrivateEntrepriseNumber(privateEntrepriseNumber);
}

SDID::SDID(const SDID& orig)
{
    setName(orig.getName());
    setPrivateEntrepriseNumber(orig.getPrivateEntrepriseNumber());
}

SDID::~SDID() {
}

void SDID::setName(string name)
{
    _name = name;
    return;
}

string SDID::getName() const
{
    return _name;
}

void SDID::setPrivateEntrepriseNumber(unsigned privateEntrepriseNumber)
{
    _privateEntrepriseNumber = privateEntrepriseNumber;
    return;
}

unsigned SDID::getPrivateEntrepriseNumber() const
{
    return _privateEntrepriseNumber;
}
