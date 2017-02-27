/**
 * @file SDElementRes.cpp
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

#include "SDElementRes.h"

using namespace std;

SDElementRes::SDElementRes(const string &content) : SDElement(content)
{
    setOffset(0);
    setLineNumber(0);
    setLotNumber(0);
    detectResKeys();
}

SDElementRes::SDElementRes(const SDElementRes& orig) : SDElement(orig)
{
    setOffset(orig.getOffset());
    setLineNumber(orig.getLineNumber());
    setLotNumber(orig.getLotNumber());
    setSDParamsRes(orig.getSDParamsRes());
}

SDElementRes::~SDElementRes()
{
}

void SDElementRes::detectResKeys()
{
    for (unsigned i(0); i < _sdParams.size(); ++i)
    {
     
        if (!_sdParams[i].getKey().compare("offset"))
        {
            try
            {
                setOffset(boost::lexical_cast<unsigned>(_sdParams[i].getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
               logger.entry("error") << "[SDElementRes] Offset is not an unsigned on SD-Element Res";
            }
        }
        else if (!_sdParams[i].getKey().compare("lotNum"))
        {
            try
            {
                setLotNumber(boost::lexical_cast<unsigned>(_sdParams[i].getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
               logger.entry("error") << "[SDElementRes] lotNumber is not an unsigned on SD-Element Res";
            }
        }
        else if (!_sdParams[i].getKey().compare("lineNum"))
        {
            try
            {
                setLineNumber(boost::lexical_cast<unsigned>(_sdParams[i].getValue()));
            }
            catch (boost::bad_lexical_cast &)
            {
               logger.entry("error") << "[SDElementRes] lineNumber is not an unsigned on SD-Element Res";
            }
        }
        else if (!boost::starts_with(_sdParams[i].getKey(), "res"))
        {
            // 2-1-1-2-1-1
            addSDParamRes(SDParamRes(_sdParams[i]));
        }
    }
    
    return;
}

void SDElementRes::setOffset(unsigned offset)
{
    _offset = offset;

    return;
}

unsigned SDElementRes::getOffset() const
{
    return _offset;
}

void SDElementRes::setLineNumber(unsigned lineNumber)
{
    _lineNumber = lineNumber;

    return;
}

unsigned SDElementRes::getLineNumber() const
{
    return _lineNumber;
}

void SDElementRes::setLotNumber(unsigned lotNumber)
{
    _lotNumber = lotNumber;

    return;
}

unsigned SDElementRes::getLotNumber() const
{
    return _lotNumber;
}

void SDElementRes::setSDParamsRes(vector<SDParamRes> sdParamsRes)
{
    _sdParamsRes = sdParamsRes;

    return;
}


void SDElementRes::addSDParamRes(const SDParamRes &sdParamRes)
{
    _sdParamsRes.push_back(sdParamRes);
    return;
}

vector<SDParamRes> SDElementRes::getSDParamsRes() const
{
    return _sdParamsRes;
}
