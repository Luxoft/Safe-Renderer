/******************************************************************************
**
**   File:        MsgTransceiverTCP.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#ifdef WIN32
#include "stdio.h"
#else
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define SOCKET_ERROR -1
#endif

#include "MsgTransceiverTCP.h"
#include <pgw.h>
#include "logmsg.h"

namespace psc
{

#if defined( WIN32 ) || defined( __INTEGRITY ) || defined(__APPLE__)
static const int socketSendFlags = 0;
#else
static const int socketSendFlags = MSG_NOSIGNAL;
#endif

MsgTransceiverTCP::MsgTransceiverTCP(U32 dataBufferSize, ODIRecorder* pODIRecorder) :
    m_pMsgTransceiverTCPObserver(0),
    m_port(0),
    m_socket(static_cast<Socket>(-1)),
    m_state(IDLE),
    m_pDataBuffer(NULL),
    m_dataBufferSize(0),
    m_messageLen(0),
    m_messageReceivedNoBytes(0),
    m_messageType(0),
    m_bDataBufferSizeDynamic(false),
    m_headerReceivedNoBytes(0),
    m_prevMessageLen(0),
    m_prevMessageType(0)
{
   if (dataBufferSize == 0)
   {
       m_bDataBufferSizeDynamic = true;
   }
   else
   {
       ResizeDataBuffer(dataBufferSize);
   }

}

MsgTransceiverTCP::~MsgTransceiverTCP()
{
    Disconnect();

    if (m_pDataBuffer)
    {
        delete[] m_pDataBuffer;
    }
}

bool MsgTransceiverTCP::Listen(const std::string& hostname, U16 portNo)
{
    m_hostname = hostname;
    m_port = portNo;

#ifdef WIN32
    WSADATA  wsa;

    // initialize windows sockets
    if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
    {
        return false;
    }
#endif

    m_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == m_socket)
    {
        perror("socket");
        LOG_ERR(( "MsgTransceiverTCP::Listen, socket(...) failed."));
        return false;
    }

    //Non blocking;
#ifdef WIN32
    int iMode = 1;
    if (0 != ioctlsocket(m_socket, FIONBIO, (u_long FAR*) &iMode))
    {
        perror("ioctlsocket");
        LOG_ERR(( "MsgTransceiverTCP::Listen, ioctlsocket FIONBIO failed, socket:%d.", m_socket));
        closeSocket();
        return false;
    }
#else
    int flags;
    flags = fcntl(m_socket, F_GETFL, 0);
    if (-1 == fcntl(m_socket, F_SETFL, flags | O_NONBLOCK))
    {
        perror("fcntl");
        LOG_ERR(( "MsgTransceiverTCP::Listen, fcntl F_SETFL O_NONBLOCK failed, socket:%d.", m_socket));
        closeSocket();
        return false;
    }
#endif

    int optval = 1;
#if !defined(WIN32) || defined(_DEBUG)
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval, sizeof(optval)) == -1)
    {
        perror("setsockopt");
        LOG_ERR(( "MsgTransceiverTCP::Listen, setsockopt SO_REUSEADDR failed, socket:%d.", m_socket));
        closeSocket();
        return false;
    }
#endif

    if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&optval), sizeof(optval)) == -1)
    {
        LOG_ERR(( "MsgTransceiverTCP::Listen, setsockopt TCP_NODELAY failed, interface=%s, port=%d, socket=%d, error=%d", m_hostname.c_str(), portNo, m_socket, errno));
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_port);
    serverAddr.sin_addr.s_addr = inet_addr(m_hostname.c_str());

    if (-1 == bind(m_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)))
    {
#ifndef WIN32
        fprintf(stderr, "bind(%d): %s\n", m_port, strerror(errno));
#endif
        closeSocket();
        return false;
    }

    if (-1 == listen(m_socket, 1))
    {
        perror("listen");
        LOG_ERR(( "MsgTransceiverTCP::Listen, listen failed on interface:%s, port:%d, socket:%d.", m_hostname.c_str(), portNo, m_socket));
        closeSocket();
        return false;
    }

    LOG_VERB(( "MsgTransceiverTCP::Listen, Listen on interface:%s, port:%d, socket:%d.", m_hostname.c_str(), portNo, m_socket));

    m_state = LISTEN;
    return true;
}

bool MsgTransceiverTCP::Connect(const std::string& hostname, U16 portNo)
{
    m_hostname = hostname;
    m_port = portNo;
#ifdef WIN32
    WSADATA  wsa;

    // initialize windows sockets
    if ( WSAStartup( MAKEWORD( 1, 1 ), &wsa ) != 0 )
    {
        LOG_ERR(( "MsgTransceiverTCP::Connect, WSAStartup failed."));
        return false;
    }
#endif

    m_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == m_socket)
    {
        LOG_ERR(( "MsgTransceiverTCP::Connect, Failed to get socket."));
        return false;
    }

#ifdef WIN32
    int iMode = 1; // 0 = blocking, 1 = nonblocking
    if ( 0 != ioctlsocket(m_socket, FIONBIO, (u_long FAR*) &iMode) )
    {
        perror("ioctlsocket");
        LOG_ERR(( "MsgTransceiverTCP::Connect, ioctlsocket FIONBIO failed, socket:%d.", m_socket));
        closeSocket();
        return false;
    }
#else
    int flags = fcntl(m_socket,F_GETFL,0);
    if ( -1 == fcntl(m_socket, F_SETFL, flags | O_NONBLOCK) )
    {
        perror("fcntl");
        LOG_ERR(( "MsgTransceiverTCP::Connect, fcntl F_SETFL O_NONBLOCK failed, socket:%d.", m_socket));
        closeSocket();
        return false;
    }
#endif
    int flag = 1;
    int result = setsockopt(m_socket,                       /* socket affected */
                            IPPROTO_TCP,                    /* set option at TCP level */
                            TCP_NODELAY,                    /* name of option */
                            reinterpret_cast<char*>(&flag), /* the cast is historical cruft */
                            sizeof(int));

    if(-1 == result)
    {
        LOG_ERR(( "MsgTransceiverTCP::Connect, setsockopt failed, port=%d, socket=%d, error=%d", portNo, m_socket, errno));
    }

    struct sockaddr_in FUSockAddr;
    memset(&FUSockAddr, 0, sizeof(FUSockAddr));

    FUSockAddr.sin_family = AF_INET;
    FUSockAddr.sin_addr.s_addr = inet_addr( m_hostname.c_str() );
    FUSockAddr.sin_port = htons(m_port);

    LOG_VERB(( "MsgTransceiverTCP::Connect, connect to %s:%d socket: %d,",  m_hostname.c_str(), m_port, m_socket));

    if(SOCKET_ERROR == connect(m_socket, (struct sockaddr*) &FUSockAddr, sizeof(FUSockAddr)))
    {
#ifdef WIN32
        if (WSAGetLastError() != WSAEWOULDBLOCK)
#else
        if (errno != EINPROGRESS)
#endif
        {
            LOG_ERR(( "%p::doConnect, Failed to connect to FU. socket %d", this, m_socket));

            closeSocket();

            return false;
        }
    }

    m_state = WAIT_FOR_CONNECTED;
    return true;
}

