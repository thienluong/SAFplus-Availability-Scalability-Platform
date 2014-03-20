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

#include <clIocProtocols.h>
#include "clSafplusMsgServer.hxx"
#include "MsgReplyHandler.hxx"


namespace SAFplus
{
    SAFplus::SafplusMsgServer::SafplusMsgServer(ClWordT port, ClWordT maxPendingMsgs, ClWordT maxHandlerThreads, Options flags) :
                    MsgServer(port, maxPendingMsgs, maxHandlerThreads, flags)
    {
        MsgHandler *replyHandler = new MsgReplyHandler();
        this->RegisterHandler(CL_IOC_SAF_MSG_REPLY_PROTO, replyHandler, &msgReply);
    }

    void
    SAFplus::SafplusMsgServer::RegisterHandler(ClWordT type, MsgHandler *handler, ClPtrT cookie)
    {
        SAFplus::MsgServer::RegisterHandler(type, handler, cookie);
    }

    void
    SAFplus::SafplusMsgServer::RemoveHandler(ClWordT type)
    {
        SAFplus::MsgServer::RemoveHandler(type);
    }

    MsgReply *SafplusMsgServer::SendReply(ClIocAddressT destination, void* buffer, ClWordT length, ClWordT msgtype)
    {
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(msgSendReplyMutex);
        memset(&msgReply, 0, sizeof(MsgReply));
        SendMsg(destination, buffer, length, msgtype);
        /**
         * Sending Sync type, need to start listen on replying to wake
         */
        Start();
        /**
         * Wait on condition
         */
        condMsgSendReplyMutex.wait(lock);
        return &msgReply;
    }

}