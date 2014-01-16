/*
 * Copyright (C) 2002-2013 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 * 
 * The source code for  this program is not published  or otherwise 
 * divested of  its trade secrets, irrespective  of  what  has been 
 * deposited with the U.S. Copyright office.
 * 
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * This file is autogenerated by OpenClovis IDE, 
 */

/******************************************************************************
 * Include files needed to compile this file
 *****************************************************************************/

/* POSIX Includes */
#include <assert.h>
#include <errno.h>

/* Basic SAFplus Includes */
#include <clCommon.h>

/* SAFplus Client Includes */
#include <clDebugApi.h>
#include <clLogApi.h>
#include <clCpmApi.h>
#include <saAmf.h>
#include <saAis.h>
#include <saEvt.h>
#include <clEventApi.h>
#include <clEventExtApi.h>



/* SAFplus Client Includes */
#include <clHandleApi.h>

/* Local function declarations */
ClRcT evtSub(void);


/* The application should fill these functions */
void safTerminate(SaInvocationT invocation, const SaNameT *compName);
void safAssignWork(SaInvocationT       invocation,
                   const SaNameT       *compName,
                   SaAmfHAStateT       haState,
                   SaAmfCSIDescriptorT csiDescriptor);
void safRemoveWork(SaInvocationT  invocation,
                   const SaNameT  *compName,
                   const SaNameT  *csiName,
                   SaAmfCSIFlagsT csiFlags);

/* Utility functions */
void initializeAmf(void);
void dispatchLoop(void);
void printCSI(SaAmfCSIDescriptorT csiDescriptor, SaAmfHAStateT haState);
int  errorExit(SaAisErrorT rc);
SaAisErrorT openPublisherChannel();

#define EVENT_CHANNEL_NAME "TestEventChannel1"
#define EVENT_CHANNEL_PUB_NAME "TestEventChannel"
#define PUBLISHER_NAME "SCComponent"
SaNameT                 evtChannelName;
//handle for subscribe event
SaEvtChannelHandleT     evtChannelHandle = 0;
SaEvtHandleT            evtHandle;

/******************************************************************************
 * Optional Features
 *****************************************************************************/

/* A wrapper for our logging. You can change "MAI" and CL_LOG_CONTEXT_UNSPECIFIED
   to another 3 letter acronym meaningful more meaningful to this module.
 */

#define clprintf(severity, ...)   clAppLog(CL_LOG_HANDLE_APP, severity, 10, "MAI", CL_LOG_CONTEXT_UNSPECIFIED,__VA_ARGS__)

/******************************************************************************
 * Global Variables.
 *****************************************************************************/

static char             appname[80];

/* The process ID is stored in this variable.  This is only used in our logging. */
pid_t        mypid;

/* Access to the SAF AMF framework occurs through this handle */
SaAmfHandleT amfHandle;

/* This process's SAF name */
SaNameT      appName = {0};


ClBoolT unblockNow = CL_FALSE;

/* Declare other global variables here. */


/******************************************************************************
 * Application Life Cycle Management Functions
 *****************************************************************************/


int main(int argc, char *argv[])
{
    SaAisErrorT rc = SA_AIS_OK;

    /* Connect to the SAF cluster */
    initializeAmf();


    /* Do the application specific initialization here. */
#define min(x,y) ((x < y)? x: y)

    strncpy(appname, (char*)appName.value, min(sizeof appname, appName.length));
    appname[min(sizeof appname - 1, appName.length)] = 0;
    clprintf(CL_LOG_SEV_INFO, "Instantiated as component instance %s.\n", appName.value);

    if (evtSub() != CL_OK)
    {
        CL_ASSERT(0);
    }
    
    CL_ASSERT(openPublisherChannel()==SA_AIS_OK);

    dispatchLoop();
    
    /* Do the application specific finalization here. */

    /* Now finalize my connection with the SAF cluster */
    if((rc = saAmfFinalize(amfHandle)) != SA_AIS_OK)
      clprintf (CL_LOG_SEV_ERROR, "AMF finalization error[0x%X]", rc);
    else
      clprintf (CL_LOG_SEV_INFO, "AMF Finalized");   

    return 0;
}


/*
 * clCompAppTerminate
 * ------------------
 * This function is invoked when the application is to be terminated.
 */

