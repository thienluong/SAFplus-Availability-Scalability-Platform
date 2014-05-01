/* 
 * File SAFplusAmf.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusAmfCommon.hxx"

#include "clMgtList.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "SaTimeT.hxx"
#include "SAFplusAmf.hxx"

#include "Node.hxx"
#include "ServiceGroup.hxx"
#include "Component.hxx"


using namespace SAFplusTypes;

namespace SAFplusAmf
  {

    /* Apply MGT object factory */
    REGISTERIMPL(SAFplusAmfRoot, /SAFplusAmf)

    SAFplusAmfRoot::SAFplusAmfRoot(): ClMgtObject("SAFplusAmfRoot"), healthCheckPeriod("healthCheckPeriod"), healthCheckMaxSilence("healthCheckMaxSilence"), clusterList("Cluster"), nodeList("Node"), serviceGroupList("ServiceGroup"), componentList("Component"), componentServiceInstanceList("ComponentServiceInstance"), serviceInstanceList("ServiceInstance"), serviceUnitList("ServiceUnit"), applicationList("Application"), entityByNameList("EntityByName"), entityByIdList("EntityById")
    {
        this->addChildObject(&healthCheckPeriod, "healthCheckPeriod");
        this->addChildObject(&healthCheckMaxSilence, "healthCheckMaxSilence");
        this->addChildObject(&clusterList, "Cluster");
        this->addChildObject(&nodeList, "Node");
        this->addChildObject(&serviceGroupList, "ServiceGroup");
        this->addChildObject(&componentList, "Component");
        this->addChildObject(&componentServiceInstanceList, "ComponentServiceInstance");
        this->addChildObject(&serviceInstanceList, "ServiceInstance");
        this->addChildObject(&serviceUnitList, "ServiceUnit");
        this->addChildObject(&applicationList, "Application");
        this->addChildObject(&entityByNameList, "EntityByName");
        this->addChildObject(&entityByIdList, "EntityById");
    };

    std::vector<std::string>* SAFplusAmfRoot::getChildNames()
    {
        std::string childNames[] = { "Cluster", "Node", "ServiceGroup", "Component", "ComponentServiceInstance", "ServiceInstance", "ServiceUnit", "Application", "EntityByName", "EntityById", "healthCheckPeriod", "healthCheckMaxSilence" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckPeriod
     */
    SAFplusTypes::SaTimeT SAFplusAmfRoot::getHealthCheckPeriod()
    {
        return this->healthCheckPeriod.Value;
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckPeriod
     */
    void SAFplusAmfRoot::setHealthCheckPeriod(SAFplusTypes::SaTimeT healthCheckPeriodValue)
    {
        this->healthCheckPeriod.Value = healthCheckPeriodValue;
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckMaxSilence
     */
    SAFplusTypes::SaTimeT SAFplusAmfRoot::getHealthCheckMaxSilence()
    {
        return this->healthCheckMaxSilence.Value;
    };

    /*
     * XPATH: /SAFplusAmf/healthCheckMaxSilence
     */
    void SAFplusAmfRoot::setHealthCheckMaxSilence(SAFplusTypes::SaTimeT healthCheckMaxSilenceValue)
    {
        this->healthCheckMaxSilence.Value = healthCheckMaxSilenceValue;
    };
unsigned short int amfId = 1;

unsigned short int getAmfId()
{
  //GAS TODO: thread safety
  unsigned short int ret = amfId;
  amfId++;
  return ret;
}

Node* createNode(const char* name, const SAFplusAmf::AdministrativeState& adminState, bool autoRepair, bool failFastOnInstantiationFailure, bool failFastOnCleanupFailure)
{
  Node* ret = new Node(name);
  ret->id = getAmfId();
  ret->adminState.Value = adminState;
  ret->autoRepair = autoRepair;
  ret->failFastOnInstantiationFailure = failFastOnInstantiationFailure;
  ret->failFastOnCleanupFailure = failFastOnCleanupFailure;
  return ret;
}


ServiceGroup* createServiceGroup(const char* name, const SAFplusAmf::AdministrativeState& adminState, bool autoRepair, bool autoAdjust,SAFplusTypes::SaTimeT autoAdjustInterval,unsigned int preferredNumActiveServiceUnits,unsigned int preferredNumStandbyServiceUnits,unsigned int preferredNumIdleServiceUnits,unsigned int maxActiveWorkAssignments,unsigned int maxStandbyWorkAssignments )
{
  ServiceGroup* ret = new ServiceGroup(name);
  ret->id                              = getAmfId();
  ret->adminState.Value                = adminState;
  ret->autoRepair                      = autoRepair;
  ret->autoAdjust                      = autoAdjust;
  ret->autoAdjustInterval              = autoAdjustInterval;
  ret->preferredNumActiveServiceUnits  = preferredNumActiveServiceUnits;
  ret->preferredNumStandbyServiceUnits = preferredNumStandbyServiceUnits;
  ret->preferredNumIdleServiceUnits    = preferredNumIdleServiceUnits;
  ret->maxActiveWorkAssignments        = maxActiveWorkAssignments;
  ret->maxStandbyWorkAssignments       = maxStandbyWorkAssignments;
  
  return ret;
}

Component* createComponent(const char* name, SAFplusAmf::CapabilityModel capabilityModel,unsigned int maxActiveAssignments,unsigned int maxStandbyAssignments,std::string safVersion, unsigned int compCategory,const std::string& swBundle,const std::string& env,unsigned int maxInstantInstantiations,unsigned int maxDelayedInstantiations,unsigned int delayBetweenInstantiation,SAFplusAmf::Recovery recovery,bool restartable,const std::string& proxy,const std::string& proxied)
{
  Component* ret = new Component(name);
  ret->id = getAmfId();
  ret->capabilityModel = capabilityModel;
  ret->maxActiveAssignments = maxActiveAssignments;
  ret->maxStandbyAssignments = maxStandbyAssignments;
  ret->safVersion = safVersion;
  ret->compCategory = compCategory;
  ret->swBundle = swBundle;
  // GAS TODO: ClMgtProvList needs code accessors: ret->commandEnvironment = env;
  ret->maxInstantInstantiations = maxInstantInstantiations;
  ret->maxDelayedInstantiations = maxDelayedInstantiations;
  ret->delayBetweenInstantiation = delayBetweenInstantiation;
  ret->recovery = recovery;
  ret->restartable = restartable;
  ret->proxy = proxy;
  // GAS TODO: ClMgtProvList needs code accessors: ret->proxied = proxied;
}

    void SAFplusAmfRoot::load(ClMgtDatabase *db)
    {
#if 1  // For Testing:  By hand initialization:
    SAFplusTypes::SaTimeT st;
    st.Value = 0;
    //SAFplusAmf::AdministrativeState as;
    //as.Value = 2;
    Node* node = createNode("ctrl0",SAFplusAmf::AdministrativeState::on,true,false,false);
    ServiceGroup* sg = createServiceGroup("sg0",SAFplusAmf::AdministrativeState::on,true,false,st,1,1,1,1,1);
    Component* comp = createComponent("c0",SAFplusAmf::CapabilityModel::x_active_or_y_standby,1,1,"B.01.01",1,"testBundle.tgz","TEST_ENV=1\nTEST_ENV2=2",2,2,2000,SAFplusAmf::Recovery::Restart,true,"","");

    nodeList.addEntry(node);
    serviceGroupList.addEntry(sg);
    componentList.addEntry(comp);

#else  // Actually load from DB
#endif
    };

    SAFplusAmfRoot::~SAFplusAmfRoot()
    {
    };

}
/* namespace SAFplusAmf */
