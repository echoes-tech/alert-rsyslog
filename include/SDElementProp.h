/* 
 * Header of SD-Element Propertie Parser
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

#ifndef SDELEMENTPROP_H
#define	SDELEMENTPROP_H

#include "SDElement.h"


class SDElementProp : public SDElement
{
    public:
        SDElementProp(SDElement& sdElement);
        SDElementProp(const SDElementProp& orig);
        virtual ~SDElementProp();
        std::string getToken() const;
        unsigned getProbeVersion() const;

    private:
        unsigned _probeVersion;
        std::string _token;

        void detectPropKeys();
        void setToken(std::string _token);
        void setProbeVersion(unsigned _probeVersion);
};

#endif	/* SDELEMENTPROP_H */

