/* 
 * File ServiceUnit.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#pragma once
#ifndef SERVICEUNIT_HXX_
#define SERVICEUNIT_HXX_
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

namespace SAFplusAmf
  {

    class ServiceUnit : public EntityId {

        /* Apply MGT object factory */
        MGT_REGISTER(ServiceUnit);

    public:

        /*
         * Unique name of this entity
         */
        SAFplus::ClMgtProv<std::string> name;

        /*
         * Each SAFplus AMF entity gets a unique numerical identifier
         */
        SAFplus::ClMgtProv<unsigned short int> id;

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        SAFplus::ClMgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * Lower rank is instantiated before higher; but rank 0 means 'don't care'.
         */
        SAFplus::ClMgtProv<unsigned int> rank;

        /*
         * TODO
         */
        SAFplus::ClMgtProv<bool> failover;

        /*
         * Can this service unit be instantiated before being assigned active?  True if ALL components are preinstantiable.
         */
        SAFplus::ClMgtProv<bool> preinstantiable;

        /*
         * The service unit can only be instantiated on the node (if a node is specified) or on one of the nodes of the node group (if a node group is configured).
         */
        SAFplus::ClMgtProv<std::string> saAmfSUHostNodeOrNodeGroup;
        SAFplus::ClMgtProv<SAFplusAmf::PresenceState> presenceState;
        SAFplus::ClMgtProv<SAFplusAmf::ReadinessState> readinessState;

        /*
         * This state field covers ALL work assignments...
         */
        SAFplus::ClMgtProv<SAFplusAmf::HighAvailabilityReadinessState> haReadinessState;
        SAFplus::ClMgtProv<SAFplusAmf::HighAvailabilityState> haState;

        /*
         * True is enabled, False is disabled.  To move from False to True a 'repair' action must occur.
         */
        SAFplus::ClMgtProv<bool> operState;
        SAFplus::ClMgtProvList<SAFplusAmf::ServiceInstance*> assignedServiceInstances;
        SAFplus::ClMgtProvList<SAFplusAmf::Component*> components;
        SAFplus::ClMgtProv<SAFplusAmf::Node*> node;
        SAFplus::ClMgtProv<SAFplusAmf::ServiceGroup*> serviceGroup;

    public:
        ServiceUnit();
        ServiceUnit(std::string nameValue);
        std::vector<std::string> getKeys();
        std::vector<std::string>* getChildNames();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/name
         */
        std::string getName();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/name
         */
        void setName(std::string nameValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/id
         */
        unsigned short int getId();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/id
         */
        void setId(unsigned short int idValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/adminState
         */
        SAFplusAmf::AdministrativeState getAdminState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/adminState
         */
        void setAdminState(SAFplusAmf::AdministrativeState adminStateValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/rank
         */
        unsigned int getRank();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/rank
         */
        void setRank(unsigned int rankValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/failover
         */
        bool getFailover();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/failover
         */
        void setFailover(bool failoverValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/preinstantiable
         */
        bool getPreinstantiable();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/preinstantiable
         */
        void setPreinstantiable(bool preinstantiableValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
         */
        std::string getSaAmfSUHostNodeOrNodeGroup();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/saAmfSUHostNodeOrNodeGroup
         */
        void setSaAmfSUHostNodeOrNodeGroup(std::string saAmfSUHostNodeOrNodeGroupValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/presenceState
         */
        SAFplusAmf::PresenceState getPresenceState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/presenceState
         */
        void setPresenceState(SAFplusAmf::PresenceState presenceStateValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/readinessState
         */
        SAFplusAmf::ReadinessState getReadinessState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/readinessState
         */
        void setReadinessState(SAFplusAmf::ReadinessState readinessStateValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
         */
        SAFplusAmf::HighAvailabilityReadinessState getHaReadinessState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haReadinessState
         */
        void setHaReadinessState(SAFplusAmf::HighAvailabilityReadinessState haReadinessStateValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haState
         */
        SAFplusAmf::HighAvailabilityState getHaState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/haState
         */
        void setHaState(SAFplusAmf::HighAvailabilityState haStateValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/operState
         */
        bool getOperState();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/operState
         */
        void setOperState(bool operStateValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
         */
        std::vector<SAFplusAmf::ServiceInstance*> getAssignedServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
         */
        void setAssignedServiceInstances(SAFplusAmf::ServiceInstance* assignedServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/components
         */
        std::vector<SAFplusAmf::Component*> getComponents();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/components
         */
        void setComponents(SAFplusAmf::Component* componentsValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/node
         */
        SAFplusAmf::Node* getNode();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/node
         */
        void setNode(SAFplusAmf::Node* nodeValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/serviceGroup
         */
        SAFplusAmf::ServiceGroup* getServiceGroup();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/serviceGroup
         */
        void setServiceGroup(SAFplusAmf::ServiceGroup* serviceGroupValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numActiveServiceInstances
         */
        SAFplusAmf::NumActiveServiceInstances* getNumActiveServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numActiveServiceInstances
         */
        void addNumActiveServiceInstances(SAFplusAmf::NumActiveServiceInstances *numActiveServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numStandbyServiceInstances
         */
        SAFplusAmf::NumStandbyServiceInstances* getNumStandbyServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/numStandbyServiceInstances
         */
        void addNumStandbyServiceInstances(SAFplusAmf::NumStandbyServiceInstances *numStandbyServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/restartCount
         */
        SAFplusAmf::RestartCount* getRestartCount();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/restartCount
         */
        void addRestartCount(SAFplusAmf::RestartCount *restartCountValue);
        ~ServiceUnit();

    };
}
/* namespace SAFplusAmf */
#endif /* SERVICEUNIT_HXX_ */