void MsgTransceiverTCP::HandleData(bool readStatus, bool writeStatus, bool exceptStatus,
    std::list<MsgTransceiverTCP::ExpectedType> &registeredTypes)
{
    U32 timestamp = 0;
    HandleData(readStatus, writeStatus, exceptStatus, registeredTypes, timestamp);
}

void MsgTransceiverTCP::HandleData(bool readStatus,bool writeStatus,bool exceptStatus,
    std::list<MsgTransceiverTCP::ExpectedType> &registeredTypes, U32& timestamp)
{
    U32 moreDataCount = 0;
    bool bMoreData = true;

    while (bMoreData)
    {
        bMoreData = false;

        switch (m_state)
        {
        case IDLE:
            break;

        case WAIT_FOR_CONNECTED:
            {
                if (exceptStatus)
                {
                    Disconnect();
                }
                else if (writeStatus)
                {
                    // get sock opt
                    int nOptionValue;
#ifdef WIN32
                    int nOptionValueLength = sizeof(nOptionValue);
                    if ( 0 != getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (char*)&nOptionValue, &nOptionValueLength) )
                    {
                        LOG_ERR(( "MsgTransceiverTCP::HandleData, WAIT_FOR_CONNECTED getsockopt"));

                        Disconnect();
                        break;
                    }
#else
                    socklen_t nOptionValueLength = sizeof(nOptionValue);
                    if ( -1 == getsockopt(m_socket, SOL_SOCKET, SO_ERROR, &nOptionValue, &nOptionValueLength) )
                    {
                        LOG_ERR(( "MsgTransceiverTCP::HandleData, WAIT_FOR_CONNECTED getsockopt"));

                        Disconnect();
                        break;
                    }
#endif
                    // Test send, this will get error status on Linux.
                    if(nOptionValue) {
                        LOG_ERR(( "MsgTransceiverTCP::HandleData, WAIT_FOR_CONNECTED, errno = 0x%x,%s", nOptionValue,strerror(nOptionValue)));

                        Disconnect();
                    } else {
                        m_state = CONNECTED_WAIT_FOR_HEADER;
                        m_headerReceivedNoBytes = 0;
                        m_pMsgTransceiverTCPObserver->OnConnect(this);
                    }
                }
            }
            break;

        case CONNECTED_WAIT_FOR_HEADER:
            {
                if (readStatus)
                {
                    if (!ReceiveHeader(registeredTypes))
                    {
                        Disconnect();
                    }
                }
            }

            break;
        case CONNECTED_WAIT_FOR_DATA:
            {
                if (readStatus)
                {
                    if (!ReceiveData())
                    {
                        Disconnect();
                    }
                }
            }
            break;

        case LISTEN:
            {
                if (readStatus)
                {
                    Socket AcceptSocket = static_cast<Socket>(SOCKET_ERROR);
                    AcceptSocket=accept(m_socket,0,0);
                    if(AcceptSocket!=SOCKET_ERROR)
                    {
                        MsgTransceiverTCP *pMsgTransceiverTCP = new MsgTransceiverTCP(0, NULL);
                        pMsgTransceiverTCP->m_port=m_port;
                        pMsgTransceiverTCP->m_pMsgTransceiverTCPObserver=m_pMsgTransceiverTCPObserver;
                        pMsgTransceiverTCP->m_socket=AcceptSocket;
                        pMsgTransceiverTCP->m_state=CONNECTED_WAIT_FOR_HEADER;
                        m_pMsgTransceiverTCPObserver->OnConnect(pMsgTransceiverTCP);
                    }
                }

            }
            //accept
            break;
        default:
            break;
        }

        if ((m_state == CONNECTED_WAIT_FOR_HEADER) ||
            (m_state == CONNECTED_WAIT_FOR_DATA))
        {
            ++moreDataCount;
            U32 currentTime = 0u;
            if (timestamp != 0 && moreDataCount % 10 == 0)
            {
                //don't measure too often (might also waste time)
                currentTime = pgwGetMonotonicTime();
            }
            if (currentTime <= timestamp)
            {
                if (GetSocketReadStatus(readStatus, 0, 0))
                {
                    bMoreData = readStatus;
                }
            }
            else
            {
                //data receiption takes too long -> return to main loop (we need to be responsive)
                bMoreData = false;
                timestamp = currentTime;
                LOG_WARN(( "MsgTransceiverTCP::HandleData exceeding time."));
            }
        }
    }
}

