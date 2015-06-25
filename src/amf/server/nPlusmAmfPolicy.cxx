#include <chrono>
#include <clAmfPolicyPlugin.hxx>
#include <clLogApi.hxx>
#include <clProcessApi.hxx>
#include <clThreadApi.hxx>
#include <clNameApi.hxx>
#include <clAmfApi.hxx>
#include <vector>
#include <boost/range/algorithm.hpp>

#include <SAFplusAmf.hxx>
#include <ServiceGroup.hxx>

using namespace std;
using namespace SAFplus;
using namespace SAFplusAmf;

namespace SAFplus
  {
 
  const char* oper_str(bool val) { if (val) return "enabled"; else return "disabled"; }

  class NplusMPolicy:public ClAmfPolicyPlugin_1
    {
  public:
    NplusMPolicy();
    ~NplusMPolicy();
    virtual void activeAudit(SAFplusAmf::SAFplusAmfRoot* root);
    virtual void standbyAudit(SAFplusAmf::SAFplusAmfRoot* root);

  protected:
    void auditOperation(SAFplusAmf::SAFplusAmfRoot* root);
    void auditDiscovery(SAFplusAmf::SAFplusAmfRoot* root);
    };

  class ServiceGroupPolicyExecution: public Poolable
    {
    public:
    ServiceGroupPolicyExecution(ServiceGroup* svcgrp,AmfOperations* ops):sg(svcgrp),amfOps(ops) {} 

    ServiceGroup* sg;
    AmfOperations* amfOps;

    virtual void wake(int amt,void* cookie=NULL);

    void start();
    void stop();

    // helper functions
    int start(ServiceUnit* s,Wakeable& w);
    };

  NplusMPolicy::NplusMPolicy()
    {
    }

  NplusMPolicy::~NplusMPolicy()
    {
    }

  void ServiceGroupPolicyExecution::wake(int amt,void* cookie)
    {
    start();
    }

  bool suEarliestRanking(ServiceUnit* a, ServiceUnit* b)
  {
  assert(a);
  assert(b);
  if (b->rank.value == 0) return true;
  if (a->rank.value == 0) return false;
  return (a->rank.value < b->rank.value);
  }

  bool siEarliestRanking(ServiceInstance* a, ServiceInstance* b)
  {
  assert(a);
  assert(b);
  if (b->rank.value == 0) return true;
  if (a->rank.value == 0) return false;
  return (a->rank.value < b->rank.value);
  }

  int ServiceGroupPolicyExecution::start(ServiceUnit* su,Wakeable& w)
    {
    int ret=0;
    SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   itcomp;
    SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   endcomp = su->components.value.end();
    for (itcomp = su->components.value.begin(); itcomp != endcomp; itcomp++)
      {
      Component* comp = dynamic_cast<Component*>(*itcomp);
      if (comp->processId)
        {
        logDebug("N+M","STRT","Not starting [%s]. Its already started as pid [%d].",comp->name.value.c_str(),comp->processId.value);
        continue;
        }
      if (comp->operState == false)
        {
        logDebug("N+M","STRT","Not starting [%s]. It must be repaired.",comp->name.value.c_str());
        continue;
        }
      if (comp->numInstantiationAttempts.value >= comp->maxInstantInstantiations + comp->maxDelayedInstantiations)
        {
        logInfo("N+M","STRT","Faulting [%s]. It has exceeded its startup attempts [%d].",comp->name.value.c_str(),comp->maxInstantInstantiations + comp->maxDelayedInstantiations);
        comp->operState = false;
        comp->numInstantiationAttempts = 0;
        continue;
        }
      uint64_t curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
// (uint64_t) std::chrono::steady_clock::now().time_since_epoch().count()/std::chrono::milliseconds(1);
      if ((comp->numInstantiationAttempts.value >= comp->maxInstantInstantiations)&&(curTime < comp->delayBetweenInstantiation.value + comp->lastInstantiation.value.value))
        {
        logDebug("N+M","STRT","Not starting [%s]. Must wait [%" PRIu64 "] more milliseconds.",comp->name.value.c_str(),comp->delayBetweenInstantiation + comp->lastInstantiation.value.value - curTime);
        continue;
        }

      logInfo("N+M","STRT","Starting component [%s]", comp->name.value.c_str());
      CompStatus status = amfOps->getCompState(comp);

      SAFplusAmf::AdministrativeState eas = effectiveAdminState(comp);
      assert(eas != SAFplusAmf::AdministrativeState::off); // Do not call this API if the component is administratively OFF!
      amfOps->start(comp,w);
      ret++;
      }
    return ret;
    }

  void ServiceGroupPolicyExecution::start()
    {
      const std::string& name = sg->name;

      logInfo("N+M","STRT","Starting service group [%s]", name.c_str());
      if (1) // TODO: figure out if this Policy should control this Service group
        {
        std::vector<SAFplusAmf::ServiceUnit*> sus(sg->serviceUnits.value.begin(),sg->serviceUnits.value.end());

        // Sort the SUs by rank so we start them up in the proper order.
        boost::sort(sus,suEarliestRanking);

        int numActive = 0;  // TODO: figure this out, so start can be called from a half-started situation.
        int numStandby = 0; // TODO: figure this out, so start can be called from a half-started situation.
        int numIdle = 0;    // TODO: figure this out, so start can be called from a half-started situation.

        int totalStarted = numActive + numStandby + numIdle;
        int preferredTotal = sg->preferredNumActiveServiceUnits.value + sg->preferredNumStandbyServiceUnits.value + sg->preferredNumIdleServiceUnits.value;

        std::vector<SAFplusAmf::ServiceUnit*>::iterator itsu;
        int waits=0;
        int curRank = -1;
        ThreadSem waitSem;
        for (itsu = sus.begin(); itsu != sus.end(); itsu++)
          {
          if (totalStarted >= preferredTotal) break;  // we have started enough
          ServiceUnit* su = dynamic_cast<ServiceUnit*>(*itsu);
          // If we moved up to a new rank, we must first wait for the old rank to come up.  This is part of the definition of SU ranks
          if (su->rank.value != curRank)  
            {
            waitSem.lock(waits);  // This code works in the initial case because waits is 0, so no locking happens
            waits = 0;
            curRank = su->rank.value;
            }
          const std::string& suName = su->name;
          if (su->adminState != AdministrativeState::off)
            {
            logInfo("N+M","STRT","Starting service unit [%s]", suName.c_str());
            waits += start(su,waitSem);  // When started, "wake" will be called on the waitSem
            totalStarted++;
            }
          else
            {
            logInfo("N+M","STRT","Not starting service unit [%s] admin state is [%s]", suName.c_str(),c_str(su->adminState.value));
            }
          }
        waitSem.lock(waits);  // if waits is 0, lock is no-op
        }
    }

#if 0 
  void NplusMPolicy::activeAudit(SAFplusAmf::SAFplusAmfRoot* root)
    {
    logInfo("POL","N+M","Active audit");
    assert(root);
    SAFplusAmfRoot* cfg = (SAFplusAmfRoot*) root;

    MgtObject::Iterator it;

    for (it = cfg->serviceGroupList.begin();it != cfg->serviceGroupList.end(); it++)
      {
      ServiceGroup* sg = dynamic_cast<ServiceGroup*> (it->second);
      const std::string& name = sg->name;

      logInfo("N+M","AUDIT","Auditing service group [%s]", name.c_str());
      if (1) // TODO: figure out if this Policy should control this Service group
        {
        MgtObject::Iterator itsu;
        MgtObject::Iterator endsu = sg->serviceUnits.end();
        for (itsu = sg->serviceUnits.begin(); itsu != endsu; itsu++)
          {
         ServiceUnit* su = dynamic_cast<ServiceUnit*>(itsu->second);
         const std::string& suName = su->name;
          logInfo("N+M","AUDIT","Auditing su %s", suName.c_str());

          MgtObject::Iterator itcomp;
          MgtObject::Iterator endcomp = su->components.end();
          for (itcomp = su->components.begin(); itcomp != endcomp; itcomp++)
            {
            std::string compName = itcomp->first;
            logInfo("N+M","AUDIT","Auditing comp %s ", compName.c_str());
            Component* comp = dynamic_cast<Component*>(itcomp->second);
            logInfo("N+M","AUDIT","Auditing component %s", comp->name.c_str());
            amfOps->getCompState(comp);
            }
          }
        }

      }

    }
#endif

  bool running(SAFplusAmf::PresenceState p)
  {
  return (   (p == SAFplusAmf::PresenceState::instantiating)
          || (p == SAFplusAmf::PresenceState::instantiated)
          || (p == SAFplusAmf::PresenceState::terminating)
          || (p == SAFplusAmf::PresenceState::restarting)
          || (p == SAFplusAmf::PresenceState::terminationFailed));
  }

  void NplusMPolicy::activeAudit(SAFplusAmf::SAFplusAmfRoot* root)
    {
    auditDiscovery(root);
    auditOperation(root);
    }

  ServiceUnit* findAssignableServiceUnit(std::vector<SAFplusAmf::ServiceUnit*>& candidates,MgtList<std::string>& weights, HighAvailabilityState tgtState)
    {
    std::vector<SAFplusAmf::ServiceUnit*>::iterator i;
    for (i = candidates.begin(); i != candidates.end(); i++)
      {
      bool assignable = true;
      ServiceUnit* su = *i;
      assert(su);
      if (su->operState == true)
        {
        SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   itcomp;
        SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   endcomp = su->components.value.end();
        for (itcomp = su->components.value.begin(); itcomp != endcomp; itcomp++)
          {
          Component* comp = dynamic_cast<Component*>(*itcomp);
          assert(comp);
          if ((comp->operState.value == true) && (comp->readinessState.value == ReadinessState::inService) && (comp->haReadinessState == HighAvailabilityReadinessState::readyForAssignment) && (comp->haState != HighAvailabilityState::quiescing))
            {
            // candidate
            }
          else 
            {
            assignable = false;
            break;
            }
          }
        if (assignable) return su;
        }
      }
    return nullptr;
    }

  // Second step in the audit is to do something to heal any discrepencies.
  void NplusMPolicy::auditOperation(SAFplusAmf::SAFplusAmfRoot* root)
    {
    bool startSg;
    logInfo("POL","N+M","Active audit: Operation phase");
    assert(root);
    SAFplusAmfRoot* cfg = (SAFplusAmfRoot*) root;

    MgtObject::Iterator it;
    for (it = cfg->serviceGroupList.begin();it != cfg->serviceGroupList.end(); it++)
      {
      startSg=false;
      ServiceGroup* sg = dynamic_cast<ServiceGroup*> (it->second);
      const std::string& name = sg->name;
 
       // TODO: figure out if this Policy should control this Service group

      logInfo("N+M","AUDIT","Auditing service group [%s]", name.c_str());

      // Look for Service Units that need to be started up
      if (1)
        {
        SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator itsu;
        SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator endsu = sg->serviceUnits.value.end();
        for (itsu = sg->serviceUnits.value.begin(); itsu != endsu; itsu++)
          {
          //ServiceUnit* su = dynamic_cast<ServiceUnit*>(itsu->second);
          ServiceUnit* su = dynamic_cast<ServiceUnit*>(*itsu);
          const std::string& suName = su->name;
          logInfo("N+M","AUDIT","Auditing service unit [%s]: Operational State [%s] AdminState [%s] PresenceState [%s] ReadinessState [%s] HA State [%s] HA Readiness [%s] ", suName.c_str(),oper_str(su->operState.value), c_str(su->adminState.value), c_str(su->presenceState.value), c_str(su->readinessState.value), c_str(su->haState.value), c_str(su->haReadinessState.value) );

          SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   itcomp;
          SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   endcomp = su->components.value.end();
          for (itcomp = su->components.value.begin(); itcomp != endcomp; itcomp++)
            {
            Component* comp = dynamic_cast<Component*>(*itcomp);
            SAFplusAmf::AdministrativeState eas = effectiveAdminState(comp);
            if (comp->operState == true) // false means that the component needs repair before we will deal with it.
              {
              if (running(comp->presence.value))
                {
                if (eas == SAFplusAmf::AdministrativeState::off)
                  {
                  logError("N+M","AUDIT","Component [%s] should be off but is instantiated", comp->name.value.c_str());
                  }
                else
                  {
                  char timeString[80];
                  //struct tm * timeptr;
                  time_t rawtime = comp->lastInstantiation.value.value / 1000;  // /1000 converts ms to sec.
                  //timeinfo = localtime(&rawtime);
                  strftime(timeString,80,"%c",localtime(&rawtime));
                  logDebug("N+M","AUDIT","Component [%s] process [%s.%d] is [%s].  Instantiated since [%s].  Instantiation attempts [%d].",comp->name.value.c_str(), su->node.value->name.value.c_str(), comp->processId.value, c_str(comp->presence.value),timeString, comp->numInstantiationAttempts.value);
                  }
                }
              else
                {
                if (eas != SAFplusAmf::AdministrativeState::off)
                  {
                  logError("N+M","AUDIT","Component [%s] could be on but is not instantiated", comp->name.value.c_str());
                  startSg=true;
                  }
                }
              }
            }
          }
        }


      // Look for Service Instances that need assignment
      if (1) 
        {
        // TODO: pick the SU sort algorithm based on SG policy
        bool (*suOrder)(ServiceUnit* a, ServiceUnit* b) = suEarliestRanking;

        // Sort the SUs by rank so we assign them in proper order.
        // TODO: I don't like this constant resorting... we should have a sorted list in the SG.
        std::vector<SAFplusAmf::ServiceUnit*> sus(sg->serviceUnits.value.begin(),sg->serviceUnits.value.end());
        boost::sort(sus,suOrder);

        // Go through in rank order so that the most important SIs are assigned first
        std::vector<SAFplusAmf::ServiceInstance*> sis(sg->serviceInstances.value.begin(),sg->serviceInstances.value.end());
        boost::sort(sis,siEarliestRanking);

        std::vector<SAFplusAmf::ServiceInstance*>::iterator itsi;
        for (itsi = sis.begin(); itsi != sis.end(); itsi++)
          {
          ServiceInstance* si = dynamic_cast<ServiceInstance*>(*itsi);
          SAFplusAmf::AdministrativeState eas = effectiveAdminState(si);

          // We want to assign but for some reason it is not.
          if ((eas == AdministrativeState::on) && (si->assignmentState != AssignmentState::fullyAssigned))
            {
            logInfo("N+M","AUDIT","Service Instance [%s] should be fully assigned but is [%s].", si->name.value.c_str(),c_str(si->assignmentState));

            if (1)
              {
              for (int cnt = si->getActiveAssignments()->current.value; cnt < si->preferredActiveAssignments; cnt++)
                {
                ServiceUnit* su = findAssignableServiceUnit(sus,si->activeWeightList,HighAvailabilityState::active);
                if (su)
                  {
                  amfOps->assignWork(su,si,HighAvailabilityState::active);
                  boost::sort(sus,suOrder);  // Sort order may have changed based on the assignment.
                  }
                else
                  {
                  logInfo("N+M","AUDIT","Service Instance [%s] cannot be assigned %dth active.  No available service units.", si->name.value.c_str(),cnt);
                  break;
                  }
                }
              }
            if (si->getActiveAssignments()->current.value > 0)  // If there is at least 1 active, try to assign the standbys
              {
              for (int cnt = si->getStandbyAssignments()->current.value; cnt < si->preferredStandbyAssignments; cnt++)
                {
                ServiceUnit* su = findAssignableServiceUnit(sus,si->standbyWeightList,HighAvailabilityState::standby);
                if (su)
                  {
                  amfOps->assignWork(su,si,HighAvailabilityState::standby);
                  boost::sort(sus,suOrder);  // Sort order may have changed based on the assignment.
                  }
                else
                  {
                  logInfo("N+M","AUDIT","Service Instance [%s] cannot be assigned %dth standby.  No available service units.", si->name.value.c_str(),cnt);
                  break;
                  }
                }
              }
            }

          else if ((eas == AdministrativeState::off) && (si->assignmentState != AssignmentState::unassigned))
            {
            logInfo("N+M","AUDIT","Service Instance [%s] should be unassigned but is [%s].", si->name.value.c_str(),c_str(si->assignmentState));
            amfOps->removeWork(si);
            }
          else
            {
            logInfo("N+M","AUDIT","Service Instance [%s]: admin state [%s]. assignment state [%s].  Assignments: active [%ld] standby [%ld]. ", si->name.value.c_str(),c_str(si->adminState.value), c_str(si->assignmentState), si->getActiveAssignments()->current.value,si->getStandbyAssignments()->current.value  );
            }

          }
        }

      if (startSg)
        {
        ServiceGroupPolicyExecution go(sg,amfOps);
        go.start(); // TODO: this will be put in a thread pool...
        }
      }

    }

  void updateStateDueToProcessDeath(SAFplusAmf::Component* comp)
    {
    comp->presence = PresenceState::uninstantiated;
    comp->processId = 0;
    SAFplus::name.set(comp->name,INVALID_HDL,NameRegistrar::MODE_NO_CHANGE);  // remove the handle in the name service because the component is dead
    
    SAFplusAmf::ServiceUnit* su = comp->serviceUnit.value;
    SAFplusAmf::ServiceGroup* sg = su->serviceGroup.value;
    
    // I need to remove any CSIs that were assigned to this component.
    SAFplus::MgtProvList<SAFplusAmf::ServiceInstance*>::ContainerType::iterator itsi;
    SAFplus::MgtProvList<SAFplusAmf::ServiceInstance*>::ContainerType::iterator endsi = sg->serviceInstances.value.end();
    for (itsi = sg->serviceInstances.value.begin();itsi != endsi; itsi++)
      {
      ServiceInstance* si = *itsi;
      const std::string& name = si->name;

      SAFplus::MgtProvList<SAFplusAmf::ComponentServiceInstance*>::ContainerType::iterator itcsi;
      SAFplus::MgtProvList<SAFplusAmf::ComponentServiceInstance*>::ContainerType::iterator endcsi = si->componentServiceInstances.value.end();

      SAFplusAmf::ComponentServiceInstance* csi = NULL;
      bool found = false;

      // Look for which CSI is assigned to the dead component and remove the assignment.
      for (itcsi = si->componentServiceInstances.value.begin(); itcsi != endcsi; itcsi++)
        {
        csi = *itcsi;
        if (!csi) continue;
        if (1)
          {
          std::vector<SAFplusAmf::Component*>& vec = csi->activeComponents.value;
          if (std::find(vec.begin(), vec.end(), comp) != vec.end())
            {
            found = true;
            vec.erase(std::remove(vec.begin(),vec.end(), comp), vec.end());
            }
          }
        if (1)
          {
          std::vector<SAFplusAmf::Component*>& vec = csi->standbyComponents.value;
          if (std::find(vec.begin(), vec.end(), comp) != vec.end())
            {
            found = true;
            vec.erase(std::remove(vec.begin(),vec.end(), comp), vec.end());
            }
          }
        }
      if (found) si->assignmentState = AssignmentState::partiallyAssigned;  // TODO: or it could be unassigned...
      }

    }

  // First step in the audit is to update the current state of every entity to match the reality.
  void NplusMPolicy::auditDiscovery(SAFplusAmf::SAFplusAmfRoot* root)
    {
    logInfo("POL","N+M","Active audit: Discovery phase");
    assert(root);
    SAFplusAmfRoot* cfg = (SAFplusAmfRoot*) root;

    MgtObject::Iterator it;
    for (it = cfg->serviceGroupList.begin();it != cfg->serviceGroupList.end(); it++)
      {
      ServiceGroup* sg = dynamic_cast<ServiceGroup*> (it->second);
      const std::string& name = sg->name;

      logInfo("N+M","AUDIT","Auditing service group [%s]", name.c_str());
      if (1) // TODO: figure out if this Policy should control this Service group
        {
        SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator itsu;
        SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator endsu = sg->serviceUnits.value.end();
        for (itsu = sg->serviceUnits.value.begin(); itsu != endsu; itsu++)
          {
          uint readyForAssignment;
          readyForAssignment = 0;
          //ServiceUnit* su = dynamic_cast<ServiceUnit*>(itsu->second);
          ServiceUnit* su = dynamic_cast<ServiceUnit*>(*itsu);
          Node* suNode = su->node.value;
          const std::string& suName = su->name;
          logInfo("N+M","AUDIT","Auditing service unit [%s]", suName.c_str());

          // Calculate readiness state SAI-AIS-AMF-B.04.01.pdf sec 3.2.1.4
          ReadinessState rs = su->readinessState.value;
          // out of service if needs repair
          if ((suNode == nullptr) || (su->operState.value == false)||(suNode->operState.value == false)
          // or any related entity is adminstratively off
            || (su->adminState.value != AdministrativeState::on) || (suNode->adminState.value != AdministrativeState::on) || (sg->adminState.value != AdministrativeState::on) 
            || ((nullptr!=sg->application.value) && (sg->application.value->adminState != AdministrativeState::on))
            // or its presence state is neither instantiated nor restarting,
            || ((su->presenceState.value != PresenceState::instantiated) && (su->presenceState.value != PresenceState::restarting))
            // TODO: or the service unit contains contained components, and their configured container CSI is not assigned active or quiescing to any container component on the node that contains the service unit.
            )
            {
            rs = ReadinessState::outOfService;
            }
          
          // in service if does not need repair
          else if ( (su->operState == true)&&(suNode->operState == true) 
            // and administratively on
            && (su->adminState == AdministrativeState::on) && (suNode->adminState == AdministrativeState::on) && (sg->adminState == AdministrativeState::on) 
            && (!sg->application.value || (sg->application.value->adminState == AdministrativeState::on))
            // and its presence state is either instantiated or restarting,
            && ((su->presenceState == PresenceState::instantiated) || (su->presenceState == PresenceState::restarting)))
            {
            rs = ReadinessState::inService;
            }
          else
            {
            // TODO: stopping
            }

          if (rs != su->readinessState.value)
            {
            logInfo("N+M","AUDIT","Readiness state of Service Unit [%s] changed from [%s] to [%s]", su->name.value.c_str(),c_str(su->readinessState),c_str(rs));
            su->readinessState.value = rs;
            // TODO event?
            }


          int numComps = 0;
          // count up the presence state of each component so I can infer the presence state of the SU
          int presenceCounts[((int)PresenceState::terminationFailed)+1];
          int haCounts[((int)HighAvailabilityState::quiescing)+1];
          for (int j = 0; j<((int)PresenceState::terminationFailed)+1;j++) presenceCounts[j] = 0;
          for (int j = 0; j<((int)HighAvailabilityState::quiescing)+1;j++) haCounts[j] = 0;

          SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   itcomp;
          SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   endcomp = su->components.value.end();
          for (itcomp = su->components.value.begin(); itcomp != endcomp; itcomp++)
            {
            numComps++;
            Component* comp = dynamic_cast<Component*>(*itcomp);
            logInfo("N+M","AUDIT","Component [%s]: operState [%s]", comp->name.value.c_str(), comp->operState.value ? "enabled" : "faulted");
            if (running(comp->presence))  // If I think its running, let's check it out.
              {
              CompStatus status = amfOps->getCompState(comp);
              if (status == CompStatus::Uninstantiated)  // database shows should be running but actually no process is there.  I should update DB.
                {
                  try
                    {
                    Handle compHdl = ::name.getHandle(comp->name);
                    // Actually it throws NameException: assert(compHdl != INVALID_HDL);  // AMF MUST register this component before it does anything else with it so the name must exist.              
                    fault->notify(compHdl,FaultEventData(AlarmState::ALARM_STATE_ASSERT,AlarmCategory::ALARM_CATEGORY_PROCESSING_ERROR,AlarmSeverity::ALARM_SEVERITY_MAJOR, AlarmProbableCause::ALARM_PROB_CAUSE_SOFTWARE_ERROR));
                    // TODO: it may be better to have the AMF react to fault manager's notification instead of doing it preemptively here
                    }
                  catch(NameException& ne)
                    {
                    logWarning("N+M","AUDIT","Component [%s] is marked as running with uninstantiated state and no name registration (no handle).  It may have died at startup.", comp->name.value.c_str());
                    }
                updateStateDueToProcessDeath(comp);
                }
              else if (comp->presence == PresenceState::instantiating)  // If the component is in the instantiating state, look for it to register with the AMF
                {
                Handle compHandle=INVALID_HDL;
                try
                  {
                  RefObjMapPair p = SAFplus::name.get(comp->name);  // The way a component "registers" is that it puts its name in the name service.
                  compHandle = p.first;
                  }
                catch(NameException& n)
                  {
                    // compHandle=INVALID_HDL; I'd do this but its already set.
                  }
                
                if (compHandle != INVALID_HDL) // TODO: what other things do we need to do for registration?
                  {
                  comp->presence = PresenceState::instantiated;
                  fault->registerEntity(compHandle ,FaultState::STATE_UP);
                  }
                else
                  {
                  uint64_t curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                  if (curTime - comp->lastInstantiation.value.value >= comp->getInstantiate()->timeout.value)
                    {
                    // TODO: process is not responding after instantiation.  Kill it.
                    logError("N+M","AUDIT","Component [%s] never registered with AMF after instantiation.", comp->name.value.c_str());
                    }
                  else
                    {
                      logInfo("N+M","AUDIT","Component [%s] waiting [%lu] more milliseconds for instantiation.", comp->name.value.c_str(),(long unsigned int) (comp->getInstantiate()->timeout.value - (curTime - comp->lastInstantiation.value.value)));
                    }
                  }
                }
              else if (comp->presence == PresenceState::instantiated)
                {
                // If the component has been instantiated for long enough, reset the instantiation attempts.

                uint64_t curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                if (curTime - comp->lastInstantiation.value.value >= comp->instantiationSuccessDuration.value)
                  {
                  comp->numInstantiationAttempts.value = 0; 
                  }
                
                if (comp->haReadinessState == HighAvailabilityReadinessState::readyForAssignment)
                  {
                    readyForAssignment++;
                  }
                }
              }

            // SAI-AIS-AMF-B.04.01.pdf sec 3.2.2.3
            if ((comp->operState == false) || (su->readinessState == SAFplusAmf::ReadinessState::outOfService))
              {
              comp->readinessState = SAFplusAmf::ReadinessState::outOfService;
              }
            if ((comp->operState == true) && (su->readinessState == SAFplusAmf::ReadinessState::inService))
              {
              comp->readinessState = SAFplusAmf::ReadinessState::inService;
              }
            if ((comp->operState == true) && (su->readinessState == SAFplusAmf::ReadinessState::stopping))
              {
              comp->readinessState = SAFplusAmf::ReadinessState::stopping;
              }

            assert(((int)comp->presence.value <= ((int)PresenceState::terminationFailed))&&((int)comp->presence.value >= ((int)PresenceState::uninstantiated)));
            presenceCounts[(int)comp->presence.value]++;
            assert(((int)comp->haState.value <= (int)HighAvailabilityState::quiescing)&&((int)comp->haState.value >= (int)HighAvailabilityState::active));
            haCounts[(int)comp->haState.value]++;
            }


          // High Availability state calculation (TODO: validate logic against AMF spec)
          HighAvailabilityState ha = su->haState; // .value;

          if (haCounts[(int)HighAvailabilityState::quiescing] > 0)  // If any component is quiescing, the Service Unit's HA state is quiescing
            {
              ha = HighAvailabilityState::quiescing;
            }
          else if (haCounts[(int)HighAvailabilityState::active] == numComps)  // If all components have an active assignment, SU is active
            {
              ha = HighAvailabilityState::active;
            }
          else if (haCounts[(int)HighAvailabilityState::standby] == numComps)  // If all components have a standby assignment, SU is standby
            {
              ha = HighAvailabilityState::standby;
            }
          else ha = HighAvailabilityState::idle;

          if (ha != su->haState.value)
            {
            // high availability state changed.
            logInfo("N+M","AUDIT","High Availability state of Service Unit [%s] changed from [%s (%d)] to [%s (%d)]", su->name.value.c_str(),c_str(su->haState.value),su->haState.value, c_str(ha), ha);
            su->haState = ha;

            // TODO: Event?
            }


           // SAI-AIS-AMF-B.04.01.pdf sec 3.2.1.1, presence state calculation
          PresenceState ps = su->presenceState.value;
          if (presenceCounts[(int)PresenceState::uninstantiated] == numComps)  // When all components are uninstantiated, the service unit is uninstantiated.
            {
            ps = PresenceState::uninstantiated;
            }
          else if (presenceCounts[(int)PresenceState::instantiating] > 0) // When the first component moves to instantiating, the service unit also becomes instantiating.
            {
            ps = PresenceState::instantiating;
            }
          else if (presenceCounts[(int)PresenceState::instantiated] == numComps) // When all pre-instantiable components of a service unit enter the instantiated state, the service unit becomes instantiated
            {
            ps = PresenceState::instantiated;
            }
          else if (presenceCounts[(int)PresenceState::instantiationFailed] > 0)  // If, after all possible retries, a component cannot be instantiated, the presence state of the component is set to instantiation-failed, and the presence state of the service unit is also set to instantiation-failed.
            {
            ps = PresenceState::instantiationFailed;
            }
          else if (presenceCounts[(int)PresenceState::terminating] > 0)  // When the first component of an already instantiated service unit becomes terminating, the service unit becomes terminating.
            {
            ps = PresenceState::terminating;
            }
          else if (presenceCounts[(int)PresenceState::terminationFailed] > 0)  // If the Availability Management Framework fails to terminate a component, the presence state of the component is set to termination-failed and the presence state of the service unit is also set to termination-failed.
            {
            ps = PresenceState::terminationFailed;
            }
          else if (presenceCounts[(int)PresenceState::restarting] == numComps) // When all components enter the restarting state, the service unit become restarting.  However, if only some components are restarting, the service unit is still instantiated.
            {
            ps = PresenceState::restarting;
            }

          if (ps != su->presenceState.value)
            {
            // Presence state changed.
            logInfo("N+M","AUDIT","Presence state of Service Unit [%s] changed from [%s (%d)] to [%s (%d)]", su->name.value.c_str(),c_str(su->presenceState.value),su->presenceState.value, c_str(ps), ps);
            su->presenceState.value = ps;

            // TODO: Event?
            }


          // Now address SU's haReadinessState.  AMF B04.01 states that the haReadiness state should be per SU/SI combination.  It is the ability of this SU to accept a particular piece of work.  At this point I am going to reject this as unnecessary complexity and have a single haReadinessState per SU.  Having work that cannot be applied to particular SUs is problematic because the AMF has no way (other than guessing) to determine which work can be assigned to which SU.  If work can't be assigned to a SU, it should not be in that SG in the first place (create a separate SG for that work).
          HighAvailabilityReadinessState hrs; // = su->haReadinessState;
          if (readyForAssignment == numComps) hrs = HighAvailabilityReadinessState::readyForAssignment;
          else hrs = HighAvailabilityReadinessState::notReadyForAssignment;
          if (hrs != su->haReadinessState)
            {
            logInfo("N+M","AUDIT","High availability readiness state of Service Unit [%s] changed from [%s (%d)] to [%s (%d)]", su->name.value.c_str(),c_str(su->haReadinessState.value),su->haReadinessState.value, c_str(hrs), hrs);
            su->haReadinessState.value = hrs;
            }

          }
        }

        SAFplus::MgtProvList<SAFplusAmf::ServiceInstance*>::ContainerType::iterator itsi;
        SAFplus::MgtProvList<SAFplusAmf::ServiceInstance*>::ContainerType::iterator endsi = sg->serviceInstances.value.end();
        for (itsi = sg->serviceInstances.value.begin(); itsi != endsi; itsi++)
          {
            SAFplusAmf::ServiceInstance* si = dynamic_cast<ServiceInstance*>(*itsi);
            logInfo("N+M","AUDIT","Auditing service instance [%s]", si->name.value.c_str());

            si->getActiveAssignments()->current.value = 0;  // TODO set this correctly
            si->getStandbyAssignments()->current.value = 0; // TODO set this correctly

            AssignmentState as = si->assignmentState;
          //if (wat.si->assignmentState = AssignmentState::fullyAssigned;  // TODO: for now just make the SI happy to see something work

            if (as != si->assignmentState)
              {
              logInfo("N+M","AUDIT","Assignment state of service instance [%s] changed from [%s (%d)] to [%s (%d)]", si->name.value.c_str(),c_str(si->assignmentState.value),si->assignmentState.value, c_str(as), as);
              si->assignmentState = as;
              }
          }


      }

    }

  void NplusMPolicy::standbyAudit(SAFplusAmf::SAFplusAmfRoot* root)
    {
    logInfo("POL","CUSTOM","Standby audit");
    }

  static NplusMPolicy api;
  };

extern "C" SAFplus::ClPlugin* clPluginInitialize(uint_t preferredPluginVersion)
  {
  // We can only provide a single version, so don't bother with the 'preferredPluginVersion' variable.

  // Initialize the pluginData structure
  SAFplus::api.pluginId         = CL_AMF_POLICY_PLUGIN_ID;
  SAFplus::api.pluginVersion    = CL_AMF_POLICY_PLUGIN_VER;

  SAFplus::api.policyId = SAFplus::AmfRedundancyPolicy::NplusM;

  // return it
  return (ClPlugin*) &SAFplus::api;
  }