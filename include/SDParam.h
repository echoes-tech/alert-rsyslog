/* 
 * Header of SD-Param Parser
 * @author ECHOES Technologies (FPO)
 * @date 15/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef SDPARAM_H
#define	SDPARAM_H

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <Wt/Utils>
#include <Wt/WLogger>

class SDParam {
    public:
        SDParam(const std::string &content);
        SDParam(const SDParam& orig);
        std::string getContent() const;
        std::string getKey() const;
        std::string getValue() const;
        virtual ~SDParam();

    protected:
        std::string _content, _key, _value;

        void setContent(std::string content);
        void splitKeyValue();
        void setKey(std::string key);
        void setValue(std::string value);
};

#endif	/* SDPARAM_H */

