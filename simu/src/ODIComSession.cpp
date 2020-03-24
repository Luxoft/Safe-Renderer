/******************************************************************************
**
**   File:        ODIComSession.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "ODIComSession.h"
#include "MsgTransceiverTCP.h"
#include "InputStream.h"
#include <pil.h>
#include "logmsg.h"

#ifndef WIN32
#define SOCKET_ERROR -1
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#endif

namespace lsr
{

ODIComSession::ODIComSession(IODIComSessionMutexDelegate* pODIComSessionMutexDelegate) :
    m_fdMax(0),
    m_pODIComSessionMutexDelegate(pODIComSessionMutexDelegate),
    m_debugSocket(static_cast<Socket>(-1)),
    m_timeout(0u)
{
    FD_ZERO(&m_fdConnectedSet);     // Clear the master set
    FD_ZERO(&m_fdWaitConnectSet);   // Clear the master set
}

ODIComSession::~ODIComSession()
{
    Reset();
}

void ODIComSession::Reset()
{
    while ( !m_connectionsList.empty() )
    {
        delete m_connectionsList.back();
        m_connectionsList.pop_back();
    }

    m_fdMax = 0;

    FD_ZERO(&m_fdConnectedSet);     // Clear the master set
    FD_ZERO(&m_fdWaitConnectSet);   // Clear the master set

    m_registeredTypes.clear();
    m_registeredTypesOnly.clear();
    m_messageListenerMap.clear();
    m_messageListeners.clear();
    m_connectionsDisconnectedList.clear();

    m_debugSocket = static_cast<Socket>(-1);
}

ComError ODIComSession::handleIncomingData(U32 msTimeout)
{
    if (m_connectionsList.size() > 0)
    {
        struct timeval tv;
        tv.tv_sec = msTimeout / 1000;
        tv.tv_usec = (msTimeout % 1000) * 1000;

        // Temp file descriptor list for select()
        fd_set readfds;
        fd_set writefds;
        fd_set exceptfds;

        {
            readfds = m_fdConnectedSet;
            writefds = m_fdWaitConnectSet;
            exceptfds = m_fdWaitConnectSet;
        }

        int ret = select(m_fdMax + 1, &readfds, &writefds, &exceptfds, &tv);

        if (ret == 0)
        {
            // Timeout
        }
        else if (SOCKET_ERROR == ret)
        {
#ifdef WIN32
            LOG_ERR(("ODIComSession::HandleIncomingData, WSAGetLastError() = %d", WSAGetLastError()));
#else
            LOG_ERR(("ODIComSession::HandleIncomingData(): errno = 0x%x,%s", errno, strerror(errno) ));
#endif
        }
        else
        {
            const U32 timestampExceed = (m_timeout != 0) ? ( m_timeout + pilGetMonotonicTime() ) : 0u;

            for (std::list<MsgTransceiverTCP *>::const_iterator it = m_connectionsList.begin(); it != m_connectionsList.end(); ++it)
            {
                Socket socket = (*it)->GetSocket();

                if ( (m_debugSocket == -1) || (m_debugSocket == socket) )
                {
                    if (socket != -1)
                    {
                        U32 timestamp = timestampExceed;

                        (*it)->HandleData(
                            (FD_ISSET(socket, &readfds) != 0),
                            (FD_ISSET(socket, &writefds) != 0),
                            (FD_ISSET(socket, &exceptfds) != 0),
                            m_registeredTypesOnly.size() > 0 ? m_registeredTypesOnly : m_registeredTypes,
                            timestamp);

                        if (timestamp > timestampExceed)
                        {
                            // Data handling takes too long (>1s) -> we need to be responsive
                            LOG_ERR(("ODIComSession::HandleIncomingData exceeding time. (%d + %d ms)", m_timeout, timestamp - timestampExceed));
                            break;
                        }
                    }
                }
            }
        }

        CheckDisconnected();
    }
    else
    {
#ifdef WIN32
        Sleep(msTimeout);
#else
        usleep(msTimeout * 1000);
#endif
    }
    return COM_NO_ERROR;
}

void ODIComSession::OnMessage(MsgTransceiverTCP* pMsgTransceiverTCP, U8 messageType, const U8* data, U32 dataLen)
{
    std::map<U8,IMsgReceiver *>::const_iterator iter = m_messageListenerMap.find(messageType);

    InputStream stream(data, dataLen);

    if ( iter != m_messageListenerMap.end() )
    {
        iter->second->onMessage(pMsgTransceiverTCP, messageType, stream);
    }

}

void ODIComSession::OnConnect(MsgTransceiverTCP* pMsgTransceiverTCP)
{
    LOG_VERB(("ODIComSession::OnConnect socket:%d", pMsgTransceiverTCP->GetSocket() ));

    // Check if this connection is an incoming new connection
    bool bNewConnection = true;
    for (std::list<MsgTransceiverTCP *>::const_iterator it = m_connectionsList.begin(); it != m_connectionsList.end(); ++it)
    {
        if ( (*it) == pMsgTransceiverTCP )
        {
            bNewConnection = false;
            break;
        }
    }

    if (bNewConnection)
    {
        m_connectionsList.push_back(pMsgTransceiverTCP);
    }

    Socket socket = pMsgTransceiverTCP->GetSocket();
    if(socket >= 0)
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4127 )   // conditional expression is constant
#endif
        // Add the listener to the master set
        FD_SET(socket, &m_fdConnectedSet);
        FD_CLR(socket, &m_fdWaitConnectSet);
#ifdef _MSC_VER
#pragma warning( pop )
#endif

        // Keep track of the biggest file descriptor
        if (static_cast<int>(socket) > m_fdMax)
        {
            m_fdMax = static_cast<int>(socket);
        }
    }

    for (std::list<IMsgReceiver *>::const_iterator obsIter = m_messageListeners.begin(); obsIter != m_messageListeners.end(); ++obsIter)
    {
        // Notify the observers
        (*obsIter)->onConnect(pMsgTransceiverTCP);
    }
}

void ODIComSession::OnDisconnect(MsgTransceiverTCP* pMsgTransceiverTCP)
{
    for (std::list<IMsgReceiver *>::const_iterator obsIter = m_messageListeners.begin();obsIter != m_messageListeners.end();obsIter++)
    {
        // Notify the observers
        (*obsIter)->onDisconnect(pMsgTransceiverTCP);
    }

    for (std::vector<MsgTransceiverTCP *>::const_iterator it = m_connectionsDisconnectedList.begin(); it != m_connectionsDisconnectedList.end(); ++it)
    {
        if ( (*it) == pMsgTransceiverTCP )
        {
            // The connection is already in the list
            return;
        }
    }

    Socket socket = pMsgTransceiverTCP->GetSocket();

    if(socket != -1)
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4127 )   // conditional expression is constant
#endif
        FD_CLR(socket, &m_fdConnectedSet);
        FD_CLR(socket, &m_fdWaitConnectSet);
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }

    m_connectionsDisconnectedList.push_back(pMsgTransceiverTCP);
}

void ODIComSession::CheckDisconnected()
{
    // printf("CheckDisconnected()\n");

    for (std::vector<MsgTransceiverTCP *>::const_iterator it = m_connectionsDisconnectedList.begin(); it != m_connectionsDisconnectedList.end(); ++it)
    {
        // Find and remove the disconnected connection from the connection set
        MsgTransceiverTCP* disconnectedConnection = *it;

        for (std::list<MsgTransceiverTCP *>::iterator it2 = m_connectionsList.begin(); it2 != m_connectionsList.end(); ++it2)
        {
            if ( (*it2) == disconnectedConnection )
            {
                delete *it2;
                m_connectionsList.erase(it2);
                break;
            }
        }

        // Keep track of the biggest file descriptor
        m_fdMax = 0;
        for (std::list<MsgTransceiverTCP *>::const_iterator fdit = m_connectionsList.begin(); fdit != m_connectionsList.end(); ++fdit)
        {
            int new_socket = static_cast<int>( (*fdit)->GetSocket() );

            if (new_socket > m_fdMax)
            {
                m_fdMax = static_cast<int>(new_socket);
            }
        }
    }

    m_connectionsDisconnectedList.clear();
}

ComError ODIComSession::registerMsgReceiver(IMsgReceiver* pMsgReceiver, const U8 messageType, U32 minPayload, U32 maxPayload)
{
    m_registeredTypes.push_back( MsgTransceiverTCP::ExpectedType(messageType, minPayload, maxPayload) );
    m_messageListenerMap.insert( std::pair<U8, IMsgReceiver*>(messageType, pMsgReceiver) );
    m_messageListeners.push_back(pMsgReceiver);
    return COM_NO_ERROR;
}

ComError ODIComSession::unregisterMsgReceiver(IMsgReceiver* pMsgReceiver, U8 messageType)
{
    std::map<U8,IMsgReceiver*>::iterator it = m_messageListenerMap.find(messageType);

    if ( it == m_messageListenerMap.end() )
    {
        LOG_ERR(("ODIComSession::UnregisterMsgReceiver, listener not found"));
        return COM_UNKNOWN_ERROR;
    }

    if( it->second != pMsgReceiver )
    {
        LOG_ERR(("ODIComSession::UnregisterMsgReceiver, attempted to unregister wrong listener"));
        return COM_UNKNOWN_ERROR;
    }

    m_messageListenerMap.erase(it);
    m_messageListeners.remove(pMsgReceiver);
    return COM_NO_ERROR;
}

void ODIComSession::unregisterAllMsgReceivers()
{
    m_messageListenerMap.clear();
    m_messageListeners.clear();
}

bool ODIComSession::Listen(const std::string& hostname, U16 portNo)
{
    MsgTransceiverTCP* pMsgTransceiverTCP = new MsgTransceiverTCP(0U);
    pMsgTransceiverTCP->SetMsgTransceiverTCPObserver(this);

    if (pMsgTransceiverTCP->Listen(hostname, portNo))
    {
        m_connectionsList.push_back(pMsgTransceiverTCP);
        Socket socket = pMsgTransceiverTCP->GetSocket();

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4127 )   // conditional expression is constant
#endif
        // Add the listener to the master set
        FD_SET(socket, &m_fdConnectedSet);
#ifdef _MSC_VER
#pragma warning( pop )
#endif

        // Keep track of the biggest file descriptor
        if (static_cast<int>(socket) > m_fdMax)
        {
            m_fdMax = static_cast<int>(socket);
        }
    }
    else
    {
        delete pMsgTransceiverTCP;
        return false;
    }

    return true;
}

MsgTransceiverTCP* ODIComSession::Connect(const std::string& hostname, U16 portNo)
{
    MsgTransceiverTCP* pMsgTransceiverTCP = new MsgTransceiverTCP(0U);
    pMsgTransceiverTCP->SetMsgTransceiverTCPObserver(this);

    if ( pMsgTransceiverTCP->Connect(hostname, portNo) )
    {
        m_connectionsList.push_back(pMsgTransceiverTCP);

        Socket socket = pMsgTransceiverTCP->GetSocket();

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4127 )   // conditional expression is constant
#endif
        // Add the connection to the `wait connection set`
        FD_SET(socket, &m_fdWaitConnectSet);
#ifdef _MSC_VER
#pragma warning( pop )
#endif

        // Keep track of the biggest file descriptor
        if (static_cast<int>(socket) > m_fdMax)
        {
            m_fdMax = static_cast<int>(socket);
        }
    }
    else
    {
        delete pMsgTransceiverTCP;
        return NULL;
    }

    return pMsgTransceiverTCP;
}

void ODIComSession::DisconnectAll()
{
    m_registeredTypes.clear();
    m_messageListenerMap.clear();
    m_messageListeners.clear();

    while ( !m_connectionsList.empty() )
    {
        delete m_connectionsList.back();
        m_connectionsList.pop_back();
    }

    m_connectionsDisconnectedList.clear();
}

} // namespace fusdk
