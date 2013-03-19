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

class SDElementRes : public SDElement {
    public:
        SDElementRes(const SDElement& sdElement);
        SDElementRes(const SDElementRes& orig);
        unsigned getOffset() const;
        unsigned getIDPlugin() const;
        unsigned getIDAsset() const;
        unsigned getIDSource() const;
        unsigned getIDSearch() const;
        unsigned getValueNum() const;        
        unsigned getLotNumber() const;
        unsigned getLineNumber() const;
        virtual ~SDElementRes();

    private:
        unsigned _offset, _idPlugin, _idAsset, _idSource, _idSearch, _valueNum, _lotNumber, _lineNumber;

        void detectResKeys();
        void setOffset(unsigned _offset);
        void setIDPlugin(unsigned _idPlugin);
        void setIDAsset(unsigned _idAsset);
        void setIDSource(unsigned _idSource);
        void setIDSearch(unsigned _idSearch);
        void setValueNum(unsigned _valueNum);
        void setLotNumber(unsigned _lotNumber);
        void setLineNumber(unsigned _lineNumber);
};

#endif	/* SDELEMENTRES_H */

