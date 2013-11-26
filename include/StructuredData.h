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
#include <tools/Session.h>

#include "SDElement.h"
#include "SDElementProp.h"
#include "SDElementRes.h"

class StructuredData {
    public:
        StructuredData(const std::string &content, Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
        StructuredData(const StructuredData& orig);
        virtual ~StructuredData();

        std::string getContent() const;
        std::vector<SDElementRes> getSDElementsRes() const;
        SDElementProp getSDElementProp() const;

    private:
        std::string _content;
        boost::optional<SDElementProp> _sdElementProp;
        std::vector<SDElementRes> _sdElementsRes;

        void setContent(std::string content);
        void splitSDElements(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
        void setSDElementsRes(std::vector<SDElementRes> _sdElementsRes);
        void addSDElementRes(const SDElementRes &sdElementRes);
        void setSDElementProp(SDElementProp sdElementProp);
        void createIVAs(Wt::Dbo::ptr<Echoes::Dbo::Syslog> sloWtDBOPtr, Echoes::Dbo::Session &session);
};

#endif	/* StructuredData_H */

