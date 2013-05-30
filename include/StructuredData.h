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

#include <tools/Enums.h>
#include <tools/SessionPool.h>

#include "SDElement.h"
#include "SDElementProp.h"
#include "SDElementRes.h"

typedef boost::shared_ptr<SDElementRes> SDElementResPtr;

class StructuredData {
    public:
        StructuredData(const std::string &content, const long long &syslogID, Session &session);
        StructuredData(const StructuredData& orig);
        virtual ~StructuredData();

        std::string getContent() const;
        std::vector<SDElementResPtr> getSDElementsResPtr() const;
        SDElementProp* getSDElementPropPtr() const;

    private:
        std::string _content;
        SDElementProp *_sdElementPropPtr;
        std::vector<SDElementResPtr> _sdElementsResPtr;

        void setContent(std::string content);
        void splitSDElements(const long long &syslogID, Session &session);
        void setSDElementsResPtr(std::vector<SDElementResPtr> _sdElementsResPtr);
        void addSDElementResPtr(SDElementRes *sdElementResPtr);
        void setSDElementPropPtr(SDElementProp *sdElementProp);
        void createIVAs(const long long &syslogID, Session &session);
};

#endif	/* StructuredData_H */

