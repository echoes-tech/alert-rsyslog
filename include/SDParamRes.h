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
        long long getIDPlugin() const;
        long long getIDAsset() const;
        long long getIDSource() const;
        long long getIDSearch() const;
        unsigned getValueNum() const;        
        unsigned getLotNumber() const;
        unsigned getLineNumber() const;
        virtual ~SDParamRes();

    private:
        long long _idPlugin, _idAsset, _idSource, _idSearch;
        unsigned _valueNum, _lotNumber, _lineNumber;

        void setIDPlugin(long long _idPlugin);
        void setIDAsset(long long _idAsset);
        void setIDSource(long long _idSource);
        void setIDSearch(long long _idSearch);
        void setValueNum(unsigned _valueNum);
        void setLotNumber(unsigned _lotNumber);
        void setLineNumber(unsigned _lineNumber);
};

#endif	/* SDPARAMRES_H */

