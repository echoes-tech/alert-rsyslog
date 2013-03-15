/* 
 * Header of SD-ID Parser
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

#ifndef SDID_H
#define	SDID_H

#include <Wt/WLogger>

class SDID {
    public:
        SDID(const std::string &name, const unsigned &privateEntrepriseNumber);
        SDID(const SDID& orig);
        std::string getName() const;
        unsigned getPrivateEntrepriseNumber() const;
        virtual ~SDID();

    private:
        std::string _name;
        unsigned _privateEntrepriseNumber;

        void setName(const std::string name);
        void setPrivateEntrepriseNumber(const unsigned privateEntrepriseNumber);
};

#endif	/* SDID_H */

