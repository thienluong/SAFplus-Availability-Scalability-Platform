/*
 * Copyright (C) 2002-2014 OpenClovis Solutions Inc.  All Rights Reserved.
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
 * For more  information, see  the file  COPYING provided with this
 * material.
 */

#include <iostream>
#include <sstream>
#include <clLogApi.hxx>
#include <clGlobals.hxx>
#include <clIocApiExt.h>
#include <clOsalApi.h>
#include "clMsgApi.hxx"
#include "clRpcChannel.hxx"
#include "rpcTest.hxx"
#include "RpcWakeable.hxx"

using namespace std;
using namespace SAFplus;
using namespace google::protobuf;

//Auto scanning
#define IOC_PORT 0
#define IOC_PORT_SERVER 65

ClUint32T clAspLocalId = 0x1;
ClBoolT gIsNodeRepresentative = CL_FALSE;

int main(void)
  {
    ClIocAddressT iocDest;

    logInitialize();
    logEchoToFd = 1;  // echo logs to stdout for debugging
    logSeverity = LOG_SEV_MAX;

    utilsInitialize();

    ClRcT rc;
    // initialize SAFplus6 libraries
    if ((rc = clOsalInitialize(NULL)) != CL_OK || (rc = clHeapInit()) != CL_OK || (rc = clTimerInitialize(NULL)) != CL_OK || (rc = clBufferInitialize(NULL)) != CL_OK)
      {
      assert(0);
      }

    rc = clIocLibInitialize(NULL);

    iocDest.iocPhyAddress.nodeAddress = 1;
    iocDest.iocPhyAddress.portId = IOC_PORT_SERVER;
    char helloMsg[] = "Hello world ";

    SAFplus::Rpc::rpcTest::TestGetRpcMethodRequest request1;
    SAFplus::Rpc::rpcTest::TestGetRpcMethodResponse res1;

    request1.set_name("myNameRequest1");

    SAFplus::Rpc::rpcTest::TestGetRpcMethod2Request request2;
    SAFplus::Rpc::rpcTest::TestGetRpcMethod2Response res2;

    request2.set_name("myNameRequest2");

    SAFplus::Rpc::rpcTest::TestGetRpcMethod3Request request3;
    SAFplus::Rpc::rpcTest::TestGetRpcMethod3Response res3;

    request3.set_name("myNameRequest3");
    /*
     * ??? msgClient or safplusMsgServer
     */
    SafplusMsgServer msgClient(IOC_PORT);

    SAFplus::Rpc::RpcChannel * channel = new SAFplus::Rpc::RpcChannel(&msgClient, iocDest);
    channel->setMsgType(100, 101);

    SAFplus::Rpc::rpcTest::rpcTest *service = new SAFplus::Rpc::rpcTest::rpcTest::Stub(channel);

    msgClient.Start();

    //Test RPC
    //Loop forever
    while (1)
      {
        Rpc::RpcWakeable wakeable1(1);
        Rpc::RpcWakeable wakeable2(2);
        Rpc::RpcWakeable wakeable3(3);

        SAFplus::Handle hdl(TransientHandle,1,IOC_PORT_SERVER,1);
        ClIocAddressT addr = getAddress(hdl);

        service->testGetRpcMethod(hdl, &request1, &res1, wakeable1);
        service->testGetRpcMethod2(hdl, &request2, &res2, wakeable2);
        service->testGetRpcMethod3(hdl, &request3, &res3, wakeable3);

        sleep(1);
      }

  }
