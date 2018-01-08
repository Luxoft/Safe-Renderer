#ifndef MSG_TRANSCEIVER_TCP_H
#define MSG_TRANSCEIVER_TCP_H

/******************************************************************************
**
**   File:        MsgTransceiverTCP.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "IMsgTransmitter.h"
#include "IMsgReceiver.h"

#ifdef WIN32
#include "winsock.h"
#else
#include <netinet/in.h>
#endif

#include <list>
#include <string>

/*!
* @addtogroup comm
* @{
*/

namespace psc
{

#ifdef WIN32
    typedef U16 in_port_t;
    typedef int ssize_t;
    typedef SOCKET Socket;
#else
    typedef int Socket;
    #ifdef ANDROID
        typedef unsigned short in_port_t;
    #endif
#endif

class ODIRecorder;


/**
*
* Handles trasport of ODI messages over a tcpconnection.
*/
class MsgTransceiverTCP : public IMsgTransmitter
{
public:
    /**
     * Struct describing what data.
     *
     * Used in MsgTransceiverTCP::HandleData() interface.
     */
    struct ExpectedType
    {
        enum
        {
            NO_PAYLOAD_LIMIT = 0 /// Indicates that there is no limit on the payload
        };

        U8 m_type; ///< The message type.
        U32 m_minPayload; ///< Minimum bytes in payload (0 - ignored).
        U32 m_maxPayload; ///< Maximum bytes in payload (0 - ignored).

        /**
         * A constructor that fills the struct.
         *
         * @param t The message type
         * @param mi Minimum bytes in payload (0 - ignored)
         * @param ma Maximum bytes in payload (0 - ignored)
         */
        ExpectedType(U8 t, U32 mi, U32 ma) : m_type(t), m_minPayload(mi), m_maxPayload(ma) { }
    };

    /**
     * @class IMsgTransceiverTCPObserver
     *
     * An interface class implemented by classes that like to be informed when
     * events happens on the MsgTransceiverTCP class.
     */
    class IMsgTransceiverTCPObserver
    {
        // TODO: Should we add protected, constructors to this class?
    public:
        /**
         * The destructor.
         */
        virtual ~IMsgTransceiverTCPObserver() {};
        /**
         * Called when a message have arrived ov the TCP connection.
         * @param pMsgTransceiverTCP the class that recived the message
         * @param pBufferHandler the class that is responsible for the message buffer.
         * @param messageType The ODI type of the message
         * @param data pointer to the message data
         * @param dataLen the number of bytes in the data
         */
        virtual void OnMessage(MsgTransceiverTCP* pMsgTransceiverTCP,
            U8 messageType,
            const U8* data,
            U32 dataLen) = 0;

        /**
         * Called when the connection has been established
         * @param pMsgTransceiverTCP the class that received the message
         */
        virtual void OnConnect(MsgTransceiverTCP* pMsgTransceiverTCP) = 0;

        /**
         * Called when the connection disconnects
         * @param pMsgTransceiverTCP the class that recived the message
         */
        virtual void OnDisconnect(MsgTransceiverTCP* pMsgTransceiverTCP) = 0;
    };

    /**
     * Creates a new instance of the class.
     *
     * @param[in] dataBufferSize the size of the reciving data buffer.
     * @param[in] pODIRecorder optional instance for recording ODI data
     */
    explicit MsgTransceiverTCP(U32 dataBufferSize, ODIRecorder* pODIRecorder = 0);

    /**
     * The destructor of the class.
     */
    virtual ~MsgTransceiverTCP();

    /**
     * Changes the observer class that gets notified of events on this connection. Only one
     * class can be observer.
     *
     * @param pMsgTransceiverTCPObserver the new observer class.
     */
    void SetMsgTransceiverTCPObserver(IMsgTransceiverTCPObserver* pMsgTransceiverTCPObserver) {m_pMsgTransceiverTCPObserver = pMsgTransceiverTCPObserver; }

