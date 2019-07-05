/******************************************************************************
**
**   File:        pil.cpp
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

#include "pil.h"
#include "pil_platform.h"
#include "Circbuf.h"
#include "pil_config.h"
#include <stdio.h>
#include <stdlib.h>


static Circbuf<unsigned char, PILBuffersizeFU> FUBuffers[ConnectionIndex::PILConn_Last - 1];
static Circbuf<unsigned char, PILBufferSizePop> lsrBuffer;
static volatile uint32_t lastMessageSize[ConnectionIndex::PILConn_Last];
static volatile uint32_t dataWritten[ConnectionIndex::PILConn_Last + 1] = { 0 };
static const uint32_t maxDataToLSRPerConnection = PILBufferSizePop * 2 / 3;

static volatile PILMailbox lastPopMessageConnection = ConnectionIndex::PILConn_Last;
static pil_mutex_t mutexFUQueue;
static pil_mutex_t mutexPopQueue;
static pil_event_t dataAvailableEvent[ConnectionIndex::PILConn_Last] = { 0 };
static bool initializedLSR = false;
static bool initializedFu[ConnectionIndex::PILConn_Last - 1] = {false};
static bool initialized = false;

// Hard-coded by customer event id which is used to give information to the Engine that someone sent it a message.
pil_event_id_t EV_Pop_FUToPop_Msg_Id = 1;
// Fixed size of message header for current version of transport protocol.
const uint8_t PIL_MSG_HEADER_SIZE = 5;


static PILError PilCheckInit(void)
{
    return initialized ? PIL_NO_ERROR : PIL_NOT_INITIALIZED;
}

static PILError PilCheckMbox(PILMailbox connection)
{
    PILError retValue = PIL_NO_ERROR;

    if (connection == ConnectionIndex::PILConn_Lsr)
    {
        retValue = initializedLSR ? retValue : PIL_MBOX_NOT_INITIALIZED;
    }
    else
    {
        if (connection < ConnectionIndex::PILConn_Last)
        {
            retValue = initializedFu[connection - 1] ? retValue : PIL_MBOX_NOT_INITIALIZED;
        }
        else
        {
            retValue = PIL_MBOX_INVALID;
        }
    }

    return retValue;
}

static pil_bool_t PilPopGetMsg(PILMailbox *connection, uint8_t** data, uint32_t *dataLen)
{
    size_t requiredSize = PIL_MSG_HEADER_SIZE;
    size_t acquiredSize = requiredSize;
    *data = NULL;
    *dataLen = 0;

    pil_mutex_lock(&mutexPopQueue);
    uint8_t* d = lsrBuffer.ReaderReserve(acquiredSize);

    if(d && acquiredSize >= requiredSize)
    {
        *connection=static_cast<PILMailbox>(d[0]);
        *dataLen = (static_cast<uint32_t>(d[1])) << 24;
        *dataLen |= (static_cast<uint32_t>(d[2])) << 16;
        *dataLen |= (static_cast<uint32_t>(d[3])) << 8;
        *dataLen |= (static_cast<uint32_t>(d[4]));


        /* Without a release, do another reserve */
        requiredSize = acquiredSize = *dataLen + PIL_MSG_HEADER_SIZE;

        /* Get pointer to acquired data with header*/
        d = lsrBuffer.ReaderReserve(acquiredSize);
        if (d && acquiredSize >= requiredSize)
        {
            lastPopMessageConnection = *connection;
            lastMessageSize[ConnectionIndex::PILConn_Lsr] = requiredSize;
            pil_mutex_unlock(&mutexPopQueue);
            /* Get pointer to acquired data without message header*/
            *data = d + PIL_MSG_HEADER_SIZE;
            return pil_true;
        }
        else
        {
            /* Should never happen since header and data are written
            * as 1 entity */
            pil_mutex_unlock(&mutexPopQueue);
            return pil_false;
        }
    }
    else
    {
        pil_mutex_unlock(&mutexPopQueue);
        return pil_false;
    }
}

static pil_bool_t PilWriteToPopMsg(PILMailbox connection, const uint8_t* data, uint32_t dataLen)
{
    if(dataWritten[connection] < maxDataToLSRPerConnection)
    {
        pil_event_t ev;
        uint8_t *pData;
        pil_bool_t ret = pil_false;
        size_t requiredLen = PIL_MSG_HEADER_SIZE + dataLen;
        size_t acquiredLen = requiredLen;

        pil_mutex_lock(&mutexPopQueue);
        pData = lsrBuffer.WriterReserve(acquiredLen);

        if (pData && acquiredLen >= requiredLen)
        {
            pData[0] = static_cast<uint8_t>(connection);
            pData[1] = static_cast<uint8_t>((dataLen >> 24));
            pData[2] = static_cast<uint8_t>((dataLen >> 16));
            pData[3] = static_cast<uint8_t>((dataLen >> 8));
            pData[4] = static_cast<uint8_t>((dataLen));

            memcpy(&pData[PIL_MSG_HEADER_SIZE], data, dataLen);
            lsrBuffer.WriterRelease(acquiredLen);

            pil_event_assign(&ev, &dataAvailableEvent[ConnectionIndex::PILConn_Lsr]);
            dataWritten[connection]+=acquiredLen;
            pil_mutex_unlock(&mutexPopQueue);
            pil_event_set(&ev);
            ret = pil_true;
        }
        else
        {
            pil_mutex_unlock(&mutexPopQueue);
        }
        return ret;
    }
    else
    {
        return pil_false;
    }
}

