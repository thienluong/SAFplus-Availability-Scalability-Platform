#ifndef _CKPT_EO_FUNC_TABLE_H_
#define _CKPT_EO_FUNC_TABLE_H_

#if !defined (__SERVER__) && !defined (__CLIENT__)
#error "This file should be included from server or client. Define __SERVER__ or __CLIENT__ if you are server or client and then recompile"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <clEoApi.h>


CL_EO_CALLBACK_TABLE_DECL(gCkptEoFuncList)[] =
{
	VSYM_VER(clCkptMasterCkptOpenServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 0)),
	VSYM_VER(clCkptMasterCkptCloseServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 1)),
	VSYM_VER(clCkptMasterCkptUnlinkServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 2)),
	VSYM_VER(_ckptCheckpointStatusGetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 3)),
	VSYM_VER(_ckptSectionCreateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 4)),
	VSYM_VER(_ckptSectionDeleteServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 5)),
	VSYM_VER(_ckptCheckpointWriteServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 6)),
	VSYM_VER(_ckptSectionOverwriteServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 7)),
	VSYM_VER(_ckptCheckpointReadServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 8)),
	VSYM_VER(clCkptSvrIterationInitializeServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 9)),
	VSYM_VER(_ckptIterationNextGetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 10)),
	VSYM_VER(clCkptMasterActiveReplicaSetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 11)),
	VSYM_VER(clCkptMasterActiveReplicaSetSwitchOverServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 12)),
	VSYM_VER(clCkptMasterCkptRetentionDurationSetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 13)),
	VSYM_VER(_ckptCheckpointSynchronizeServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 14)),
	VSYM_VER(_ckptSectionExpirationTimeSetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 15)),
	VSYM_VER(clCkptMasterActiveAddrGetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 16)),
	VSYM_VER(clCkptServerFinalizeServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 17)),
	VSYM_VER(clCkptDeputyMasterInfoSyncupServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 18)),
	VSYM_VER(clCkptLeaderAddrUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 19)),
	VSYM_VER(clCkptDeputyCkptCreateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 20)),
	VSYM_VER(clCkptDeputyCkptOpenServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 21)),
	VSYM_VER(clCkptDeputyCkptInfoUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 22)),
	VSYM_VER(clCkptDeputyCkptInfoUpdateServer, 5, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 22)),
	VSYM_VER(clCkptCreateInfoDeputyUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 23)),
	VSYM_VER(clCkptActiveCkptOpenServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 24)),
	VSYM_VER(clCkptReplicaNotifyServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 25)),
	VSYM_VER(clCkptDeputyReplicaListUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 26)),
	VSYM_VER(clCkptActiveCkptDeleteServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 27)),
	VSYM_VER(clCkptActiveAddrSetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 28)),
	VSYM_VER(clCkptActiveAddrInformServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 29)),
	VSYM_VER(clCkptDeputyDynamicUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 30)),
	VSYM_VER(clCkptDeputyPeerListUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 31)),
	VSYM_VER(clCkptAllReplicaPresenceListUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 32)),
	VSYM_VER(clCkptRemSvrWelcomeServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 33)),
	VSYM_VER(clCkptRemSvrByeServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 34)),
	VSYM_VER(clCkptNackReceiveServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 35)),
	VSYM_VER(clCkptMasterStatusInfoGetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 36)),
	VSYM_VER(clCkptRemSvrCkptInfoSyncServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 37)),
	VSYM_VER(clCkptRemSvrCkptInfoSyncServer, 5, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 37)),
	VSYM_VER(clCkptRemSvrCkptInfoGetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 38)),
	VSYM_VER(clCkptRemSvrCkptInfoGetServer, 5, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 38)),
	VSYM_VER(clCkptRemSvrSectionInfoUpdateServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 39)),
	VSYM_VER(clCkptRemSvrCkptDeleteServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 40)),
	VSYM_VER(clCkptRemSvrCkptWriteServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 41)),
	VSYM_VER(clCkptRemSvrSectionExpTimeSetServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 42)),
	VSYM_VER(clCkptCheckpointReplicaRemoveServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 43)),
	VSYM_VER(clCkptReplicaAppInfoNotifyServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 44)),
	VSYM_VER(clCkptActiveCallbackNotifyServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 45)),
	VSYM_VER(_ckptSectionCheckServer, 5, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 46)),
	VSYM_VER(_ckptCheckpointWriteVectorServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 47)),
	VSYM_VER(_ckptSectionOverwriteVectorServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 48)),
	VSYM_VER(clCkptRemSvrCkptWriteVectorServer, 4, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 49)),
	VSYM_VER(clCkptRemSvrWelcomeServer, 5, 1, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 50)),
	VSYM_VER(_ckptClientInfoGetServer, 6, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 51)),
	VSYM_VER(_ckptCheckpointReadSectionsServer, 6, 0, 0, CL_EO_GET_FULL_FN_NUM(CL_EO_NATIVE_COMPONENT_TABLE_ID, 52)),

};

CL_EO_CALLBACK_TABLE_LIST_DECL(gAspFuncTable, CkptEo) [] =
{
    CL_EO_CALLBACK_TABLE_LIST_DEF(CL_EO_NATIVE_COMPONENT_TABLE_ID, gCkptEoFuncList),
    CL_EO_CALLBACK_TABLE_LIST_DEF_NULL,
};


#ifdef __cplusplus
}
#endif
#endif /*_CKPT_EO_FUNC_TABLE_H_*/