bool MsgTransceiverTCP::GetSocketReadStatus(bool& result, int s_timeout, int us_timeout)
{
    struct timeval tv;
    fd_set readfds;
    fd_set exceptfds;

    tv.tv_sec = s_timeout;
    tv.tv_usec = us_timeout;

    FD_ZERO(&readfds);
    FD_ZERO(&exceptfds);

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4127 )   // conditional expression is constant
#endif
    FD_SET(m_socket, &readfds);
    FD_SET(m_socket, &exceptfds);
#ifdef _MSC_VER
#pragma warning( pop )
#endif

    // don't care about writefds
    int ret = select(static_cast<int>(m_socket+1), &readfds, NULL, &exceptfds, &tv);

    if ((((s_timeout != 0) || (us_timeout != 0)) && (ret == 0 )) ||
         ret == SOCKET_ERROR || FD_ISSET(m_socket, &exceptfds))
    {
        return false;
    }

    result = (FD_ISSET(m_socket, &readfds) != 0);

    return true;
}

bool MsgTransceiverTCP::GetSocketWriteStatus(bool& result, int s_timeout, int us_timeout)
{
    struct timeval tv;
    fd_set writefds;
    fd_set exceptfds;

    tv.tv_sec = s_timeout;
    tv.tv_usec = us_timeout;

    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4127 )   // conditional expression is constant
