/**
 * @file SDParam.cpp
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

#include "SDParam.h"

using namespace std;

SDParam::SDParam(const string &content)
{
    setContent(content);
    setKey("");
    setValue("");

    if (_content.compare(""))
        splitKeyValue();
    else
        logger.entry("error") << "[SDParam] Content is empty";
}

SDParam::SDParam(const SDParam& orig)
{
    setContent(orig.getContent());
    setKey(orig.getKey());
    setValue(orig.getValue());
}

SDParam::~SDParam()
{
}

void SDParam::setContent(string content)
{
    _content = content;

    return;
}

string SDParam::getContent() const
{
    return _content;
}

void SDParam::splitKeyValue()
{
    string valueTmp;

    // Example : 22="urlEncode(data)"

    unsigned pos = _content.find_first_of('=');

    setKey(_content.substr(0, pos));

    // Example : "urlEncode(data)"
    valueTmp = _content.substr(pos + 1);

    if (boost::starts_with(valueTmp, "\"") && boost::ends_with(valueTmp, "\"") )
    {
        boost::erase_head(valueTmp, 1);
        boost::erase_tail(valueTmp, 1);
    }

    // Example : urlEncode(data)
    setValue(valueTmp);

    return;
}

void SDParam::setKey(string key)
{
    _key = key;
}

string SDParam::getKey() const
{
    return _key;
}

void SDParam::setValue(string value)
{
    _value = value;
}

std::string SDParam::getValue() const
{
    return _value;
}
