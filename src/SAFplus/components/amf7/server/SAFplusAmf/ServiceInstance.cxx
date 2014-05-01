/* 
 * File ServiceInstance.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "AssignmentState.hxx"
#include "StandbyWeight.hxx"
#include "StandbyWeight.hxx"
#include "StandbyAssignments.hxx"
#include "clMgtList.hxx"
#include "MgtFactory.hxx"
#include "ActiveAssignments.hxx"
#include "AdministrativeState.hxx"
#include "ActiveWeight.hxx"
#include <string>
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "StandbyAssignments.hxx"
#include <vector>
#include "ActiveAssignments.hxx"
#include "ActiveWeight.hxx"
#include "ServiceInstance.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    REGISTERIMPL(ServiceInstance, /SAFplusAmf/ServiceInstance)

    ServiceInstance::ServiceInstance(): ClMgtObject("ServiceInstance"), name("name"), id("id"), adminState("adminState"), assignmentState("assignmentState"), rank("rank"), activeWeightList("activeWeight"), standbyWeightList("standbyWeight")
    {
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&assignmentState, "assignmentState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&activeWeightList, "activeWeight");
        this->addChildObject(&standbyWeightList, "standbyWeight");
        this->addKey("name");
    };

    ServiceInstance::ServiceInstance(std::string nameValue): ClMgtObject("ServiceInstance"), name("name"), id("id"), adminState("adminState"), assignmentState("assignmentState"), rank("rank"), activeWeightList("activeWeight"), standbyWeightList("standbyWeight")
    {
        this->name.Value =  nameValue;
        this->addKey("name");
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&assignmentState, "assignmentState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&activeWeightList, "activeWeight");
        this->addChildObject(&standbyWeightList, "standbyWeight");
    };

    std::vector<std::string> ServiceInstance::getKeys()
    {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* ServiceInstance::getChildNames()
    {
        std::string childNames[] = { "name", "id", "adminState", "assignmentState", "rank", "activeWeight", "standbyWeight", "activeAssignments", "standbyAssignments" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/name
     */
    std::string ServiceInstance::getName()
    {
        return this->name.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/name
     */
    void ServiceInstance::setName(std::string nameValue)
    {
        this->name.Value = nameValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/id
     */
    unsigned short int ServiceInstance::getId()
    {
        return this->id.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/id
     */
    void ServiceInstance::setId(unsigned short int idValue)
    {
        this->id.Value = idValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/adminState
     */
    SAFplusAmf::AdministrativeState ServiceInstance::getAdminState()
    {
        return this->adminState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/adminState
     */
    void ServiceInstance::setAdminState(SAFplusAmf::AdministrativeState adminStateValue)
    {
        this->adminState.Value = adminStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/assignmentState
     */
    SAFplusAmf::AssignmentState ServiceInstance::getAssignmentState()
    {
        return this->assignmentState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/assignmentState
     */
    void ServiceInstance::setAssignmentState(SAFplusAmf::AssignmentState assignmentStateValue)
    {
        this->assignmentState.Value = assignmentStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/rank
     */
    unsigned int ServiceInstance::getRank()
    {
        return this->rank.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/rank
     */
    void ServiceInstance::setRank(unsigned int rankValue)
    {
        this->rank.Value = rankValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeWeight
     */
    SAFplusAmf::ActiveWeight* ServiceInstance::getActiveWeight(std::string resourceValue)
    {
        for (unsigned int i = 0; i < this->activeWeightList.getEntrySize(); i++)
        {
            ActiveWeight* childObject = (ActiveWeight*)this->activeWeightList.getEntry(i);
            if (childObject->getResource() == resourceValue)
            {
                return childObject;
            }
        }
        return NULL;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeWeight
     */
    void ServiceInstance::addActiveWeight(SAFplusAmf::ActiveWeight *activeWeightValue)
    {
        this->activeWeightList.addEntry(activeWeightValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight
     */
    SAFplusAmf::StandbyWeight* ServiceInstance::getStandbyWeight(std::string resourceValue)
    {
        for (unsigned int i = 0; i < this->standbyWeightList.getEntrySize(); i++)
        {
            StandbyWeight* childObject = (StandbyWeight*)this->standbyWeightList.getEntry(i);
            if (childObject->getResource() == resourceValue)
            {
                return childObject;
            }
        }
        return NULL;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyWeight
     */
    void ServiceInstance::addStandbyWeight(SAFplusAmf::StandbyWeight *standbyWeightValue)
    {
        this->standbyWeightList.addEntry(standbyWeightValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeAssignments
     */
    SAFplusAmf::ActiveAssignments* ServiceInstance::getActiveAssignments()
    {
        return (ActiveAssignments*)this->getChildObject("activeAssignments");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/activeAssignments
     */
    void ServiceInstance::addActiveAssignments(SAFplusAmf::ActiveAssignments *activeAssignmentsValue)
    {
        this->addChildObject(activeAssignmentsValue, "activeAssignments");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyAssignments
     */
    SAFplusAmf::StandbyAssignments* ServiceInstance::getStandbyAssignments()
    {
        return (StandbyAssignments*)this->getChildObject("standbyAssignments");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceInstance/standbyAssignments
     */
    void ServiceInstance::addStandbyAssignments(SAFplusAmf::StandbyAssignments *standbyAssignmentsValue)
    {
        this->addChildObject(standbyAssignmentsValue, "standbyAssignments");
    };

    ServiceInstance::~ServiceInstance()
    {
    };

}
/* namespace SAFplusAmf */