#endif
    FD_SET(m_socket, &writefds);
    FD_SET(m_socket, &exceptfds);
#ifdef _MSC_VER
#pragma warning( pop )
#endif

    // don't care about readfds
    int ret = select(static_cast<int>(m_socket+1), NULL , &writefds, &exceptfds, &tv);

    if ((((s_timeout != 0) || (us_timeout != 0)) && (ret == 0 )) ||
         ret == SOCKET_ERROR || FD_ISSET(m_socket, &exceptfds))
    {
        return false;
    }

    result = (FD_ISSET(m_socket, &writefds) != 0);

    return true;
}

PSCError MsgTransceiverTCP::transmitMessage(const U8 *pData, U32 dataLen)
{
    //printf("MsgTransceiverTCP::TransmitMessage, socket: %d, type: %d, header len: %d, data len: %d\n", m_socket, messageType, HEADER_SIZE, dataLen);

    U32 dataLenNet = htonl(dataLen-1);

    memcpy(&m_headerBuffer[0],&dataLenNet,4);
    m_headerBuffer[4] = pData[0]; // messageType

    if (!InternalSend(m_headerBuffer, HEADER_SIZE))
    {
        return PSC_UNKNOWN_ERROR;
    }

    if (!InternalSend(pData+1, dataLen-1))
    {
        return PSC_UNKNOWN_ERROR;
    }

    if (m_state == WAIT_FOR_CONNECTED)
    {
        // OK, if we send we are connected..
        m_state = CONNECTED_WAIT_FOR_HEADER;
        m_pMsgTransceiverTCPObserver->OnConnect(this);
    }
    return PSC_NO_ERROR;
}

#ifdef PROXY_FU
void MsgTransceiverTCP::LockMutex( void )
{
    m_sMutex.lock( );
}

bool MsgTransceiverTCP::TransmitMessage( const U8* data, U32 dataLen )
{
    /*
    ** This function is supposed to be enclosed with LockMutex( ), UnlockMutex( ).
    */
    if( !InternalSend( data,dataLen ))
    {
        return false;
    }
    return true;
}

void MsgTransceiverTCP::UnlockMutex( void )
{
    m_sMutex.unlock();
}
#endif

bool MsgTransceiverTCP::InternalSend(const U8* data, U32 dataLen)
{
    bool ready = false;
    U32 totalDataSent = 0;
    int dataSent = 0;
    while (totalDataSent < dataLen)
    {
        if (GetSocketWriteStatus(ready,5,0))
        {
            if (ready)
            {
                dataSent = send(m_socket, reinterpret_cast<const char *> (&data[totalDataSent]), dataLen-totalDataSent, socketSendFlags);
                if(SOCKET_ERROR == dataSent)
                {
#ifndef HAVE_ERRNO_T
                    typedef int errno_t;
#endif
                    errno_t err = errno;
                    Disconnect();
                    LOG_ERR(( "MsgTransceiverTCP::InternalSend, socket error. socket:%d, %s(%d)",m_socket,strerror(err), err));
                    return false;
                }
                if(dataSent > 0)
                {
                    totalDataSent += dataSent;
                    //printf("MsgTransceiverTCP::InternalSend, socket: %d, wrote: %d\n", m_socket, dataSent);
                }
            }
            else
            {
                // timeout
                Disconnect();
                LOG_WARN(( "MsgTransceiverTCP::InternalSend, tim. socket:%d",m_socket));
                return false;
            }
        }
        else
        {
            // timeout
            Disconnect();
            LOG_VERB(( "MsgTransceiverTCP::InternalSend, timeout. socket:%d",m_socket));
            return false;
        }
    }
    return true;
}

