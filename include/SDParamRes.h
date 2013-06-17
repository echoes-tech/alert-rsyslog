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

        long long getIDPlugin() const;
        long long getIDAsset() const;
        long long getIDSource() const;
        long long getIDSearch() const;
        int getValueNum() const;        
        unsigned getLotNumber() const;
        unsigned getLineNumber() const;

    private:
        long long _idPlugin, _idAsset, _idSource, _idSearch;
        int _valueNum;
        unsigned _lotNumber, _lineNumber;

        void setIDPlugin(long long idPlugin);
        void setIDAsset(long long idAsset);
        void setIDSource(long long idSource);
        void setIDSearch(long long idSearch);
        void setValueNum(int valueNum);
        void setLotNumber(unsigned lotNumber);
        void setLineNumber(unsigned lineNumber);
};

#endif	/* SDPARAMRES_H */