void safTerminate(SaInvocationT invocation, const SaNameT *compName)
{
    SaAisErrorT rc = SA_AIS_OK;

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Terminating\n", compName->length, compName->value, mypid);


    /*
     * Unregister with AMF and respond to AMF saying whether the
     * termination was successful or not.
     */
    if ( (rc = saAmfComponentUnregister(amfHandle, compName, NULL)) != SA_AIS_OK)
    {
        clprintf (CL_LOG_SEV_ERROR, "Component [%.*s] : PID [%d]. Unregister failed with error [0x%x]\n",
                  compName->length, compName->value, mypid, rc);
        return;        
    }

    /* Ok tell SAFplus that we handled it properly */
    saAmfResponse(amfHandle, invocation, SA_AIS_OK);

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Terminated\n",
              compName->length, compName->value, mypid);

    unblockNow = CL_TRUE;
}

/******************************************************************************
 * Application Work Assignment Functions
 *****************************************************************************/

/*
 * safAssignWork
 * ------------------
 * This function is invoked when a CSI assignment is made or the state
 * of a CSI is changed.
 */

void safAssignWork(SaInvocationT       invocation,
                   const SaNameT       *compName,
                   SaAmfHAStateT       haState,
                   SaAmfCSIDescriptorT csiDescriptor)
{
    /* Print information about the CSI Set */

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. CSI Set Received\n", 
              compName->length, compName->value, mypid);

    printCSI(csiDescriptor, haState);

    /*
     * Take appropriate action based on state
     */

    switch ( haState )
    {
        /* AMF asks this process to take the standby HA state for the work
           described in the csiDescriptor variable */
        case SA_AMF_HA_ACTIVE:
        {
            /* Typically you would spawn a thread here to initiate active 
               processing of the work. */


            /* The AMF times the interval between the assignment and acceptance
               of the work (the time interval is configurable).
               So it is important to call this saAmfResponse function ASAP.
             */
            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        /* AMF asks this process to take the standby HA state for the work
           described in the csiDescriptor variable */
        case SA_AMF_HA_STANDBY:
        {
            /* If your standby has ongoing maintenance, you would spawn a thread
               here to do it. */

            /* The AMF times the interval between the assignment and acceptance
               of the work (the time interval is configurable).
               So it is important to call this saAmfResponse function ASAP.
             */
            saAmfResponse(amfHandle, invocation, SA_AIS_OK);  
            break;
        }

        case SA_AMF_HA_QUIESCED:
        {
            /*
             * AMF has requested application to quiesce the CSI currently
             * assigned the active or quiescing HA state. The application 
             * must stop work associated with the CSI immediately.
             */

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_QUIESCING:
        {
            /*
             * AMF has requested application to quiesce the CSI currently
             * assigned the active HA state. The application must stop work
             * associated with the CSI gracefully and not accept any new
             * workloads while the work is being terminated.
             */

            /* There are two typical cases for quiescing.  Chooose one!
               CASE 1: Its possible to quiesce rapidly within this thread context */
            if (1)
              {
              /* App code here: Now finish your work and cleanly stop the work*/
            
              /* Call saAmfCSIQuiescingComplete when stopping the work is done */
              saAmfCSIQuiescingComplete(amfHandle, invocation, SA_AIS_OK);
              }
            else
              {
              /* CASE 2: You can't quiesce within this thread context or quiesce
               rapidly. */

              /* Respond immediately to the quiescing request */
              saAmfResponse(amfHandle, invocation, SA_AIS_OK);

              /* App code here: Signal or spawn a thread to cleanly stop the work*/
              /* When that thread is done, it should call:
                 saAmfCSIQuiescingComplete(amfHandle, invocation, SA_AIS_OK);
              */
              }

            break;
        }

        default:
        {
            assert(0);
            break;
        }
    }

    return;
}

/*
 * safRemoveWork
 * ---------------------
 * This function is invoked when a CSI assignment is to be removed.
 */

void safRemoveWork(SaInvocationT  invocation,
                   const SaNameT  *compName,
                   const SaNameT  *csiName,
                   SaAmfCSIFlagsT csiFlags)
{
    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. CSI Remove Received\n", 
              compName->length, compName->value, mypid);

    clprintf (CL_LOG_SEV_INFO, "   CSI                     : %.*s\n", csiName->length, csiName->value);
    clprintf (CL_LOG_SEV_INFO, "   CSI Flags               : 0x%d\n", csiFlags);

    /*
     * Add application specific logic for removing the work for this CSI.
     */

    saAmfResponse(amfHandle, invocation, SA_AIS_OK);
}

