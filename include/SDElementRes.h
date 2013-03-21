/* 
 * Header of SD-Element Result Parser
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

#ifndef SDELEMENTRES_H
#define	SDELEMENTRES_H

#include "SDElement.h"
#include "SDParamRes.h"

typedef boost::shared_ptr<SDParamRes> SDParamResPtr;

class SDElementRes : public SDElement {
    public:
        SDElementRes(const SDElement& sdElement);
        SDElementRes(const SDElementRes& orig);
        unsigned getOffset() const;
        std::vector<SDParamResPtr> getSDParamsResPtr() const;
        virtual ~SDElementRes();

    private:
        unsigned _offset;
        std::vector<SDParamResPtr> _sdParamsResPtr;

        void detectResKeys();
        void setOffset(unsigned _offset);
        void addSDParamResPtr(SDParamResPtr sdParamResPtr);
        void setSDParamsResPtr(std::vector<SDParamResPtr> sdParamsResPtr);
};

#endif	/* SDELEMENTRES_H */

