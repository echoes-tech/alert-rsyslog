/* 
 * Header of StructuredData Parser
 * @author ECHOES Technologies (FPO)
 * @date 14/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef StructuredData_H
#define	StructuredData_H

#include "SDElement.h"

typedef boost::shared_ptr<SDElement> SDElementPtr;

class StructuredData {
    public:
        StructuredData(std::istream &input);
        StructuredData(const StructuredData& orig);
        std::string getContent() const;
        std::vector<SDElementPtr> getSDElementsPtr() const;
        virtual ~StructuredData();

    private:
        std::string _content;
        std::vector<SDElementPtr> _sdElementsPtr;

        void setContent(std::istream& input);
        void setContent(std::string content);
        void splitSDElements();
        void setSDElementsPtr(std::vector<SDElementPtr> _sdElementsPtr);
        void addSDElementPtr(SDElementPtr sdElementPtr);
};

#endif	/* StructuredData_H */