/******************************************************************************
 * Utility functions 
 *****************************************************************************/
/* This simple helper function just prints an error and quits */
int errorExit(SaAisErrorT rc)
{        
    clprintf (CL_LOG_SEV_ERROR, "Component [%.*s] : PID [%d]. Initialization error [0x%x]\n",
              appName.length, appName.value, mypid, rc);
    exit(-1);
    return -1;
}

void initializeAmf(void)
{
    SaAmfCallbacksT     callbacks;
    SaVersionT          version;
    ClIocPortT          iocPort;
    SaAisErrorT         rc = SA_AIS_OK;

    /* Get the pid for the process and store it in global variable. */
    mypid = getpid();

    /* SAFplus is fully API compatible with SA-Forum (SAF) definitions.

       This optional call customizes OpenClovis SAFplus Platform extensions
       to the basic SAF services (to use, you would define the parameters as globals).  
       
       If this call is removed, standard SAF services will work just fine. */

    /* clAppConfigure(&clEoConfig,clEoBasicLibs,clEoClientLibs); */

    
    /*
     * Initialize and register with SAFplus AMF. 'version' specifies the
     * version of AMF with which this application would like to
     * interface. 'callbacks' is used to register the callbacks this
     * component expects to receive.
     */
    version.releaseCode  = 'B';
    version.majorVersion = 01;
    version.minorVersion = 01;
    
    callbacks.saAmfHealthcheckCallback          = NULL; /* rarely necessary because SAFplus monitors the process */
    callbacks.saAmfComponentTerminateCallback   = safTerminate;
    callbacks.saAmfCSISetCallback               = safAssignWork;
    callbacks.saAmfCSIRemoveCallback            = safRemoveWork;
    callbacks.saAmfProtectionGroupTrackCallback = NULL;
        
    /* Initialize AMF client library. */
    if ( (rc = saAmfInitialize(&amfHandle, &callbacks, &version)) != SA_AIS_OK)
        errorExit(rc);

    /*
     * Now register the component with AMF. At this point it is
     * ready to provide service, i.e. take work assignments.
     */

    if ( (rc = saAmfComponentNameGet(amfHandle, &appName)) != SA_AIS_OK) 
        errorExit(rc);
    if ( (rc = saAmfComponentRegister(amfHandle, &appName, NULL)) != SA_AIS_OK) 
        errorExit(rc);

    /*
     * Print out standard information for this component.
     */

    clEoMyEoIocPortGet(&iocPort);
    
    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Initializing\n", appName.length, appName.value, mypid);
    clprintf (CL_LOG_SEV_INFO, "   IOC Address             : 0x%x\n", clIocLocalAddressGet());
    clprintf (CL_LOG_SEV_INFO, "   IOC Port                : 0x%x\n", iocPort);    
}

static void appEventCallback( SaEvtSubscriptionIdT	subscriptionId, SaEvtEventHandleT     eventHandle, SaSizeT eventDataSize)
{
    clprintf (CL_LOG_SEV_INFO,"Received event from external app");
    SaAisErrorT  saRc = SA_AIS_OK;
    static ClPtrT   resTest = 0;
    static ClSizeT  resSize = 0;
    if (resTest != 0)
    {
        // Maybe try to save the previously allocated buffer if it's big
        // enough to hold the new event message.
        clHeapFree((char *)resTest);
        resTest = 0;
        resSize = 0;
    }
    resTest = clHeapAllocate(eventDataSize + 1);
    if (resTest == 0)
    {
        clprintf(CL_LOG_SEV_ERROR,"Failed to allocate space for event");
        return;
    }
    
    *(((char *)resTest) + eventDataSize) = 0;
    resSize = eventDataSize;
    saRc = saEvtEventDataGet(eventHandle, resTest, &resSize);
    if (saRc!= SA_AIS_OK)
    {
        clprintf(CL_LOG_SEV_ERROR,"Failed to get event data [0x%x]\n",saRc);
    }
    clprintf (CL_LOG_SEV_INFO,"Received event from external app: %s\n", (char *)resTest);
    return;
}

SaEvtChannelHandleT pubChannelHandle = 0;
SaEvtEventHandleT eventForPub;

