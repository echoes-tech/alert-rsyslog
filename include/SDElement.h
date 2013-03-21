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

typedef boost::shared_ptr<SDParam> SDParamPtr;

class SDElement {
    public:
        SDElement(const std::string &content);
        SDElement(const SDElement& orig);
        std::string getContent() const;
        SDID* getSDIDPtr() const;
        std::string getSDParamsString() const;
        std::vector<SDParamPtr> getSDParamsPtr() const;
        virtual ~SDElement();

    protected:
        std::string _content, _sdParamsString;
        SDID *_sdIDPtr;
        std::vector<SDParamPtr> _sdParamsPtr;
        
        void setContent(std::string content);
        void detectSDID();
        void setSDIDPtr(SDID *sdIDPtr);
        void setSDParamsString(std::string sSDParams);
        void splitSDParams();
        void addSDParamPtr(SDParamPtr sdParamPtr);
        void setSDParamPtr(std::vector<SDParamPtr> sdParamsPtr);

};

#endif	/* SDELEMENT_H */