void MsgTransceiverTCP::Disconnect()
{
    m_pMsgTransceiverTCPObserver->OnDisconnect(this);
    closeSocket();
    m_state = IDLE;
}

void MsgTransceiverTCP::closeSocket()
{
    if (m_socket != -1)
    {
#ifdef WIN32
        closesocket(m_socket);
#else
        close(m_socket);
#endif
        m_socket = static_cast<Socket>(-1);
    }
}


bool MsgTransceiverTCP::ReceiveHeader(std::list<MsgTransceiverTCP::ExpectedType> &registeredTypes)
{
    //printf("MsgTransceiverTCP::ReceiveHeader(): Waiting for header, socket %d\n", m_socket);

    U32 messageLenNet = 0;

    const int recvBytes = recv(m_socket, reinterpret_cast<char *>(&m_headerBuffer[m_headerReceivedNoBytes]),
            sizeof(m_headerBuffer)-m_headerReceivedNoBytes, 0);
    //printf("MsgTransceiverTCP::ReceiveHeader - number of bytes: %u socket: %d,\n", recvBytes,m_socket);

    if((SOCKET_ERROR == recvBytes) || (recvBytes == 0))
    {
        LOG_VERB(( "MsgTransceiverTCP::ReceiveHeader, recvBytes:%d",recvBytes));
        return false;
    }

    m_headerReceivedNoBytes += static_cast<U8>(recvBytes);

    if (m_headerReceivedNoBytes == sizeof(m_headerBuffer))
    {
        memcpy(&messageLenNet,&m_headerBuffer[0],4);
        m_messageLen = ntohl(messageLenNet);
        m_messageType = m_headerBuffer[4];

        LOG_VERB(( "MsgTransceiverTCP::ReceiveHeader, socket: %d, type: %d, msg len: %d", m_socket, m_messageType, m_messageLen));

        std::list<MsgTransceiverTCP::ExpectedType>::iterator it;
        for (it = registeredTypes.begin();it != registeredTypes.end();it++)
        {
            if((*it).m_type == m_messageType)
            {
                break;
            }
        }
        if(it == registeredTypes.end())
        {
            TraceErrPrevMessage("MsgTransceiverTCP::ReceiveHeader, Unexpected message type received.", m_headerBuffer);
            return false; // Abort and disconnect.
        }

        //Check if message is too small
        if(m_messageLen < (*it).m_minPayload)
        {
            TraceErrPrevMessage("MsgTransceiverTCP::ReceiveHeader, Unexpected message length for this type of message (too short).", m_headerBuffer);
            return false; // Abort and disconnect.
        }

        //Check if message is too large
        if(m_messageLen > (*it).m_maxPayload && (*it).m_maxPayload != ExpectedType::NO_PAYLOAD_LIMIT)
        {
            TraceErrPrevMessage("MsgTransceiverTCP::ReceiveHeader, Unexpected message length for this type of message (too long).", m_headerBuffer);
            return false; // Abort and disconnect.
        }

        m_prevMessageLen = m_messageLen;
        m_prevMessageType = m_messageType;

        if (m_messageLen > m_dataBufferSize)
        {
            if (m_bDataBufferSizeDynamic)
            {
                ResizeDataBuffer(m_messageLen);
            }
            else
            {
                LOG_ERR(( "MsgTransceiverTCP::ReceiveHeader, Message (%d bytes) to large for buffer (%d bytes)",(int)m_messageLen,(int)m_dataBufferSize));
            }
        }

        if((m_pDataBuffer == NULL) || (m_messageLen == 0))
        {
           LOG_VERB(( "MsgTransceiverTCP::ReceiveHeader, m_messageLen:%d",(int)m_messageLen));
           PrintErrorCode();
           return false;
        }

        m_messageReceivedNoBytes = 0;
        m_state = CONNECTED_WAIT_FOR_DATA;
    }

    return true;
}