extern "C" {
    static void PIL_setWaitForNewMessageEvent(PILMailbox connection, pil_event_t* ev);

    void pilInit()
    {
        if (!initialized)
        {
            pil_mutex_create(&mutexPopQueue, mutexLSRQueueID);
            pil_mutex_create(&mutexFUQueue, mutexFUQueueID);

            // Reinitialize circle buffers, cleanup old data
            lsrBuffer.Flush();

            for (int i = 0; i < ConnectionIndex::PILConn_Last - 1; ++i)
            {
                FUBuffers[i].Flush();
                initializedFu[i] = false;
            }
            initializedLSR = false;

            initialized = true;
        }
    }

    void pilClose()
    {
        if (initialized)
        {
            initialized = false;

            // Reinitialize circle buffers, cleanup old data
            lsrBuffer.Flush();

            for (int i = 0; i < ConnectionIndex::PILConn_Last - 1; ++i)
            {
                FUBuffers[i].Flush();
                initializedFu[i] = false;
            }
            initializedLSR = false;

            pil_mutex_destroy(&mutexPopQueue);
            pil_mutex_destroy(&mutexFUQueue);
        }
    }


    PILError pilMailboxInit(PILMailbox connection)
    {
        PILError ret = PilCheckInit();
        // in theory condition variables could be used for the FUApps, too
        // in the past these seemed to be only used by the engine
        ret = (PIL_NO_ERROR == ret) ? PilCheckMbox(connection) : ret;

        if (PIL_MBOX_NOT_INITIALIZED == ret)
        {
            if (ConnectionIndex::PILConn_Lsr == connection)
            {
                pil_event_t m_fUToPopMsgEvent;
                pil_event_create(&m_fUToPopMsgEvent, EV_Pop_FUToPop_Msg_Id);

                PIL_setWaitForNewMessageEvent(connection, &m_fUToPopMsgEvent);
                initializedLSR = true;
                ret = PIL_NO_ERROR;
            }
            else
            {
                initializedFu[connection - 1] = true;
                ret = PIL_NO_ERROR;
            }
        }

        return ret;
    }

    PILError pilMailboxPop(PILMailbox connection)
    {
        PILError ret = PilCheckInit();
        ret = (PIL_NO_ERROR == ret) ? PilCheckMbox(connection) : ret;

        if (PIL_NO_ERROR == ret)
        {
            if (connection == ConnectionIndex::PILConn_Lsr)
            {
                pil_mutex_lock(&mutexPopQueue);
                if (lastMessageSize[ConnectionIndex::PILConn_Lsr])
                {
                    dataWritten[lastPopMessageConnection] -= lastMessageSize[ConnectionIndex::PILConn_Lsr];
                    lsrBuffer.ReaderRelease(lastMessageSize[ConnectionIndex::PILConn_Lsr]);
                    lastMessageSize[ConnectionIndex::PILConn_Lsr] = 0;
                }
                pil_mutex_unlock(&mutexPopQueue);
                ret = PIL_NO_ERROR;
            }
            else
            {
                pil_mutex_lock(&mutexFUQueue);
                if(lastMessageSize[connection])
                {
                    FUBuffers[connection].ReaderRelease(lastMessageSize[connection]);
                    lastMessageSize[connection] = 0;
                }
                pil_mutex_unlock(&mutexFUQueue);
                ret = PIL_NO_ERROR;
            }
        }

        return ret;
    }

    void PIL_setWaitForNewMessageEvent(PILMailbox connection, pil_event_t* ev)
    {
        PILError ret = PilCheckInit();
        ret = (PIL_NO_ERROR == ret) ? PilCheckMbox(connection) : ret;

        if (PIL_NO_ERROR == ret)
        {
            if (connection == ConnectionIndex::PILConn_Lsr)
            {
                pil_mutex_lock(&mutexPopQueue);
                pil_event_assign(&dataAvailableEvent[connection], ev);
                pil_mutex_unlock(&mutexPopQueue);
            }
            else
            {
                pil_mutex_lock(&mutexFUQueue);
                pil_event_assign(&dataAvailableEvent[connection], ev);
                pil_mutex_unlock(&mutexFUQueue);
            }
        }
    }

    PILError pilMailboxGet(PILMailbox connection, PILMailbox *from, uint8_t** data, uint32_t *dataLen)
    {
        PILError retValue = PilCheckInit();
        retValue = (PIL_NO_ERROR == retValue) ? PilCheckMbox(connection) : retValue;

        *data = NULL;
        *dataLen = 0;

        if (PIL_NO_ERROR == retValue)
        {
            if (connection == ConnectionIndex::PILConn_Lsr)
            {
                retValue = (pil_true == PilPopGetMsg(from, data, dataLen)) ? PIL_NO_ERROR : ((0 == *dataLen) ? PIL_NO_ERROR : PIL_INVALID_MSG);
                return retValue;
            }
            size_t requiredSize = PIL_MSG_HEADER_SIZE;
            size_t acquiredSize = requiredSize;

            pil_mutex_lock(&mutexFUQueue);
            uint8_t* d = FUBuffers[connection].ReaderReserve(acquiredSize);
            pil_mutex_unlock(&mutexFUQueue);
            if(d && acquiredSize >= requiredSize)
            {
                *from=static_cast<PILMailbox>(d[0]);
                *dataLen = (static_cast<uint32_t>(d[1])) << 24;
                *dataLen |= (static_cast<uint32_t>(d[2])) << 16;
                *dataLen |= (static_cast<uint32_t>(d[3])) << 8;
                *dataLen |= (static_cast<uint32_t>(d[4]));

                /* Without a release, do another reserve */
                acquiredSize = requiredSize = *dataLen + PIL_MSG_HEADER_SIZE;
                /* Get pointer to aquired message header*/
                d = FUBuffers[connection].ReaderReserve(acquiredSize);
                if (d && acquiredSize >= requiredSize)
                {
                    lastMessageSize[connection] = requiredSize;
                    /* Get pointer to aquired data without message header*/
                    *data = d + PIL_MSG_HEADER_SIZE;
                    retValue = PIL_NO_ERROR;
                    return retValue;
                }
                else
                {   // header without data
                    retValue = PIL_INVALID_MSG;
                    return retValue;
                }
            }
            else
            {   // no messages
                retValue = PIL_NO_ERROR;
                return retValue;
            }
        }

        return retValue;
    }

    PILError pilMailboxWrite(PILMailbox to, PILMailbox from, const uint8_t* data, uint32_t dataLen)
    {
        PILError ret = PilCheckInit();
        ret = (PIL_NO_ERROR == ret) ? PilCheckMbox(to) : ret;

        if (PIL_UNKNOWN_MAILBOX == from)
        {
            ret = PIL_MBOX_INVALID;
        }

        if (NULL == data && 0 != dataLen)
        {
            ret = PIL_UNKNOWN_ERROR;
        }

        if (PIL_NO_ERROR == ret)
        {
            if (to == ConnectionIndex::PILConn_Lsr)
            {
                return (pil_true == PilWriteToPopMsg(from, data, dataLen)) ? PIL_NO_ERROR : PIL_UNKNOWN_ERROR;
            }
            pil_event_t ev;

            uint8_t *pData;
            size_t requiredLen = PIL_MSG_HEADER_SIZE + dataLen;
            size_t acquiredLen = requiredLen;

            pil_mutex_lock(&mutexFUQueue);
            pData = FUBuffers[to].WriterReserve(acquiredLen);

            if (pData && acquiredLen >= requiredLen)
            {
                pData[0] = (uint8_t)from;
                pData[1] = static_cast<uint8_t>((dataLen >> 24));
                pData[2] = static_cast<uint8_t>((dataLen >> 16));
                pData[3] = static_cast<uint8_t>((dataLen >> 8));
                pData[4] = static_cast<uint8_t>((dataLen));

                memcpy(&pData[PIL_MSG_HEADER_SIZE], data, dataLen);

                FUBuffers[to].WriterRelease(requiredLen);

                pil_event_assign(&ev,&dataAvailableEvent[to]);
                pil_mutex_unlock(&mutexFUQueue);
                pil_event_set(&ev);
                ret = PIL_NO_ERROR;
            }
            else
            {
                pil_mutex_unlock(&mutexFUQueue);
            }
        }

        return ret;
    }

    PILError pilMailboxWait(PILMailbox connection, uint32_t msTimeout)
    {
        PILError ret = PilCheckInit();
        ret = (PIL_NO_ERROR == ret) ? PilCheckMbox(connection) : ret;

        if (PIL_NO_ERROR == ret)
        {
            if (msTimeout)
            {
                if (connection == ConnectionIndex::PILConn_Lsr)
                {
                    pil_event_wait_timeout(&dataAvailableEvent[connection], msTimeout);
                }
            }
        }

        return ret;
    }

    void pilError(uint32_t errorCode, const char* msg)
    {
        printf("pilError: %d %s\n", static_cast<int>(errorCode), msg);
    }

    void pilTrace(const char* msg)
    {
        printf("%s\n", msg);
    }

    void pilAssert(const char* msg, const char* file, int lineNo)
    {
        printf("Assertion failed in %s (%d): %s\n", file, lineNo, msg);
        abort();
    }
}
