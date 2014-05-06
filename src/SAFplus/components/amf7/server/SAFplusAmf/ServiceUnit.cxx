/* 
 * File ServiceUnit.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "RestartCount.hxx"
#include "Node.hxx"
#include <string>
#include "NumActiveServiceInstances.hxx"
#include "RestartCount.hxx"
#include "Component.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "NumStandbyServiceInstances.hxx"
#include "ReadinessState.hxx"
#include "NumActiveServiceInstances.hxx"
#include "clMgtProv.hxx"
#include "ServiceInstance.hxx"
#include "HighAvailabilityReadinessState.hxx"
#include "ServiceGroup.hxx"
#include <vector>
#include "HighAvailabilityState.hxx"
#include "PresenceState.hxx"
#include "EntityId.hxx"
#include "NumStandbyServiceInstances.hxx"
#include "clMgtProvList.hxx"
#include "ServiceUnit.hxx"


namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    MGT_REGISTER_IMPL(ServiceUnit, /SAFplusAmf/ServiceUnit)

    ServiceUnit::ServiceUnit(): name("name"), id("id"), adminState("adminState"), rank("rank"), failover("failover"), preinstantiable("preinstantiable"), saAmfSUHostNodeOrNodeGroup("saAmfSUHostNodeOrNodeGroup"), presenceState("presenceState"), readinessState("readinessState"), haReadinessState("haReadinessState"), haState("haState"), operState("operState"), assignedServiceInstances("assignedServiceInstances"), components("components"), node("node"), serviceGroup("serviceGroup")
    {
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&failover, "failover");
        this->addChildObject(&preinstantiable, "preinstantiable");
        this->addChildObject(&saAmfSUHostNodeOrNodeGroup, "saAmfSUHostNodeOrNodeGroup");
        this->addChildObject(&presenceState, "presenceState");
        this->addChildObject(&readinessState, "readinessState");
        this->addChildObject(&haReadinessState, "haReadinessState");
        this->addChildObject(&haState, "haState");
        this->addChildObject(&operState, "operState");
        this->addChildObject(&assignedServiceInstances, "assignedServiceInstances");
        this->addChildObject(&components, "components");
        this->addChildObject(&node, "node");
        this->addChildObject(&serviceGroup, "serviceGroup");
        this->addKey("name");
    };

    ServiceUnit::ServiceUnit(std::string nameValue): name("name"), id("id"), adminState("adminState"), rank("rank"), failover("failover"), preinstantiable("preinstantiable"), saAmfSUHostNodeOrNodeGroup("saAmfSUHostNodeOrNodeGroup"), presenceState("presenceState"), readinessState("readinessState"), haReadinessState("haReadinessState"), haState("haState"), operState("operState"), assignedServiceInstances("assignedServiceInstances"), components("components"), node("node"), serviceGroup("serviceGroup")
    {
        this->name.Value =  nameValue;
        this->addKey("name");
        this->addChildObject(&name, "name");
        this->addChildObject(&id, "id");
        this->addChildObject(&adminState, "adminState");
        this->addChildObject(&rank, "rank");
        this->addChildObject(&failover, "failover");
        this->addChildObject(&preinstantiable, "preinstantiable");
        this->addChildObject(&saAmfSUHostNodeOrNodeGroup, "saAmfSUHostNodeOrNodeGroup");
        this->addChildObject(&presenceState, "presenceState");
        this->addChildObject(&readinessState, "readinessState");
        this->addChildObject(&haReadinessState, "haReadinessState");
        this->addChildObject(&haState, "haState");
        this->addChildObject(&operState, "operState");
        this->addChildObject(&assignedServiceInstances, "assignedServiceInstances");
        this->addChildObject(&components, "components");
        this->addChildObject(&node, "node");
        this->addChildObject(&serviceGroup, "serviceGroup");
    };

    std::vector<std::string> ServiceUnit::getKeys()
    {
        std::string keyNames[] = { "name" };
        return std::vector<std::string> (keyNames, keyNames + sizeof(keyNames) / sizeof(keyNames[0]));
    };

    std::vector<std::string>* ServiceUnit::getChildNames()
    {
        std::string childNames[] = { "name", "id", "adminState", "rank", "failover", "preinstantiable", "saAmfSUHostNodeOrNodeGroup", "presenceState", "readinessState", "haReadinessState", "haState", "operState", "assignedServiceInstances", "numActiveServiceInstances", "numStandbyServiceInstances", "restartCount", "components", "node", "serviceGroup" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/name
     */
    std::string ServiceUnit::getName()
    {
        return this->name.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/name
     */
    void ServiceUnit::setName(std::string nameValue)
    {
        this->name.Value = nameValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/id
     */
    unsigned short int ServiceUnit::getId()
    {
        return this->id.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/id
     */
    void ServiceUnit::setId(unsigned short int idValue)
    {
        this->id.Value = idValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/adminState
     */
    SAFplusAmf::AdministrativeState ServiceUnit::getAdminState()
    {
        return this->adminState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/adminState
     */
    void ServiceUnit::setAdminState(SAFplusAmf::AdministrativeState adminStateValue)
    {
        this->adminState.Value = adminStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/rank
     */
    unsigned int ServiceUnit::getRank()
    {
        return this->rank.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/rank
     */
    void ServiceUnit::setRank(unsigned int rankValue)
    {
        this->rank.Value = rankValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/failover
     */
    bool ServiceUnit::getFailover()
    {
        return this->failover.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/failover
     */
    void ServiceUnit::setFailover(bool failoverValue)
    {
        this->failover.Value = failoverValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/preinstantiable
     */
    bool ServiceUnit::getPreinstantiable()
    {
        return this->preinstantiable.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/preinstantiable
     */
    void ServiceUnit::setPreinstantiable(bool preinstantiableValue)
    {
        this->preinstantiable.Value = preinstantiableValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
     */
    std::string ServiceUnit::getSaAmfSUHostNodeOrNodeGroup()
    {
        return this->saAmfSUHostNodeOrNodeGroup.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
     */
    void ServiceUnit::setSaAmfSUHostNodeOrNodeGroup(std::string saAmfSUHostNodeOrNodeGroupValue)
    {
        this->saAmfSUHostNodeOrNodeGroup.Value = saAmfSUHostNodeOrNodeGroupValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/presenceState
     */
    SAFplusAmf::PresenceState ServiceUnit::getPresenceState()
    {
        return this->presenceState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/presenceState
     */
    void ServiceUnit::setPresenceState(SAFplusAmf::PresenceState presenceStateValue)
    {
        this->presenceState.Value = presenceStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/readinessState
     */
    SAFplusAmf::ReadinessState ServiceUnit::getReadinessState()
    {
        return this->readinessState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/readinessState
     */
    void ServiceUnit::setReadinessState(SAFplusAmf::ReadinessState readinessStateValue)
    {
        this->readinessState.Value = readinessStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
     */
    SAFplusAmf::HighAvailabilityReadinessState ServiceUnit::getHaReadinessState()
    {
        return this->haReadinessState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
     */
    void ServiceUnit::setHaReadinessState(SAFplusAmf::HighAvailabilityReadinessState haReadinessStateValue)
    {
        this->haReadinessState.Value = haReadinessStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haState
     */
    SAFplusAmf::HighAvailabilityState ServiceUnit::getHaState()
    {
        return this->haState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/haState
     */
    void ServiceUnit::setHaState(SAFplusAmf::HighAvailabilityState haStateValue)
    {
        this->haState.Value = haStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/operState
     */
    bool ServiceUnit::getOperState()
    {
        return this->operState.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/operState
     */
    void ServiceUnit::setOperState(bool operStateValue)
    {
        this->operState.Value = operStateValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
     */
    std::vector<SAFplusAmf::ServiceInstance*> ServiceUnit::getAssignedServiceInstances()
    {
        return this->assignedServiceInstances.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
     */
    void ServiceUnit::setAssignedServiceInstances(SAFplusAmf::ServiceInstance* assignedServiceInstancesValue)
    {
        this->assignedServiceInstances.Value.push_back(assignedServiceInstancesValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/components
     */
    std::vector<SAFplusAmf::Component*> ServiceUnit::getComponents()
    {
        return this->components.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/components
     */
    void ServiceUnit::setComponents(SAFplusAmf::Component* componentsValue)
    {
        this->components.Value.push_back(componentsValue);
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/node
     */
    SAFplusAmf::Node* ServiceUnit::getNode()
    {
        return this->node.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/node
     */
    void ServiceUnit::setNode(SAFplusAmf::Node* nodeValue)
    {
        this->node.Value = nodeValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/serviceGroup
     */
    SAFplusAmf::ServiceGroup* ServiceUnit::getServiceGroup()
    {
        return this->serviceGroup.Value;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/serviceGroup
     */
    void ServiceUnit::setServiceGroup(SAFplusAmf::ServiceGroup* serviceGroupValue)
    {
        this->serviceGroup.Value = serviceGroupValue;
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/numActiveServiceInstances
     */
    SAFplusAmf::NumActiveServiceInstances* ServiceUnit::getNumActiveServiceInstances()
    {
        return (NumActiveServiceInstances*)this->getChildObject("numActiveServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/numActiveServiceInstances
     */
    void ServiceUnit::addNumActiveServiceInstances(SAFplusAmf::NumActiveServiceInstances *numActiveServiceInstancesValue)
    {
        this->addChildObject(numActiveServiceInstancesValue, "numActiveServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/numStandbyServiceInstances
     */
    SAFplusAmf::NumStandbyServiceInstances* ServiceUnit::getNumStandbyServiceInstances()
    {
        return (NumStandbyServiceInstances*)this->getChildObject("numStandbyServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/numStandbyServiceInstances
     */
    void ServiceUnit::addNumStandbyServiceInstances(SAFplusAmf::NumStandbyServiceInstances *numStandbyServiceInstancesValue)
    {
        this->addChildObject(numStandbyServiceInstancesValue, "numStandbyServiceInstances");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/restartCount
     */
    SAFplusAmf::RestartCount* ServiceUnit::getRestartCount()
    {
        return (RestartCount*)this->getChildObject("restartCount");
    };

    /*
     * XPATH: /SAFplusAmf/ServiceUnit/restartCount
     */
    void ServiceUnit::addRestartCount(SAFplusAmf::RestartCount *restartCountValue)
    {
        this->addChildObject(restartCountValue, "restartCount");
    };

    ServiceUnit::~ServiceUnit()
    {
    };

}
/* namespace SAFplusAmf */
