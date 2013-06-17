/* 
 * Header of SD-Element Parser
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

#ifndef SDELEMENT_H
#define	SDELEMENT_H

#include <tools/SessionPool.h>

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

