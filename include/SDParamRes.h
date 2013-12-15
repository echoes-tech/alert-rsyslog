/* 
 * Header of SD-Param Result Parser
 * @author ECHOES Technologies (FPO)
 * @date 20/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef SDPARAMRES_H
#define	SDPARAMRES_H

#include "SDParam.h"

class SDParamRes : public SDParam {
    public:
        SDParamRes(const SDParam& sdParam);
        SDParamRes(const SDParamRes& orig);
        virtual ~SDParamRes();

        long long getIdaId() const;

    private:
        long long _idaId;

        void setIdaId(long long idaId);
};

#endif	/* SDPARAMRES_H */

