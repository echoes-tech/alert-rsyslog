/**
 * @file SDParamRes.cpp
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

#include "SDParamRes.h"

using namespace std;

SDParamRes::SDParamRes(const SDParam& sdParam) : SDParam(sdParam)
{
    try
    {
        setIdaId(boost::lexical_cast<long long>(_key));
    }
    catch (boost::bad_lexical_cast &)
    {
        logger.entry("error") << "[SDParamRes] All IDs are not the right type on SD-Element Res";
    }
}

SDParamRes::SDParamRes(const SDParamRes& orig) : SDParam(orig)
{
    setIdaId(orig.getIdaId());
}

SDParamRes::~SDParamRes()
{
}

void SDParamRes::setIdaId(long long idaId)
{
    _idaId = idaId;

    return;
}

long long SDParamRes::getIdaId() const
{
    return _idaId;
}