    /**
     * Connect the transport to a ODI server, e.g. the Luxoft Populus Engine.
     *
     * @param[in] hostname Name of the server host
     * @param[in] portNo port number to connect to.
     */
    bool Connect(const std::string& hostname, U16 portNo);

    /**
    * Listen for connections on a port.
    * @param[in] hostname Address of the interface to bind to
    * @param[in] portNo port number to listen on.
    */
    bool Listen(const std::string& hostname, U16 portNo);

    /**
     * Handle incoming data.
     *
     * @param readStatus if file is possible to read
     * @param writeStatus if file is possible to write
     * @param exceptStatus if an exeption have occured
     * @param registeredTypes what types that can be expected
     * @param[in,out] timestamp HandleData compares current timestamp with provided timestamp
     *      and aborts if current timestamp is newer.
     *      Timestamp will be set to the last measured current timestamp if aborted.
     *      No measurements/abort will be done if provided timestamp is 0
     */
    void HandleData(bool readStatus,bool writeStatus,bool exceptStatus,
        std::list< MsgTransceiverTCP::ExpectedType > &registeredTypes, U32& timestamp);

    /**
     * Handle incoming data.
     *
     * @param readStatus if file is possible to read
     * @param writeStatus if file is possible to write
     * @param exceptStatus if an exeption have occured
     * @param registeredTypes what types that can be expected
     */
    void HandleData(bool readStatus,bool writeStatus,bool exceptStatus,
        std::list< MsgTransceiverTCP::ExpectedType > &registeredTypes);

    /**
     * Return the socet object for this connection.
     *
     * @return the socket object.
     */
    Socket GetSocket() {return m_socket;}

    // IMsgTransmitter
    virtual PSCError transmitMessage(const U8* data, U32 dataLen) P_OVERRIDE;

    // IBufferHandler
    virtual U8* ClaimDataBuffer();
#ifdef PROXY_FU
    virtual void LockMutex( void );
    virtual bool TransmitMessage( const U8* data,U32 dataLen );
    virtual void UnlockMutex( void );
#endif

private:
    IMsgTransceiverTCPObserver* m_pMsgTransceiverTCPObserver; //!< The currect observer class

    std::string m_hostname; //!< The hostname of the server
    in_port_t   m_port; //!< Portnumber of the server
    Socket      m_socket; //!< The socket used to connect to the server.

    void closeSocket();
    void Disconnect();
    void PrintErrorCode();
    bool GetSocketReadStatus(bool& result, int s_timeout = 0, int us_timeout = 0);
    bool GetSocketWriteStatus(bool& status, int s_timeout = 0, int us_timeout = 0);
    bool ReceiveHeader(std::list<MsgTransceiverTCP::ExpectedType> &registeredTypes);
    bool ReceiveData();
    void ResizeDataBuffer(U32 newSize);
    bool InternalSend(const U8* data, U32 dataLen);

    typedef enum {
        IDLE = 0,
        TRY_CONNECT,
        WAIT_FOR_CONNECTED,
        CONNECTED_WAIT_FOR_HEADER,
        CONNECTED_WAIT_FOR_DATA,
        TRY_LISTEN,
        LISTEN
    } TCPState;

    TCPState m_state;

    U8* m_pDataBuffer;
    U32 m_dataBufferSize;
    U32 m_messageLen;
    U32 m_messageReceivedNoBytes;
    U8  m_messageType;
    bool m_bDataBufferSizeDynamic;

    enum {
        HEADER_SIZE = 5
    };

    U8 m_headerBuffer[HEADER_SIZE];
    U8 m_headerReceivedNoBytes;

    U32 m_prevMessageLen;
    U8 m_prevMessageType;

    void TraceErrPrevMessage(const char* msg, U8* buffer);
private:
    MsgTransceiverTCP(const MsgTransceiverTCP&);
    MsgTransceiverTCP& operator=(const MsgTransceiverTCP&);
};

} // namespace comm

/*! @} */

#endif // MSG_TRANSCEIVER_TCP_H
