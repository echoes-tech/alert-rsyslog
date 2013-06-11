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

class SDElementRes : public SDElement {
    public:
        SDElementRes(const std::string &content);
        SDElementRes(const SDElementRes& orig);
        virtual ~SDElementRes();

        unsigned getOffset() const;
        std::vector<SDParamRes> getSDParamsRes() const;

    private:
        unsigned _offset;
        std::vector<SDParamRes> _sdParamsRes;

        void detectResKeys();
        void setOffset(unsigned _offset);
        void addSDParamRes(const SDParamRes &sdParamRes);
        void setSDParamsRes(std::vector<SDParamRes> sdParamsRes);
};

#endif	/* SDELEMENTRES_H */

