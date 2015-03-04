#include <clFaultApi.hxx>
#include <clGlobals.hxx>
#include <clIocPortList.hxx>
#include <clSafplusMsgServer.hxx>
#include <string>

using namespace std;
using namespace SAFplus;

//ClUint32T clAspLocalId = 0x1;
void tressTest(int eventNum);
void deRegisterTest();
static unsigned int MAX_MSGS=25;
static unsigned int MAX_HANDLER_THREADS=2;
ClBoolT   gIsNodeRepresentative = false;
SafplusInitializationConfiguration sic;
SAFplus::Handle faultEntityHandle(PointerHandle, 0x9876, 5454);
SAFplus::Handle me;
Fault fc;

void testAllFeature();
int main(int argc, char* argv[])
{
  logEchoToFd = 1;  // echo logs to stdout for debugging
  logSeverity = LOG_SEV_MAX;
  sic.iocPort     = 50;
  safplusInitialize(SAFplus::LibDep::IOC | SAFplus::LibDep::LOG |SAFplus::LibDep::MSG ,sic);

  logInfo("FLT","CLT","********************Start msg server********************");
  safplusMsgServer.Start();
  logInfo("FLT","CLT","********************Initial fault lib********************");
  faultInitialize();
  me = Handle::create();
  fc = Fault();
  Handle server = getProcessHandle(SAFplusI::FLT_IOC_PORT,SAFplus::ASP_NODEADDR);
  logInfo("FLT","CLT","********************Initial fault client*********************");
  fc.init(me,server,sic.iocPort,BLOCK);
  fc.registerFault();
  testAllFeature();
  tressTest(20);
  sleep(1);
  deRegisterTest();
  while(1)
  {
	  sleep(10000);
  }
  return 0;

}

void testAllFeature()
{

  sleep(10);
  FaultState state = fc.getFaultState(me);
  logInfo("FLT","CLT","********************Get current fault state in shared memory [%s]********************", strFaultEntityState[int(state)]);
  // Register other fault entity
  logInfo("FLT","CLT","********************Register other fault entity********************");
  fc.registerFault(faultEntityHandle,FaultState::STATE_DOWN);
  sleep(10);
  state = fc.getFaultState(faultEntityHandle);
  logInfo("FLT","CLT","********************Get current fault state in shared memory [%s]********************", strFaultEntityState[int(state)]);
  sleep(10);
  logInfo("FLT","CLT","********************Update other fault entity********************");
  fc.registerFault(faultEntityHandle,FaultState::STATE_UP);
  sleep(10);
  state = fc.getFaultState(faultEntityHandle);
  logInfo("FLT","CLT","********************Get current fault state after updated in shared memory [%s]********************", strFaultEntityState[int(state)]);
  sleep(10);
  FaultEventData faultData;
  faultData.alarmState=SAFplusI::AlarmStateT::ALARM_STATE_INVALID;
  faultData.category=SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_COMMUNICATIONS;
  faultData.cause=SAFplusI::AlarmProbableCauseT::ALARM_PROB_CAUSE_PROCESSOR_PROBLEM;
  faultData.severity=SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_MINOR;

  state = fc.getFaultState(me);
  logInfo("FLT","CLT","********************Get current fault state in shared memory [%s]********************", strFaultEntityState[int(state)]);

  logInfo("FLT","CLT","********************Send fault event to local fault server********************");
  fc.notify(faultData,SAFplus::FaultPolicy::Custom);
  sleep(10);
  logInfo("FLT","CLT","********************Send fault event to active  fault server********************");
  fc.notifytoActive(faultData,SAFplus::FaultPolicy::AMF);
  sleep(10);
  logInfo("FLT","CLT","********************Get current fault state in shared memory [%s]********************", strFaultEntityState[int(state)]);
  state = fc.getFaultState(me);


  logInfo("FLT","CLT","********************Send fault event to local fault server********************");
  fc.notify(faultEntityHandle,faultData,SAFplus::FaultPolicy::Custom);
  sleep(10);
  logInfo("FLT","CLT","********************Send fault event to active  fault server********************");
  fc.notifytoActive(faultEntityHandle,faultData,SAFplus::FaultPolicy::AMF);
  logInfo("FLT","CLT","********************Get current fault state in shared memory [%s]********************", strFaultEntityState[int(state)]);
  state = fc.getFaultState(faultEntityHandle);


}
//void test()
//{
//	while (IsOk(fc.(destination)))
//	{
//		bool result = sendMsgGetReply(destination);
//		if (!result)
//		{ fc.notify(FaultData(...), destination)  }
//	}
//}

void tressTest(int eventNum)
{
	for (int i = 0; i < eventNum; i ++)
	{
		FaultEventData faultData;
		faultData.alarmState=SAFplusI::AlarmStateT::ALARM_STATE_INVALID;
		faultData.category=SAFplusI::AlarmCategoryTypeT::ALARM_CATEGORY_COMMUNICATIONS;
		faultData.cause=SAFplusI::AlarmProbableCauseT::ALARM_PROB_CAUSE_PROCESSOR_PROBLEM;
		faultData.severity=SAFplusI::AlarmSeverityTypeT::ALARM_SEVERITY_MINOR;
		fc.notify(faultData,FaultPolicy::AMF);
		sleep(1);
	}
}

void deRegisterTest()
{
	  logInfo("FLT","CLT","********************Deregister fault entity********************");
	  fc.deRegister(faultEntityHandle);
	  logInfo("FLT","CLT","********************Deregister fault client********************");
	  fc.deRegister();
}