void publishEvent(void)
{
    SaAisErrorT  saRc = SA_AIS_OK;
    ClEventIdT      eventId         = 0;
    const char* evtcontents = "Event from SCComponent application";
    clprintf(CL_LOG_SEV_INFO,"publishing event [%s] to [%s]", evtcontents, EVENT_CHANNEL_PUB_NAME);
    saRc = saEvtEventPublish(eventForPub, (void *)evtcontents, strlen(evtcontents)+1, &eventId);
    //CL_ASSERT(saRc == SA_AIS_OK);
}


SaAisErrorT openPublisherChannel()
{
    SaNameT evtChannelName;
    SaNameT myName;
    SaAisErrorT  rc = SA_AIS_OK;

    saNameSet(&evtChannelName,EVENT_CHANNEL_PUB_NAME);
    saNameSet(&myName,PUBLISHER_NAME);
    
    printf("Opening event publisher to channel [%s]\n",evtChannelName.value);
    rc = saEvtChannelOpen (evtHandle, &evtChannelName, (SA_EVT_CHANNEL_PUBLISHER | SA_EVT_CHANNEL_CREATE), (ClTimeT)SA_TIME_END, &pubChannelHandle);
    if (rc != SA_AIS_OK)
    {
        printf( "Failed to open event channel [0x%x]\n",rc);
        return rc;
    }

    rc = saEvtEventAllocate(pubChannelHandle, &eventForPub);
    if (rc != SA_AIS_OK)
    {
        printf( "Failed to cllocate event [0x%x]\n",rc);
        return rc;
    }

    rc = saEvtEventAttributesSet(eventForPub, NULL, 1, 0, &myName);
    if (rc != SA_AIS_OK)
    {
        printf( "Failed to set event attributes [0x%x]\n",rc);
        return rc;
    }
    return rc;
}




ClRcT evtSub(void)
{
    ClRcT rc = CL_OK;
        //  Open a subscribe event channel and start receiving events.
    clprintf(CL_LOG_SEV_INFO,"Open Event subscription to %s", EVENT_CHANNEL_NAME);        
    const SaEvtCallbacksT evtCallbacks =
    {
        NULL,
        appEventCallback
    };
    SaVersionT  evtVersion = CL_EVENT_VERSION;
    rc = saEvtInitialize(&evtHandle, &evtCallbacks, &evtVersion);
    if (rc != SA_AIS_OK)
    {
        printf("Failed to init event mechanism [0x%x]\n",rc);
        return rc;
    }

    saNameSet(&evtChannelName,EVENT_CHANNEL_NAME);
    rc = saEvtChannelOpen(evtHandle,&evtChannelName, (SA_EVT_CHANNEL_SUBSCRIBER | SA_EVT_CHANNEL_CREATE), (SaTimeT)SA_TIME_END, &evtChannelHandle);
    if (rc != SA_AIS_OK)
    {
        printf("Failure opening event channel[0x%x] at %ld\n", rc, time(0L));
        return rc;
        
    }
    rc = saEvtEventSubscribe(evtChannelHandle, NULL, 1);
    if (rc != SA_AIS_OK)
    {
        printf("Failed to subscribe to event channel [0x%x]\n", rc);
        return rc;
    }

    return CL_OK;
}


