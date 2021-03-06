#include <chrono>
#include <google/protobuf/stubs/common.h>
#include <clCommon.hxx>
#include "amfRpc/amfRpc.pb.hxx"
#include "amfRpc/amfRpc.hxx"
#include "amfAppRpc/amfAppRpc.hxx"
#include "clPortAllocator.hxx"
#include <clRpcChannel.hxx>

#include <amfOperations.hxx>
#include <clHandleApi.hxx>
#include <clNameApi.hxx>
#include <clOsalApi.hxx>
#include <clAmfPolicyPlugin.hxx>
#include <clAmfIpi.hxx>

#include <SAFplusAmf/Component.hxx>
#include <SAFplusAmf/ComponentServiceInstance.hxx>
#include <SAFplusAmf/ServiceUnit.hxx>
#include <SAFplusAmf/ServiceGroup.hxx>
#include <SAFplusAmf/Data.hxx>

using namespace SAFplus;
using namespace SAFplusI;
using namespace SAFplusAmf;
using namespace SAFplus::Rpc::amfRpc;

extern Handle           nodeHandle; //? The handle associated with this node
namespace SAFplus
  {

    uint64_t nowMs() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

    WorkOperationTracker::WorkOperationTracker(SAFplusAmf::Component* c,SAFplusAmf::ComponentServiceInstance* cwork,SAFplusAmf::ServiceInstance* work,uint statep, uint targetp)
    {
    comp = c; csi = cwork; si=work; state = statep; target = targetp;
    issueTime = nowMs();
    }


  // Move this service group and all contained elements to the specified state.
  void setAdminState(SAFplusAmf::ServiceGroup* sg,SAFplusAmf::AdministrativeState tgt)
    {
    SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator itsu;
    SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator endsu = sg->serviceUnits.value.end();
    for (itsu = sg->serviceUnits.value.begin(); itsu != endsu; itsu++)
      {
      //ServiceUnit* su = dynamic_cast<ServiceUnit*>(itsu->second);
      ServiceUnit* su = dynamic_cast<ServiceUnit*>(*itsu);
      const std::string& suName = su->name;
      if (su->adminState.value != tgt)
        {
        logInfo("N+M","AUDIT","Setting service unit [%s] to admin state [%d]",suName.c_str(),tgt);
        su->adminState.value = tgt;
        // TODO: transactional and event
        }
      }
      if (sg->adminState.value != tgt)
        {
        logInfo("N+M","AUDIT","Setting service group [%s] to admin state [%d]",sg->name.value.c_str(),tgt);
        sg->adminState.value = tgt;
        }
    }

  // The effective administrative state is calculated by looking at the admin state of the containers: SU, SG, node, and application.  If any contain a "more restrictive" state, then this component inherits the more restrictive state.  The states from most to least restrictive is off, idle, on.  The Application object is optional.
  SAFplusAmf::AdministrativeState effectiveAdminState(SAFplusAmf::Component* comp)
    {
    assert(comp);
    if (!comp->serviceUnit.value) comp->serviceUnit.updateReference(); // find the pointer if it is not resolved

    if ((!comp->serviceUnit.value)||(!comp->serviceUnit.value->node.value)||(!comp->serviceUnit.value->serviceGroup.value))  // This component is not properly hooked up to other entities; it must be off
      {
      logInfo("N+M","AUDIT","Component [%s] entity group is not properly configured",comp->name.value.c_str());
      return SAFplusAmf::AdministrativeState::off;
      }
    ServiceUnit* su = comp->serviceUnit.value;
    return effectiveAdminState(su);
    }

  SAFplusAmf::AdministrativeState effectiveAdminState(SAFplusAmf::ServiceUnit* su)
    {
    assert(su);
    if ((!su->node.value)||(!su->serviceGroup.value))  // This component is not properly hooked up to other entities; is must be off
      {
      return SAFplusAmf::AdministrativeState::off;
      }
    Node* node = su->node.value;
    ServiceGroup* sg = su->serviceGroup.value;
    Application* app = sg->application;

    if ((su->adminState.value == SAFplusAmf::AdministrativeState::off) || (sg->adminState.value == SAFplusAmf::AdministrativeState::off)
      || (node->adminState.value == SAFplusAmf::AdministrativeState::off) || (app && app->adminState.value == SAFplusAmf::AdministrativeState::off))
      return SAFplusAmf::AdministrativeState::off;

    if ((su->adminState.value == SAFplusAmf::AdministrativeState::idle) || (sg->adminState.value == SAFplusAmf::AdministrativeState::idle)
      || (node->adminState.value == SAFplusAmf::AdministrativeState::off) || (app && app->adminState.value == SAFplusAmf::AdministrativeState::idle))
      return SAFplusAmf::AdministrativeState::idle;

    if ((su->adminState.value == SAFplusAmf::AdministrativeState::on) || (sg->adminState.value == SAFplusAmf::AdministrativeState::on)
      || (node->adminState.value == SAFplusAmf::AdministrativeState::off) || (app && app->adminState.value == SAFplusAmf::AdministrativeState::on))
      return SAFplusAmf::AdministrativeState::on;
    }

  SAFplusAmf::AdministrativeState effectiveAdminState(SAFplusAmf::ServiceGroup* sg)
    {
    assert(sg);
    Application* app = sg->application;

    if ((sg->adminState.value == SAFplusAmf::AdministrativeState::off) || (app && app->adminState.value == SAFplusAmf::AdministrativeState::off))
      return SAFplusAmf::AdministrativeState::off;

    if ( (sg->adminState.value == SAFplusAmf::AdministrativeState::idle) || (app && app->adminState.value == SAFplusAmf::AdministrativeState::idle))
      return SAFplusAmf::AdministrativeState::idle;

    if ((sg->adminState.value == SAFplusAmf::AdministrativeState::on) || (app && app->adminState.value == SAFplusAmf::AdministrativeState::on))
      return SAFplusAmf::AdministrativeState::on;
    }

  SAFplusAmf::AdministrativeState effectiveAdminState(SAFplusAmf::ServiceInstance* si)
    {
    // If either SG or SI is off, admin state is off
    if (si->adminState.value == SAFplusAmf::AdministrativeState::off) return SAFplusAmf::AdministrativeState::off;

    ServiceGroup* sg = si->serviceGroup.value;

    SAFplusAmf::AdministrativeState ret;
    ret = effectiveAdminState(sg);

    if (ret == SAFplusAmf::AdministrativeState::off) return ret;
 
    // If either SG or SI is idle, admin state is idle
    if ((ret == SAFplusAmf::AdministrativeState::idle) || (si->adminState.value == SAFplusAmf::AdministrativeState::idle)) return SAFplusAmf::AdministrativeState::idle;
        
    // If its not off or idle, it must be on
    return SAFplusAmf::AdministrativeState::on;
    }

    bool ClAmfPolicyPlugin_1::initialize(SAFplus::AmfOperations* amfOperations,SAFplus::Fault* faultp)
    {
    amfOps = amfOperations;
    fault  = faultp;
    return true;
    }

  void AmfOperations::workOperationResponse(uint64_t invocation, uint32_t result)
    {
    if (1)
      {
      WorkOperationTracker& wat = pendingWorkOperations.at(invocation);
      logInfo("AMF","OPS","Work Operation response on component [%s] invocation [%" PRIu64 "] result [%d]",wat.comp->name.value.c_str(),invocation, result);

      if ( wat.state <= (int) HighAvailabilityState::quiescing)
        {
        if (result == SA_AIS_OK)  // TODO: actually, I think I need to call into the redundancy model plugin to correctly process the result.
          {
          assert(wat.comp->pendingOperation == PendingOperation::workAssignment);  // No one should be issuing another operation until this one is aborted

          wat.comp->haState = (SAFplusAmf::HighAvailabilityState) wat.state; // TODO: won't work with multiple assignments of active and standby, for example
          // if (wat.si->assignmentState = AssignmentState::fullyAssigned;  // TODO: for now just make the SI happy to see something work

          // pending operation completed.  Clear it out
          wat.comp->pendingOperationExpiration.value.value = 0;
          wat.comp->pendingOperation = PendingOperation::none;
          }
        }
      else // work removal
        {
        if (result == SA_AIS_OK)  // TODO: actually, I think I need to call into the redundancy model plugin to correctly process the result.
          {
          assert(wat.comp->pendingOperation == PendingOperation::workRemoval);  // No one should be issuing another operation until this one is aborted

          wat.comp->haState = SAFplusAmf::HighAvailabilityState::idle;
          // if (wat.si->assignmentState = AssignmentState::fullyAssigned;  // TODO: for now just make the SI happy to see something work

          // pending operation completed.  Clear it out
          wat.comp->pendingOperationExpiration.value.value = 0;
          wat.comp->pendingOperation = PendingOperation::none;
          }
        }
      reportChange();
      }
    // TODO: crashes pendingWorkOperations.erase(invocation);
    
    }

  CompStatus AmfOperations::getCompState(SAFplusAmf::Component* comp)
    {
    assert(comp);
    if (!comp->serviceUnit)
      {
      return CompStatus::Uninstantiated; 
      }
    if (!comp->serviceUnit.value->node)
      {
      return CompStatus::Uninstantiated; 
      }

    try
      {
      Handle nodeHdl = name.getHandle(comp->serviceUnit.value->node.value->name);

      int pid = comp->processId;
      if (0) // nodeHdl == nodeHandle)  // Handle this request locally
        {
        if (pid == 0)
          {
          return CompStatus::Uninstantiated;
          }
        Process p(pid);
        try
          {
          std::string cmdline = p.getCmdline();
          // Some other process took that PID
          // TODO: if (cmdline != comp->commandLine)  return CompStatus::Uninstantiated;
          }
        catch (ProcessError& pe)
          {
          return CompStatus::Uninstantiated;
          }

        // TODO: Talk to the process to discover its state...
        return CompStatus::Instantiated;
        }
      else  // RPC call
        {
          //logInfo("OP","CMP","Request component [%s] state from node [%s]", comp->name.value.c_str(), comp->serviceUnit.value->node.value->name.value.c_str());

        ProcessInfoRequest req;
        req.set_pid(pid);
        ProcessInfoResponse resp;
        amfInternalRpc->processInfo(nodeHdl,&req, &resp);
        if (!resp.IsInitialized())
          {
            // RPC call is broken, should throw exception
            assert(0);
          }
        logInfo("OP","CMP","Request component [%s] state from node [%s] returned [%s]", comp->name.value.c_str(), comp->serviceUnit.value->node.value->name.value.c_str(),resp.running() ? "running" : "stopped");

        if (resp.running()) 
          {
          // TODO: I need to compare the process command line with my command line to make sure that my proc didn't die and another reuse the pid
          return CompStatus::Instantiated;
          }
        else return CompStatus::Uninstantiated;
        }
      }
    catch (NameException& e)
      {
      return CompStatus::Uninstantiated;
      }
    }

  class StartCompResp:public SAFplus::Wakeable
    {
    public:
      StartCompResp(SAFplus::Wakeable* w, SAFplusAmf::Component* comp): w(w), comp(comp) {};
      virtual ~StartCompResp(){};
    SAFplus::Rpc::amfRpc::StartComponentResponse response;
    SAFplusAmf::Component* comp;
    SAFplus::Wakeable* w;

    void wake(int amt,void* cookie=NULL)
      {
      if (response.err() != 0)
        {
        comp->processId.value = 0;
        comp->lastError.value = strprintf("Process spawn failure [%s:%d]", strerror(response.err()));
        comp->presenceState.value  = PresenceState::instantiationFailed;
        }
      else if (comp)
        {
        comp->processId.value = response.pid();

       if ( comp->capabilityModel == CapabilityModel::not_preinstantiable)
          {
          Handle handle=getProcessHandle(comp->processId.value);
          name.set(comp->name, handle, NameRegistrar::MODE_NO_CHANGE); // I need to set the handle because the process itself will not do so.
        
          comp->presenceState.value  = PresenceState::instantiated;    // There are no transitional states in the not_preinstantiable (not SAF aware) case
          }
        else
          {
            comp->presenceState.value  = PresenceState::instantiating;   // When the component sets its handle, this will be marked instantiated.
          }

        }
      if (w) w->wake(1,comp);
      delete this;
      }
    };


  class WorkOperationResponseHandler:public SAFplus::Wakeable
    {
    public:
    WorkOperationResponseHandler(SAFplus::Wakeable* w, SAFplusAmf::Component* comp): w(w), comp(comp) {};
    virtual ~WorkOperationResponseHandler(){};
    //SAFplus::Rpc::amfAppRpc::WorkOperationResponse response;
    SAFplusAmf::Component* comp;
    SAFplus::Wakeable* w;

    void wake(int amt,void* cookie=NULL)
      {
#if 0
      if (response.err() != 0)
        {
        comp->processId.value = 0;
        comp->lastError.value = strprintf("Process spawn failure [%s:%d]", strerror(response.err()));
        comp->presence.value  = PresenceState::instantiationFailed;
        }
      else if (comp)
        {
        comp->processId.value = response.pid();
        comp->presence.value  = PresenceState::instantiating;
        }
#endif
      if (w) w->wake(1,comp);
      delete this;
      }
    };

  void AmfOperations::removeWork(SAFplusAmf::ServiceInstance* si,Wakeable& w)
    {
    auto standby = si->getNumStandbyAssignments();
    auto active = si->getNumActiveAssignments();
    
    
    }

    void AmfOperations::removeWork(ServiceUnit* su, Wakeable& w)
    {
      assert(su);

      // Update the Service Instances: decrement assignment statistics, and remove this SU from the SI's assigned list.
      SAFplus::MgtProvList<SAFplusAmf::ServiceInstance*>::ContainerType::iterator   it;
      SAFplus::MgtProvList<SAFplusAmf::ServiceInstance*>::ContainerType::iterator   end = su->assignedServiceInstances.value.end();
      for (it = su->assignedServiceInstances.value.begin(); it != end; it++)
        {
          ServiceInstance* si = dynamic_cast<ServiceInstance*>(*it);
          assert(si);
          if (si->activeAssignments.find(su) != si->activeAssignments.value.end())
            {
              assert(si->numActiveAssignments.current > 0); // Data is inconsistent
              si->numActiveAssignments.current -= 1;
              si->activeAssignments.erase(su);
            }

          if (si->standbyAssignments.find(su) != si->standbyAssignments.value.end())
            {
              assert(si->numStandbyAssignments.current > 0);  // Data is inconsistent
              si->numStandbyAssignments.current -= 1;
              si->standbyAssignments.erase(su);
            }
          if ((si->numActiveAssignments.current.value == 0)||(si->numStandbyAssignments.current.value == 0)) si->assignmentState = AssignmentState::partiallyAssigned;
          if ((si->numActiveAssignments.current.value == 0)&&(si->numStandbyAssignments.current.value == 0)) si->assignmentState = AssignmentState::unassigned;
        }

      // Update the Service Unit's statistics and SI list.
      su->assignedServiceInstances.clear();
      su->numActiveServiceInstances = 0;
      su->numStandbyServiceInstances = 0;

      // TODO: clear the CSI structures

      // Now actually remove the work from the relevant components
      SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   itcomp;
      SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   endcomp = su->components.value.end();
      for (itcomp = su->components.value.begin(); itcomp != endcomp; itcomp++)
        {
          Component* comp = dynamic_cast<Component*>(*itcomp);
          assert(comp);   

          // In multi component service units, we need to remove the work from all the other components. 
          if (!((comp->presenceState == PresenceState::uninstantiated) || (comp->presenceState == PresenceState::instantiationFailed)))
            {
              if ( comp->capabilityModel == CapabilityModel::not_preinstantiable)  // except if it has no work we just kill it
                {
                  abort(comp, w);  // TODO, need to consolidate the wakeables
                }
              else
                {
                  // Nothing to do if already dead or never started
                  if (!((comp->presenceState == PresenceState::uninstantiated) || (comp->presenceState == PresenceState::instantiationFailed)))
                    {
                      SAFplus::Rpc::amfAppRpc::WorkOperationRequest request;
                      Handle hdl;
                      try
                        {
                          hdl = name.getHandle(comp->name);
                        }
                      catch (SAFplus::NameException& n)
                        {
                          logCritical("OPS","WRK","Component [%s] is not registered in the name service.  Cannot control it.", comp->name.value.c_str());
                          comp->lastError.value = "Component's name is not registered in the name service so cannot remove work cleanly";
                          // this one should be killed since it can't be controlled
                          abort(comp,w);  // TODO, need to consolidate the wakeables
                          // TODO ? anything to set in the comp's status?
                          continue; // Go to the next component
                        }

                      // Mark this component with a pending operation.  This will be cleared in the WorkOperationTracker, or by timeout in auditDiscovery
                      comp->pendingOperationExpiration.value.value = nowMs() + comp->timeouts.workAssignment;
                      comp->pendingOperation = PendingOperation::workRemoval;

                      request.set_componentname(comp->name.value.c_str());
                      request.set_componenthandle((const char*) &hdl, sizeof(Handle)); // [libprotobuf ERROR google/protobuf/wire_format.cc:1053] String field contains invalid UTF-8 data when serializing a protocol buffer. Use the 'bytes' type if you intend to send raw bytes.
                      request.set_operation((uint32_t)SAFplusI::AMF_HA_OPERATION_REMOVE);
                      request.set_target(SA_AMF_CSI_TARGET_ALL);
                      if ((invocation & 0xFFFFFFFF) == 0xFFFFFFFF) invocation &= 0xFFFFFFFF00000000ULL;  // Don't let increasing invocation numbers overwrite the node or port... ofc this'll never happen 4 billion invocations? :-)
                      request.set_invocation(invocation++);

                      // Now I need to fill up the key/value pairs from the CSI
                      request.clear_keyvaluepairs();

                      pendingWorkOperations[request.invocation()] = WorkOperationTracker(comp,nullptr,nullptr,(uint32_t)SAFplusI::AMF_HA_OPERATION_REMOVE,SA_AMF_CSI_TARGET_ALL);

                      amfAppRpc->workOperation(hdl, &request);
                    }
                }
            }
        }
      reportChange();
    }

  void AmfOperations::assignWork(ServiceUnit* su, ServiceInstance* si, HighAvailabilityState state,Wakeable& w)
    {
    SAFplus::Rpc::amfAppRpc::WorkOperationRequest request;
    ComponentServiceInstance* csi = nullptr;

    assert(su->assignedServiceInstances.contains(si) == false);  // We can only assign a particular SI to a particular SU once.

    su->assignedServiceInstances.push_back(si);
    if (state == HighAvailabilityState::active) su->numActiveServiceInstances.current.value+=1;
    if (state == HighAvailabilityState::standby) su->numStandbyServiceInstances.current.value+=1;

    SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   itcomp;
    SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   endcomp = su->components.value.end();
    for (itcomp = su->components.value.begin(); itcomp != endcomp; itcomp++)
      {

      Component* comp = dynamic_cast<Component*>(*itcomp);
      assert(comp);

      assert(comp->pendingOperation == PendingOperation::none);  // We should not be adding work to a component if something else is happening to it.

      Handle hdl;
      if (comp->capabilityModel != CapabilityModel::not_preinstantiable)  // If the component is preinstantiable, it better be instantiated by now (work would not be assigned if it wasn't)
        {
          try
            {
              hdl = name.getHandle(comp->name);
            }
          catch (SAFplus::NameException& n)
            {
              logCritical("OPS","SRT","Component [%s] is not registered in the name service.  Cannot control it.", comp->name.value.c_str());
              comp->lastError.value = "Component's name is not registered in the name service so address cannot be determined.";
              assert(0);
              break; // TODO: right now go to the next component, however assignment should not occur on ANY components if all components are not accessible. 
            }
        }

      // TODO: let's add an extension to SAF in the SI which basically just says "ignore CSIs" and/or "assign all components to the same CSI".  This makes the model simpler

      // Let's find a CSI that we can apply to this component
      SAFplus::MgtProvList<SAFplusAmf::ComponentServiceInstance*>::ContainerType::iterator itcsi;
      SAFplus::MgtProvList<SAFplusAmf::ComponentServiceInstance*>::ContainerType::iterator endcsi = si->componentServiceInstances.value.end();

      SAFplusAmf::ComponentServiceInstance* csi = NULL;
      for (itcsi = si->componentServiceInstances.value.begin(); itcsi != endcsi; itcsi++)
        {
        csi = *itcsi;
        if (!csi) continue;
        // TODO: figure out number of assignments allowed if (csi->getComponent()) continue;  // We can't assign a CSI to > 1 component.
        // TODO validate CSI dependencies are assigned
        break;  // We found one!
        }

      if (itcsi != endcsi)  // We found an assignable CSI and it is the variable "csi"
        {
        logInfo("OPS","SRT","Component [%s] handle [%" PRIx64 ":%" PRIx64 "] is being assigned [%s] work", comp->name.value.c_str(),hdl.id[0],hdl.id[1], c_str(state));
        if (comp->capabilityModel == CapabilityModel::not_preinstantiable)
          {
            if (state == HighAvailabilityState::active)
             start(comp,w);
          }
        else
          {
            // Mark this component with a pending operation.  This will be cleared in the WorkOperationTracker, or by timeout in auditDiscovery
            comp->pendingOperationExpiration.value.value = nowMs() + comp->timeouts.workAssignment;
            comp->pendingOperation = PendingOperation::workAssignment;

            request.set_componentname(comp->name.value.c_str());
            request.set_componenthandle((const char*) &hdl, sizeof(Handle)); // [libprotobuf ERROR google/protobuf/wire_format.cc:1053] String field contains invalid UTF-8 data when serializing a protocol buffer. Use the 'bytes' type if you intend to send raw bytes.
            request.set_operation((uint32_t)state);
            request.set_target(SA_AMF_CSI_ADD_ONE);
            if ((invocation & 0xFFFFFFFF) == 0xFFFFFFFF) invocation &= 0xFFFFFFFF00000000ULL;  // Don't let increasing invocation numbers overwrite the node or port... ofc this'll never happen 4 billion invocations? :-)
            request.set_invocation(invocation++);

            if (state == HighAvailabilityState::active)
              {
                csi->activeComponents.value.push_back(comp);  // Mark this CSI assigned to this component
              }
            else if (state == HighAvailabilityState::standby)
              {
                csi->standbyComponents.value.push_back(comp); // Mark this CSI assigned to this component
              }
            else if (state == HighAvailabilityState::idle)
              {
                assert(0);  // TODO (will this fn call work for work removal?
              }
            else if (state == HighAvailabilityState::quiescing)
              {
                assert(0);  // TODO (will this fn call work for work removal?
              }
          

            // Now I need to fill up the key/value pairs from the CSI
            request.clear_keyvaluepairs();
            SAFplus::MgtList<std::string>::Iterator it;
            for (it = csi->dataList.begin(); it != csi->dataList.end(); it++)
              {
                SAFplus::Rpc::amfAppRpc::KeyValuePairs* kvp = request.add_keyvaluepairs();
                assert(kvp);
                std::string val("val");
                //MgtObject *obj = it->second->getChildObject("val");
                MgtObject *obj2 = it->second;
                //MgtProv<std::string>* kv = dynamic_cast<MgtProv<std::string>*>(obj);
                SAFplusAmf::Data* kv2 =  dynamic_cast<SAFplusAmf::Data*>(obj2); 
                //kv->dbgDump();
                //obj2->dbgDump();
                //assert(kv);
                //kvp->set_thekey(kv->tag.c_str());  // it->first().c_str()
                //kvp->set_thevalue(kv->value.c_str());
                kvp->set_thekey(kv2->name.value.c_str());
                kvp->set_thevalue(kv2->val.value.c_str());
              }

            pendingWorkOperations[request.invocation()] = WorkOperationTracker(comp,csi,si,(uint32_t)state,SA_AMF_CSI_ADD_ONE);

            amfAppRpc->workOperation(hdl, &request);
          }

        reportChange();
        }
      else
        {
        logInfo("OPS","SRT","Component [%s] handle [%" PRIx64 ":%" PRIx64 "] cannot be assigned work.  No valid Component Service Instance.", comp->name.value.c_str(),hdl.id[0],hdl.id[1]);
        }

      }

    }

  void AmfOperations::stop(SAFplusAmf::Component* comp,Wakeable& w)
    {
      assert(0);
    }

  void AmfOperations::abort(SAFplusAmf::Component* comp,Wakeable& w)
    {
    Handle nodeHdl;
    try
      {
      nodeHdl = name.getHandle(comp->serviceUnit.value->node.value->name);
      }
    catch (SAFplus::NameException& n)
      {
      logCritical("OPS","SRT","AMF Entity [%s] is not registered in the name service.  Cannot start processes on it.", comp->serviceUnit.value->node.value->name.value.c_str());
      comp->lastError.value = "Component's node is not registered in the name service so address cannot be determined.";
      if (&w) w.wake(1,(void*)comp);
      return;
      }

    if (nodeHdl == nodeHandle)  // Handle this request locally.  This is an optimization.  The RPC call will also work locally.
      {
        Process p(comp->processId.value);
        p.signal(SIGTERM);
      }
    else  
      {
        assert(0);  // TODO implement process stop RPC
      }
    }

  void AmfOperations::start(SAFplusAmf::Component* comp,Wakeable& w)
    {
    assert(comp);
    comp->numInstantiationAttempts.value++;
    comp->lastInstantiation.value.value = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    if (!comp->serviceUnit)
      {
      clDbgCodeError(1,("Can't start disconnected comp"));  // Because we don't know what node to start it on...
      comp->lastError.value = "Can't start disconnected component.";
      comp->operState = false;  // A configuration error isn't going to heal itself -- component needs manual intervention then repair
      if (&w) w.wake(1,(void*)comp);
      return;
      }
    if (!comp->serviceUnit.value->node)
      {
      clDbgCodeError(1,("Can't start disconnected comp"));
      comp->lastError.value = "Can't start disconnected component.";
      comp->operState = false;  // A configuration error isn't going to heal itself -- component needs manual intervention then repair
      if (&w) w.wake(1,(void*)comp);
      return;
      }

    Handle nodeHdl;
    try
      {
      nodeHdl = name.getHandle(comp->serviceUnit.value->node.value->name);
      }
    catch (SAFplus::NameException& n)
      {
      logCritical("OPS","SRT","AMF Entity [%s] is not registered in the name service.  Cannot start processes on it.", comp->serviceUnit.value->node.value->name.value.c_str());
      comp->lastError.value = "Component's node is not registered in the name service so address cannot be determined.";
      if (&w) w.wake(1,(void*)comp);
      return;
      }

    SAFplusAmf::Instantiate* inst = comp->getInstantiate();
    //assert(inst);
    if (!inst)  // Bad configuration
      {
      logWarning("OPS","SRT","Component [%s] has improper configuration (no instantiation information). Cannot start", comp->name.value.c_str());
      comp->operState = false;  // A configuration error isn't going to heal itself -- component needs manual intervention then repair
      comp->lastError.value = "No instantiation information";
      if (&w) w.wake(1,(void*)comp);
      return;
      }

    if ( comp->capabilityModel == CapabilityModel::not_preinstantiable)
        {
        comp->presenceState.value  = PresenceState::instantiated;
        // TODO: add the WORK key/value pairs to the environment variables
        }
    else 
        comp->presenceState.value  = PresenceState::instantiating;

    if (nodeHdl == nodeHandle)  // Handle this request locally.  This is an optimization.  The RPC call will also work locally.
      {
      std::vector<std::string> newEnv = comp->commandEnvironment.value;
      std::string strCompName("ASP_COMPNAME=");
      std::string strNodeName("ASP_NODENAME=");
      std::string strNodeAddr("ASP_NODEADDR=");
      std::string strPort("SAFPLUS_RECOMMENDED_MSG_PORT=");

      strCompName.append(comp->name);
      strNodeName.append(SAFplus::ASP_NODENAME);
      strNodeAddr.append(std::to_string(SAFplus::ASP_NODEADDR));
      int port = portAllocator.allocPort();
      strPort.append(std::to_string(port));
      newEnv.push_back(strCompName);
      newEnv.push_back(strNodeName);
      newEnv.push_back(strNodeAddr);
      newEnv.push_back(strPort);

      Process p = executeProgram(inst->command.value, newEnv,Process::InheritEnvironment);
      portAllocator.assignPort(port, p.pid);
      comp->processId.value = p.pid;

      // I need to set the handle because the process itself will not do so.
      if ( comp->capabilityModel == CapabilityModel::not_preinstantiable)
        {
          Handle handle=getProcessHandle(p.pid);
          name.set(comp->name, handle, NameRegistrar::MODE_NO_CHANGE);        
          comp->presenceState.value  = PresenceState::instantiated;    // There are no transitional states in the not_preinstantiable (not SAF aware) case
        }

      logInfo("OPS","SRT","Launching Component [%s] as [%s] locally with process id [%d]", comp->name.value.c_str(),inst->command.value.c_str(),p.pid);


      if (&w) w.wake(1,(void*)comp);
      }
    else  // RPC call
      {
      logInfo("OP","CMP","Request launch component [%s] as [%s] on node [%s]", comp->name.value.c_str(),inst->command.value.c_str(),comp->serviceUnit.value->node.value->name.value.c_str());

#if 0
      SAFplus::Rpc::RpcChannel channel(&safplusMsgServer, nodeHdl);
      channel->setMsgType(AMF_REQ_HANDLER_TYPE, AMF_REPLY_HANDLER_TYPE);
      amfRpc_Stub service(channel);
      StartComponentRequest req;
      StartCompResp respData(w,comp);
      service.startComponent(INVALID_HDL, &req, &respData.response, respData);  // TODO: what happens in a RPC call timeout?
#endif
      StartComponentRequest req;
      req.set_name(comp->name.value.c_str());
      req.set_command(inst->command.value.c_str());
      StartCompResp* resp = new StartCompResp(&w,comp);
      amfInternalRpc->startComponent(nodeHdl,&req, &resp->response,*resp);
      }
    reportChange();
    }

  void AmfOperations::start(SAFplusAmf::ServiceGroup* sg,Wakeable& w)
    {
    clDbgNotImplemented();
    // TODO: Service Group startup needs to be done in a manner consistent with the Redundancy Policy.
#if 0
    SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator itsu;
    SAFplus::MgtProvList<SAFplusAmf::ServiceUnit*>::ContainerType::iterator endsu = sg->serviceUnits.value.end();
    for (itsu = sg->serviceUnits.value.begin(); itsu != endsu; itsu++)
      {
      //ServiceUnit* su = dynamic_cast<ServiceUnit*>(itsu->second);
      ServiceUnit* su = dynamic_cast<ServiceUnit*>(*itsu);
      const std::string& suName = su->name;
      logInfo("N+M","AUDIT","Auditing su %s", suName.c_str());

      SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   itcomp;
      SAFplus::MgtProvList<SAFplusAmf::Component*>::ContainerType::iterator   endcomp = su->components.value.end();
      for (itcomp = su->components.value.begin(); itcomp != endcomp; itcomp++)
        {
        Component* comp = dynamic_cast<Component*>(*itcomp);
        SAFplusAmf::AdministrativeState eas = effectiveAdminState(comp);

        if ((comp->operState == false)&&(eas != SAFplusAmf::AdministrativeState::off))
          {
          logError("N+M","AUDIT","Component %s should be on but is not instantiated", comp->name.c_str());
          }
        if ((comp->operState)&&(eas == SAFplusAmf::AdministrativeState::off))
          {
          logError("N+M","AUDIT","Component %s should be off but is instantiated", comp->name.c_str());
          }
        }
      }
#endif
    }

  };
