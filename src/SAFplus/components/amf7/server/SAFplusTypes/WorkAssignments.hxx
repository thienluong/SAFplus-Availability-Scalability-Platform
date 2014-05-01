/* 
 * File WorkAssignments.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef WORKASSIGNMENTS_HXX_
#define WORKASSIGNMENTS_HXX_
#include "SAFplusTypesCommon.hxx"

#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "Provisioning.hxx"
#include "Provisioning.hxx"
#include <string>

namespace SAFplusTypes
  {

    class WorkAssignments : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(WorkAssignments);

    public:

        /*
         * SAF Service Instance name
         */
        ClMgtProv<std::string> name;
        ClMgtList provisioningList;

    public:
        WorkAssignments();
        WorkAssignments(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusTypes/application/workAssignments/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusTypes/application/workAssignments/name
         */
        void setName(std::string nameValue);

        /*
         * XPATH: /SAFplusTypes/application/workAssignments/provisioning
         */
        SAFplusTypes::Provisioning* getProvisioning(std::string nameValue);

        /*
         * XPATH: /SAFplusTypes/application/workAssignments/provisioning
         */
        void addProvisioning(SAFplusTypes::Provisioning *provisioningValue);
        ~WorkAssignments();

    };
}
/* namespace SAFplusTypes */
#endif /* WORKASSIGNMENTS_HXX_ */