void dispatchLoop(void)
{        
  SaAisErrorT         rc = SA_AIS_OK;
  SaSelectionObjectT amf_dispatch_fd;
  //SaSelectionObjectT evt_dispatch_fd;
  int maxFd;
  fd_set read_fds;

  /* This boilerplate code includes an example of how to simultaneously
     dispatch for 2 services (in this case AMF and CKPT).  But since checkpoint
     is not initialized or used, it is commented out */
  /* SaSelectionObjectT ckpt_dispatch_fd; */

  /*
   * Get the AMF dispatch FD for the callbacks
   */
  if ( (rc = saAmfSelectionObjectGet(amfHandle, &amf_dispatch_fd)) != SA_AIS_OK)
    errorExit(rc);
  /* if ( (rc = saCkptSelectionObjectGet(ckptLibraryHandle, &ckpt_dispatch_fd)) != SA_AIS_OK)
       errorExit(rc); */
    
  maxFd = amf_dispatch_fd;  /* maxFd = max(amf_dispatch_fd,ckpt_dispatch_fd); */
  do
    {
      FD_ZERO(&read_fds);
      FD_SET(amf_dispatch_fd, &read_fds);
      /* FD_SET(ckpt_dispatch_fd, &read_fds); */
      struct timeval timeout;
      timeout.tv_sec = 1;
      timeout.tv_usec = 0;
      
      if( select(maxFd + 1, &read_fds, NULL, NULL, &timeout) < 0)
        {
          char errorStr[80];
          int err = errno;
          if (EINTR == err) continue;

          errorStr[0] = 0; /* just in case strerror does not fill it in */
          strerror_r(err, errorStr, 79);
          clprintf (CL_LOG_SEV_ERROR, "Error [%d] during dispatch loop select() call: [%s]",err,errorStr);
          break;
        }
      publishEvent();
      if (FD_ISSET(amf_dispatch_fd,&read_fds)) saAmfDispatch(amfHandle, SA_DISPATCH_ALL);
      /* if (FD_ISSET(ckpt_dispatch_fd,&read_fds)) saCkptDispatch(ckptLibraryHandle, SA_DISPATCH_ALL); */
    }while(!unblockNow);      
}


#define STRING_HA_STATE(S)                                                  \
(   ((S) == SA_AMF_HA_ACTIVE)             ? "Active" :                \
    ((S) == SA_AMF_HA_STANDBY)            ? "Standby" :               \
    ((S) == SA_AMF_HA_QUIESCED)           ? "Quiesced" :              \
    ((S) == SA_AMF_HA_QUIESCING)          ? "Quiescing" :             \
                                            "Unknown" )

#define STRING_CSI_FLAGS(S)                                                 \
(   ((S) == SA_AMF_CSI_ADD_ONE)            ? "Add One" :               \
    ((S) == SA_AMF_CSI_TARGET_ONE)         ? "Target One" :            \
    ((S) == SA_AMF_CSI_TARGET_ALL)         ? "Target All" :            \
                                                  "Unknown" )

/*
 * printCSI
 * --------------------
 * Print information received in a CSI set request.
 */

void printCSI(SaAmfCSIDescriptorT csiDescriptor, SaAmfHAStateT haState)
{
    clprintf (CL_LOG_SEV_INFO, "CSI Flags : [%s]", STRING_CSI_FLAGS(csiDescriptor.csiFlags));

    if (SA_AMF_CSI_TARGET_ALL != csiDescriptor.csiFlags)
    {
        clprintf (CL_LOG_SEV_INFO, "CSI Name : [%s]", csiDescriptor.csiName.value);
    }

    if (SA_AMF_CSI_ADD_ONE == csiDescriptor.csiFlags)
    {
        ClUint32T i = 0;
        
        clprintf (CL_LOG_SEV_INFO, "Name value pairs :");
        for (i = 0; i < csiDescriptor.csiAttr.number; i++)
        {
            clprintf (CL_LOG_SEV_INFO, "Name : [%s]",
                      csiDescriptor.csiAttr.
                      attr[i].attrName);
            clprintf (CL_LOG_SEV_INFO, "Value : [%s]",
                      csiDescriptor.csiAttr.
                      attr[i].attrValue);
        }
    }
    
    clprintf (CL_LOG_SEV_INFO, "HA state : [%s]", STRING_HA_STATE(haState));

    if (SA_AMF_HA_ACTIVE == haState)
    {
        clprintf (CL_LOG_SEV_INFO, "Active Descriptor :");
        clprintf (CL_LOG_SEV_INFO,
                  "Transition Descriptor : [%d]",
                  csiDescriptor.csiStateDescriptor.
                  activeDescriptor.transitionDescriptor);
        clprintf (CL_LOG_SEV_INFO,
                  "Active Component : [%s]",
                  csiDescriptor.csiStateDescriptor.
                  activeDescriptor.activeCompName.value);
    }
    else if (SA_AMF_HA_STANDBY == haState)
    {
        clprintf (CL_LOG_SEV_INFO, "Standby Descriptor :");
        clprintf (CL_LOG_SEV_INFO,
                  "Standby Rank : [%d]",
                  csiDescriptor.csiStateDescriptor.
                  standbyDescriptor.standbyRank);
        clprintf (CL_LOG_SEV_INFO, "Active Component : [%s]",
                  csiDescriptor.csiStateDescriptor.
                  standbyDescriptor.activeCompName.value);
    }
}
