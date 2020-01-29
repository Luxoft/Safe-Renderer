#ifndef ODISESSION_H
#define ODISESSION_H

/******************************************************************************
**
**   File:        ODIComSession.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   Luxoft Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Render is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Render.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "MsgTransceiverTCP.h"
#include "IMsgReceiver.h"
#include "IMsgDispatcher.h"
#include "IMsgTransmitter.h"

#include <list>
#include <vector>
#include <map>

#ifndef WIN32
#include <sys/select.h>
#endif

/*!
* @addtogroup comm
* @{
*/

namespace lsr
{

/**
 * This class handles traffic to and from the FU or the Engine.
 */
class ODIComSession : public MsgTransceiverTCP::IMsgTransceiverTCPObserver, public IMsgDispatcher
{
public:

    /**
     * Mutex delegate interface.
     *
     * This interface is used to make a delegate class handle locking and
     * unlocking of a mutex.
     */
    class IODIComSessionMutexDelegate
    {
    public:
        virtual ~IODIComSessionMutexDelegate() {};

        /**
         * Called when the session needs to make a lock and be sure to be the
         * only one with access to the stack. (When data has been received for the socket)
         */
        virtual void Lock() = 0;

        /**
         * Called when the session is ready with the lock.
         * (Right before the session is waiting for new socket data)
         */
        virtual void Unlock() = 0;
    };

    /**
     * Constructor.
     * Takes an optional MutexDelegate as an argument.
     * The MutexDelegate should be used when more than one thread is about to send/receive data
     * with this session.
     * @param pODIComSessionMutexDelegate optional MutexDelegate
     */
    explicit ODIComSession(IODIComSessionMutexDelegate* pODIComSessionMutexDelegate = NULL);
    virtual ~ODIComSession();

    /**
     * Will disconnect all listeners and close all open sockets
     */
    void Reset();

    /**
     * Set timeout for data processing.
     * HandleIncomingData will return at latest if this timeout exceeds, even
     * if there would be more data to process.
     * @param timeout timeout in ms. 0 deactivates timeout. (default)
     */
    void SetTimeout(U32 timeout);

    // IMsgDispatcher
    ComError registerMsgReceiver(IMsgReceiver* const pMsgReceiver, const U8 messageType,
        const U32 minPayload = IMsgDispatcher::NO_PAYLOAD_LIMIT, const U32 maxPayload = IMsgDispatcher::NO_PAYLOAD_LIMIT) P_OVERRIDE;
    ComError unregisterMsgReceiver(IMsgReceiver* const pMsgReceiver, const U8 messageType) P_OVERRIDE;
    void unregisterAllMsgReceivers() P_OVERRIDE;

    /**
     * Handles incoming data and connections. Calls the appropriate observer callbacks.
     * This method uses the mutexDelegate if provided in constructor: @see IODIComSessionMutexDelegate
     *
     * @param msTimeout Specify how much time, at most, you want to be spent in this function.
     *                  The function returns after this time BUT in some cases it could
     *                  take longer time depending on callback functions.
     */

    ComError handleIncomingData(const U32 msTimeout) P_OVERRIDE;

    /**
     * Create a connection over TCP/IP. Note: The Function uses a non blocking socket
     * and will return before the connection has been established. Therefore, first register
     * a message receiver to be able to receive either a OnConnect or a OnDisconnect callback
     * in order to know if the connection was successful or not.
     *
     * @param[in] hostname Name of the server host
     * @param[in] portNo port number to connect to.
     * @return MsgTransceiverTCP* MsgTransceiverTCP object.
     */
    MsgTransceiverTCP* Connect(const std::string& hostname, U16 portNo);

    /**
     * Start to listen for TCP/IP connections on a port.
     * All registered message receivers will receive callbacks when someone connects or disconnects
     *
     * @param[in] hostname Address of the interface to bind to
     * @param[in] portNo port number to connect to.
     * @return bool True if we have successfully started to listen on the port.
     */
    bool Listen(const std::string& hostname, U16 portNo);

    /**
     * Disconnects all connections
     */
    void DisconnectAll();

    // IMsgTransceiverTCP
    void OnMessage(MsgTransceiverTCP* pMsgTransceiverTCP, U8 messageType, const U8* data, U32 dataLen) P_OVERRIDE;
    void OnConnect(MsgTransceiverTCP* pMsgTransceiverTCP) P_OVERRIDE;
    void OnDisconnect(MsgTransceiverTCP* pMsgTransceiverTCP) P_OVERRIDE;

private:
    ODIComSession(const ODIComSession&);
    ODIComSession& operator=(const ODIComSession&);

    void CheckDisconnected();

    std::list<MsgTransceiverTCP::ExpectedType> m_registeredTypes;
    std::list<MsgTransceiverTCP::ExpectedType> m_registeredTypesOnly;

    std::map<U8,IMsgReceiver*> m_messageListenerMap;       // fu to transport

    std::list<IMsgReceiver*> m_messageListeners;

    std::list<MsgTransceiverTCP*> m_connectionsList;
    std::vector<MsgTransceiverTCP*> m_connectionsDisconnectedList;

    fd_set m_fdConnectedSet;    // file descriptor list for connected connections
    fd_set m_fdWaitConnectSet;  // file descriptor list for connections waiting to connect
    int    m_fdMax;             // maximum file descriptor number
    IODIComSessionMutexDelegate* m_pODIComSessionMutexDelegate;

    //Debug variables and functions
    Socket m_debugSocket;
    U32 m_timeout;
};

inline void ODIComSession::SetTimeout(U32 timeout)
{
    m_timeout = timeout;
}

} // namespace comm

/*! @} */

#endif // ODISESSION_H