bool MsgTransceiverTCP::ReceiveData()
{
    if((m_pDataBuffer != NULL) && m_messageLen)
    {
        int nrOfBytesRead = 0;

        nrOfBytesRead = recv(m_socket, reinterpret_cast<char *>(&m_pDataBuffer[m_messageReceivedNoBytes]),
            (m_messageLen-m_messageReceivedNoBytes), 0 );
        m_messageReceivedNoBytes += nrOfBytesRead;
        //printf( "MsgTransceiverTCP::ReceiveData (%d): reading %d bytes\n",m_socket, nrOfBytesRead);

        if ((nrOfBytesRead == SOCKET_ERROR) || (nrOfBytesRead == 0))
        {
            LOG_VERB(( "MsgTransceiverTCP::ReceiveData, nrOfBytesRead %d",(int)nrOfBytesRead));
            PrintErrorCode();
            return false;
        }

        LOG_VERB(( "MsgTransceiverTCP::ReceiveData, socket: %d, read: %d", m_socket, (int)nrOfBytesRead));

        if (m_messageReceivedNoBytes == m_messageLen)
        {
            m_state = CONNECTED_WAIT_FOR_HEADER;
            m_headerReceivedNoBytes = 0;
            m_pMsgTransceiverTCPObserver->OnMessage(this, m_messageType, m_pDataBuffer, m_messageLen);
        #ifdef PROXY_FU
            /*
             * There are a lot of messages that the proxy does not need/want.
             * But we send them to it and let it work out wat to do with em.
             * This way it should be easy to modify Proxy_FU behaviour.
             */
            if( m_pForwarder ) m_pForwarder->Forward( m_headerBuffer,HEADER_SIZE,
                                                      m_pDataBuffer,m_messageLen );
        #endif
        }
    }
    else
    {
        LOG_VERB(( "MsgTransceiverTCP::ReceiveHeader, m_messageLen:%d",(int)m_messageLen));
        return false;
    }
    return true;
}

void MsgTransceiverTCP::ResizeDataBuffer(U32 newSize)
{
    LOG_VERB(( "MsgTransceiverTCP::ResizeDataBuffer, socket: %d, new size:%d",m_socket,newSize));

    if (m_pDataBuffer)
    {
        delete[] m_pDataBuffer;
    }

#ifdef __EXCEPTIONS
    try {
        m_pDataBuffer = new U8[newSize];
    } catch ( ... )
    {
        m_pDataBuffer = NULL;
        LOG_ERR(( "MsgTransceiverTCP::ResizeDataBuffer, failed to allocate new memory socket:%d, new size:%d",m_socket,newSize));
    }
#else // __EXCEPTIONS
    m_pDataBuffer = new U8[newSize];
#endif // __EXCEPTIONS

    if (m_pDataBuffer)
    {
        m_dataBufferSize = newSize;
    }
    else
    {
        LOG_ERR(( "MsgTransceiverTCP::ResizeDataBuffer, failed to allocate new memory socket:%d, new size:%d",m_socket,newSize));
        m_dataBufferSize = 0;
    }
}

void MsgTransceiverTCP::PrintErrorCode()
{
#ifdef WIN32
    LOG_ERR(( "WSAGetLastError() = %d",WSAGetLastError()));

    int nOptionValue;
    int nOptionValueLength = sizeof(nOptionValue);

    //Get error code specific to this socket

    getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (char*)&nOptionValue,
                                            &nOptionValueLength);

    LOG_ERR(( "Error code specific to this socket:%d",nOptionValue));
#else
    LOG_ERR(( "MsgTransceiverTCP::PrintErrorCode(): errno = 0x%x,%s", errno,strerror(errno)));
#endif
}

void MsgTransceiverTCP::TraceErrPrevMessage(const char* msg, U8* buffer)
{
    LOG_ERR(( "Sanity check: %s\n"
        "        This message: Len: % 8u, Type: %d, Buff: %02X %02X %02X %02X %02X\n"
        "        Previous msg: Len: % 8u, Type: %d", msg,
        m_messageLen, m_messageType, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4],
        m_prevMessageLen, m_prevMessageType));
}

U8* MsgTransceiverTCP::ClaimDataBuffer()
{
    if(m_bDataBufferSizeDynamic)
    {
        U8* retVal = m_pDataBuffer;
        m_dataBufferSize = 0;
        m_pDataBuffer = NULL;
        return retVal;
    }
    return NULL;
}

} // namespace comm
