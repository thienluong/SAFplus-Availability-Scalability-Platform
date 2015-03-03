/* This file contains configurable defaults for the entire set of SAFplus services */
#pragma once
#ifndef CL_CUSTOMIZATION_HXX
#define CL_CUSTOMIZATION_HXX
/* Configuration parameters that are part of the API */

#define AMF_GRP_NODE_REPRESENTATIVE // Indicates that the AMF will act as the one-per-node GRP membership shared memory maintainer, rather than a standalone safplus_group process

// Define this if you want the logging system to be cluster wide.
// Comment it out to make the logging system local to the node.
#define SAFPLUS_CLUSTERWIDE_LOG

namespace SAFplus
  {
    enum
    {
    Log2MaxNodes = 10,  // 2^10 = 1024 total nodes.
    MaxNodes = (1<<Log2MaxNodes)
    };

  /* Messaging */
  enum
    {
    MsgAppMaxThreads = 2,   //? Default maximum number of message processing threads for applications
    MsgAppQueueLen   = 25   //? Default maximum queue size for message processing
    };

  };


/* Configuration parameters that are used internally */
namespace SAFplusI
  {
  /* THREADS */
  enum
    {
    ThreadPoolTimerInterval = 60, //? Seconds between checks that threads are not hung
    ThreadPoolIdleTimeLimit = 50, //? If a thread has had no tasks for this long, let it quit
    };

  /* LOGGING */
  enum
    {
    LogDefaultFileBufferSize = 16*1024,
    LogDefaultMessageBufferSize = 16*1024,
    };

  /* GROUP */
  enum
    {
    GroupSharedMemSize = 4 * 1024*1024,
    GroupMax           = 1024,  // Maximum number of groups
    GroupMaxMembers    = 1024,   // Maximum number of members in a group
    GroupElectionTimeMs = 5000  // Default Group election time in milliseconds
    };

  /* CHECKPOINT */
  enum
    {
    CkptMinSize = 4*1024,
    CkptDefaultSize = 64*1024,

    CkptMinRows = 2,
    CkptDefaultRows = 256,

    CkptSyncMsgStride = 128,   // Checkpoint sync messages will be either < this length OR have only one record.  That is, if a record is > this amount the message can be bigger.

    };

  /* AMF */
  enum
    {
    AmfMaxComponentServiceInstanceKeyValuePairs = 1024
    };


  /* UDP message transport */
  enum
    {
    UdpTransportMaxMsgSize = 65507,  // 65,535 - 8 byte UDP header - 20 byte IP header  (http://en.wikipedia.org/wiki/User_Datagram_Protocol).  This is defined here so you can artifically limit the packet size.
    UdpTransportNumPorts = 2048,  // Limit the ports to a range for no particular reason
    UdpTransportStartPort = 7000,  // Pick a random spot in the UDP port range so our ports don't overlap common services
    UdpTransportMaxMsg = 64,
    UdpTransportMaxFragments = 256,
    };

  extern const char* defaultMsgTransport;  //? Specifies the default messaging transport plugin filename.  This can be overridden by an environment variable.

  };

#endif

