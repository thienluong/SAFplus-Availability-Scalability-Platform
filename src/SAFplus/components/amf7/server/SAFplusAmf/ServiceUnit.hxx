/* 
 * File ServiceUnit.hxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 

#ifndef SERVICEUNIT_HXX_
#define SERVICEUNIT_HXX_

#include "RestartCount.hxx"
#include "StandbyServiceInstances.hxx"
#include <string>
#include "RestartCount.hxx"
#include "StandbyServiceInstances.hxx"
#include "MgtFactory.hxx"
#include "AdministrativeState.hxx"
#include "ActiveServiceInstances.hxx"
#include "ActiveServiceInstances.hxx"
#include "ReadinessState.hxx"
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "HighAvailabilityReadinessState.hxx"
#include <vector>
#include "HighAvailabilityState.hxx"
#include "PresenceState.hxx"
#include "clMgtProvList.hxx"

namespace SAFplusAmf {

    class ServiceUnit : public ClMgtObject {

        /* Apply MGT object factory */
        REGISTER(ServiceUnit);

    public:

        /*
         * Unique name of this entity
         */
        ClMgtProv<std::string> name;

        /*
         * Each SAFplus AMF entity gets a unique numerical identifier
         */
        ClMgtProv<unsigned short int> id;

        /*
         * Does the operator want this entity to be off, idle, or in service?
         */
        ClMgtProv<SAFplusAmf::AdministrativeState> adminState;

        /*
         * Lower rank is instantiated before higher; but rank 0 means 'don't care'.
         */
        ClMgtProv<unsigned int> rank;

        /*
         * TODO
         */
        ClMgtProv<bool> failover;

        /*
         * Can this service unit be instantiated before being assigned active?  True if ALL components are preinstantiable.
         */
        ClMgtProv<bool> preInstantiable;

        /*
         * The service unit can only be instantiated on the node (if a node is specified) or on one of the nodes of the node group (if a node group is configured).
         */
        ClMgtProv<std::string> saAmfSUHostNodeOrNodeGroup;
        ClMgtProv<SAFplusAmf::PresenceState> presenceState;
        ClMgtProv<SAFplusAmf::ReadinessState> readinessState;

        /*
         * This state field covers ALL work assignments...
         */
        ClMgtProv<SAFplusAmf::HighAvailabilityReadinessState> haReadinessState;
        ClMgtProv<SAFplusAmf::HighAvailabilityState> haState;

        /*
         * True is enabled, False is disabled.  To move from False to True a 'repair' action must occur.
         */
        ClMgtProv<bool> operState;
        ClMgtProvList<std::string> assignedServiceInstances;

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
         * XPATH: /SAFplusAmf/ServiceUnit/preInstantiable
         */
        bool getPreInstantiable();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/preInstantiable
         */
        void setPreInstantiable(bool preInstantiableValue);

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
        std::vector<std::string> getAssignedServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/assignedServiceInstances
         */
        void setAssignedServiceInstances(std::string assignedServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/activeServiceInstances
         */
        SAFplusAmf::ActiveServiceInstances* getActiveServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/activeServiceInstances
         */
        void addActiveServiceInstances(SAFplusAmf::ActiveServiceInstances *activeServiceInstancesValue);

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/standbyServiceInstances
         */
        SAFplusAmf::StandbyServiceInstances* getStandbyServiceInstances();

        /*
         * XPATH: /SAFplusAmf/ServiceUnit/standbyServiceInstances
         */
        void addStandbyServiceInstances(SAFplusAmf::StandbyServiceInstances *standbyServiceInstancesValue);

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
