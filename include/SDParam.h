/**
 * @file SDParam.h
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

#ifndef SDPARAM_H
#define	SDPARAM_H

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <Wt/Utils>

#include "Logger.h"

class SDParam {
    public:
        SDParam(const std::string &content);
        SDParam(const SDParam& orig);
        virtual ~SDParam();

        std::string getContent() const;
        std::string getKey() const;
        std::string getValue() const;

    protected:
        std::string _content, _key, _value;

        void setContent(std::string content);
        void splitKeyValue();
        void setKey(std::string key);
        void setValue(std::string value);
};

#endif	/* SDPARAM_H */
