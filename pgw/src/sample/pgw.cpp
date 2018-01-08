/******************************************************************************
**
**   File:        pgw.cpp
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

#include "pgw.h"
#include "pgw_platform.h"
#include "Circbuf.h"
#include "pgw_config.h"
#include <stdio.h>
#include <stdlib.h>


static Circbuf<unsigned char, PGWBuffersizeFU> FUBuffers[ConnectionIndex::PGWConn_Last - 1];
static Circbuf<unsigned char, PGWBufferSizePop> populusBuffer;
static volatile uint32_t lastMessageSize[ConnectionIndex::PGWConn_Last];
static volatile uint32_t dataWritten[ConnectionIndex::PGWConn_Last + 1] = { 0 };
static const uint32_t maxDataToPopulusPerConnection = PGWBufferSizePop * 2 / 3;

static volatile PGWMailbox lastPopMessageConnection = ConnectionIndex::PGWConn_Last;
static pgw_mutex_t mutexFUQueue;
static pgw_mutex_t mutexPopQueue;
static pgw_event_t dataAvailableEvent[ConnectionIndex::PGWConn_Last] = { 0 };
static bool initializedPopulus = false;
static bool initializedFu[ConnectionIndex::PGWConn_Last - 1] = {false};
static bool initialized = false;

// Hard-coded by customer event id which is used to give information to the Engine that someone sent it a message.
pgw_event_id_t EV_Pop_FUToPop_Msg_Id = 1;
// Fixed size of message header for current version of transport protocol.
const uint8_t PGW_MSG_HEADER_SIZE = 5;


static PGWError PgwCheckInit(void)
{
    return initialized ? PGW_NO_ERROR : PGW_NOT_INITIALIZED;
}

static PGWError PgwCheckMbox(PGWMailbox connection)
{
    PGWError retValue = PGW_NO_ERROR;

    if (connection == ConnectionIndex::PGWConn_Populus)
    {
        retValue = initializedPopulus ? retValue : PGW_MBOX_NOT_INITIALIZED;
    }
    else
    {
        if (connection < ConnectionIndex::PGWConn_Last)
        {
            retValue = initializedFu[connection - 1] ? retValue : PGW_MBOX_NOT_INITIALIZED;
        }
        else
        {
            retValue = PGW_MBOX_INVALID;
        }
    }

    return retValue;
}

static pgw_bool_t PgwPopGetMsg(PGWMailbox *connection, uint8_t** data, uint32_t *dataLen)
{
    size_t requiredSize = PGW_MSG_HEADER_SIZE;
    size_t acquiredSize = requiredSize;
    *data = NULL;
    *dataLen = 0;

    pgw_mutex_lock(&mutexPopQueue);
    uint8_t* d = populusBuffer.ReaderReserve(acquiredSize);

    if(d && acquiredSize >= requiredSize)
    {
        *connection=static_cast<PGWMailbox>(d[0]);
        *dataLen = (static_cast<uint32_t>(d[1])) << 24;
        *dataLen |= (static_cast<uint32_t>(d[2])) << 16;
        *dataLen |= (static_cast<uint32_t>(d[3])) << 8;
        *dataLen |= (static_cast<uint32_t>(d[4]));


        /* Without a release, do another reserve */
        requiredSize = acquiredSize = *dataLen + PGW_MSG_HEADER_SIZE;

        /* Get pointer to acquired data with header*/
        d = populusBuffer.ReaderReserve(acquiredSize);
        if (d && acquiredSize >= requiredSize)
        {
            lastPopMessageConnection = *connection;
            lastMessageSize[ConnectionIndex::PGWConn_Populus] = requiredSize;
            pgw_mutex_unlock(&mutexPopQueue);
            /* Get pointer to acquired data without message header*/
            *data = d + PGW_MSG_HEADER_SIZE;
            return pgw_true;
        }
        else
        {
            /* Should never happen since header and data are written
            * as 1 entity */
            pgw_mutex_unlock(&mutexPopQueue);
            return pgw_false;
        }
    }
    else
    {
        pgw_mutex_unlock(&mutexPopQueue);
        return pgw_false;
    }
}

static pgw_bool_t PgwWriteToPopMsg(PGWMailbox connection, const uint8_t* data, uint32_t dataLen)
{
    if(dataWritten[connection] < maxDataToPopulusPerConnection)
    {
        pgw_event_t ev;
        uint8_t *pData;
        pgw_bool_t ret = pgw_false;
        size_t requiredLen = PGW_MSG_HEADER_SIZE + dataLen;
        size_t acquiredLen = requiredLen;

        pgw_mutex_lock(&mutexPopQueue);
        pData = populusBuffer.WriterReserve(acquiredLen);

        if (pData && acquiredLen >= requiredLen)
        {
            pData[0] = static_cast<uint8_t>(connection);
            pData[1] = static_cast<uint8_t>((dataLen >> 24));
            pData[2] = static_cast<uint8_t>((dataLen >> 16));
            pData[3] = static_cast<uint8_t>((dataLen >> 8));
            pData[4] = static_cast<uint8_t>((dataLen));

            memcpy(&pData[PGW_MSG_HEADER_SIZE], data, dataLen);
            populusBuffer.WriterRelease(acquiredLen);

            pgw_event_assign(&ev, &dataAvailableEvent[ConnectionIndex::PGWConn_Populus]);
            dataWritten[connection]+=acquiredLen;
            pgw_mutex_unlock(&mutexPopQueue);
            pgw_event_set(&ev);
            ret = pgw_true;
        }
        else
        {
            pgw_mutex_unlock(&mutexPopQueue);
        }
        return ret;
    }
    else
    {
        return pgw_false;
    }
}

extern "C" {
    static void PGW_setWaitForNewMessageEvent(PGWMailbox connection, pgw_event_t* ev);

    void pgwInit()
    {
        if (!initialized)
        {
            pgw_mutex_create(&mutexPopQueue, mutexPopulusQueueID);
            pgw_mutex_create(&mutexFUQueue, mutexFUQueueID);

            // Reinitialize circle buffers, cleanup old data
            populusBuffer.Flush();

            for (int i = 0; i < ConnectionIndex::PGWConn_Last - 1; ++i)
            {
                FUBuffers[i].Flush();
                initializedFu[i] = false;
            }
            initializedPopulus = false;

            initialized = true;
        }
    }

    void pgwClose()
    {
        if (initialized)
        {
            initialized = false;

            // Reinitialize circle buffers, cleanup old data
            populusBuffer.Flush();

            for (int i = 0; i < ConnectionIndex::PGWConn_Last - 1; ++i)
            {
                FUBuffers[i].Flush();
                initializedFu[i] = false;
            }
            initializedPopulus = false;

            pgw_mutex_destroy(&mutexPopQueue);
            pgw_mutex_destroy(&mutexFUQueue);
        }
    }


    PGWError pgwMailboxInit(PGWMailbox connection)
    {
        PGWError ret = PgwCheckInit();
        // in theory condition variables could be used for the FUApps, too
        // in the past these seemed to be only used by the engine
        ret = (PGW_NO_ERROR == ret) ? PgwCheckMbox(connection) : ret;

        if (PGW_MBOX_NOT_INITIALIZED == ret)
        {
            if (ConnectionIndex::PGWConn_Populus == connection)
            {
                pgw_event_t m_fUToPopMsgEvent;
                pgw_event_create(&m_fUToPopMsgEvent, EV_Pop_FUToPop_Msg_Id);

                PGW_setWaitForNewMessageEvent(connection, &m_fUToPopMsgEvent);
                initializedPopulus = true;
                ret = PGW_NO_ERROR;
            }
            else
            {
                initializedFu[connection - 1] = true;
                ret = PGW_NO_ERROR;
            }
        }

        return ret;
    }

    PGWError pgwMailboxPop(PGWMailbox connection)
    {
        PGWError ret = PgwCheckInit();
        ret = (PGW_NO_ERROR == ret) ? PgwCheckMbox(connection) : ret;

        if (PGW_NO_ERROR == ret)
        {
            if (connection == ConnectionIndex::PGWConn_Populus)
            {
                pgw_mutex_lock(&mutexPopQueue);
                if (lastMessageSize[ConnectionIndex::PGWConn_Populus])
                {
                    dataWritten[lastPopMessageConnection] -= lastMessageSize[ConnectionIndex::PGWConn_Populus];
                    populusBuffer.ReaderRelease(lastMessageSize[ConnectionIndex::PGWConn_Populus]);
                    lastMessageSize[ConnectionIndex::PGWConn_Populus] = 0;
                }
                pgw_mutex_unlock(&mutexPopQueue);
                ret = PGW_NO_ERROR;
            }
            else
            {
                pgw_mutex_lock(&mutexFUQueue);
                if(lastMessageSize[connection])
                {
                    FUBuffers[connection].ReaderRelease(lastMessageSize[connection]);
                    lastMessageSize[connection] = 0;
                }
                pgw_mutex_unlock(&mutexFUQueue);
                ret = PGW_NO_ERROR;
            }
        }

        return ret;
    }

    void PGW_setWaitForNewMessageEvent(PGWMailbox connection, pgw_event_t* ev)
    {
        PGWError ret = PgwCheckInit();
        ret = (PGW_NO_ERROR == ret) ? PgwCheckMbox(connection) : ret;

        if (PGW_NO_ERROR == ret)
        {
            if (connection == ConnectionIndex::PGWConn_Populus)
            {
                pgw_mutex_lock(&mutexPopQueue);
                pgw_event_assign(&dataAvailableEvent[connection], ev);
                pgw_mutex_unlock(&mutexPopQueue);
            }
            else
            {
                pgw_mutex_lock(&mutexFUQueue);
                pgw_event_assign(&dataAvailableEvent[connection], ev);
                pgw_mutex_unlock(&mutexFUQueue);
            }
        }
    }

    PGWError pgwMailboxGet(PGWMailbox connection, PGWMailbox *from, uint8_t** data, uint32_t *dataLen)
    {
        PGWError retValue = PgwCheckInit();
        retValue = (PGW_NO_ERROR == retValue) ? PgwCheckMbox(connection) : retValue;

        *data = NULL;
        *dataLen = 0;

        if (PGW_NO_ERROR == retValue)
        {
            if (connection == ConnectionIndex::PGWConn_Populus)
            {
                retValue = (pgw_true == PgwPopGetMsg(from, data, dataLen)) ? PGW_NO_ERROR : ((0 == *dataLen) ? PGW_NO_ERROR : PGW_INVALID_MSG);
                return retValue;
            }
            size_t requiredSize = PGW_MSG_HEADER_SIZE;
            size_t acquiredSize = requiredSize;

            pgw_mutex_lock(&mutexFUQueue);
            uint8_t* d = FUBuffers[connection].ReaderReserve(acquiredSize);
            pgw_mutex_unlock(&mutexFUQueue);
            if(d && acquiredSize >= requiredSize)
            {
                *from=static_cast<PGWMailbox>(d[0]);
                *dataLen = (static_cast<uint32_t>(d[1])) << 24;
                *dataLen |= (static_cast<uint32_t>(d[2])) << 16;
                *dataLen |= (static_cast<uint32_t>(d[3])) << 8;
                *dataLen |= (static_cast<uint32_t>(d[4]));

                /* Without a release, do another reserve */
                acquiredSize = requiredSize = *dataLen + PGW_MSG_HEADER_SIZE;
                /* Get pointer to aquired message header*/
                d = FUBuffers[connection].ReaderReserve(acquiredSize);
                if (d && acquiredSize >= requiredSize)
                {
                    lastMessageSize[connection] = requiredSize;
                    /* Get pointer to aquired data without message header*/
                    *data = d + PGW_MSG_HEADER_SIZE;
                    retValue = PGW_NO_ERROR;
                    return retValue;
                }
                else
                {   // header without data
                    retValue = PGW_INVALID_MSG;
                    return retValue;
                }
            }
            else
            {   // no messages
                retValue = PGW_NO_ERROR;
                return retValue;
            }
        }

        return retValue;
    }

    PGWError pgwMailboxWrite(PGWMailbox to, PGWMailbox from, const uint8_t* data, uint32_t dataLen)
    {
        PGWError ret = PgwCheckInit();
        ret = (PGW_NO_ERROR == ret) ? PgwCheckMbox(to) : ret;

        if (PGW_UNKNOWN_MAILBOX == from)
        {
            ret = PGW_MBOX_INVALID;
        }

        if (NULL == data && 0 != dataLen)
        {
            ret = PGW_UNKNOWN_ERROR;
        }

        if (PGW_NO_ERROR == ret)
        {
            if (to == ConnectionIndex::PGWConn_Populus)
            {
                return (pgw_true == PgwWriteToPopMsg(from, data, dataLen)) ? PGW_NO_ERROR : PGW_UNKNOWN_ERROR;
            }
            pgw_event_t ev;

            uint8_t *pData;
            size_t requiredLen = PGW_MSG_HEADER_SIZE + dataLen;
            size_t acquiredLen = requiredLen;

            pgw_mutex_lock(&mutexFUQueue);
            pData = FUBuffers[to].WriterReserve(acquiredLen);

            if (pData && acquiredLen >= requiredLen)
            {
                pData[0] = (uint8_t)from;
                pData[1] = static_cast<uint8_t>((dataLen >> 24));
                pData[2] = static_cast<uint8_t>((dataLen >> 16));
                pData[3] = static_cast<uint8_t>((dataLen >> 8));
                pData[4] = static_cast<uint8_t>((dataLen));

                memcpy(&pData[PGW_MSG_HEADER_SIZE], data, dataLen);

                FUBuffers[to].WriterRelease(requiredLen);

                pgw_event_assign(&ev,&dataAvailableEvent[to]);
                pgw_mutex_unlock(&mutexFUQueue);
                pgw_event_set(&ev);
                ret = PGW_NO_ERROR;
            }
            else
            {
                pgw_mutex_unlock(&mutexFUQueue);
            }
        }

        return ret;
    }

    PGWError pgwMailboxWait(PGWMailbox connection, uint32_t msTimeout)
    {
        PGWError ret = PgwCheckInit();
        ret = (PGW_NO_ERROR == ret) ? PgwCheckMbox(connection) : ret;

        if (PGW_NO_ERROR == ret)
        {
            if (msTimeout)
            {
                if (connection == ConnectionIndex::PGWConn_Populus)
                {
                    pgw_event_wait_timeout(&dataAvailableEvent[connection], msTimeout);
                }
            }
        }

        return ret;
    }

    void pgwError(uint32_t errorCode, const char* msg)
    {
        fprintf(stderr, "pgwError: %d %s\n", errorCode, msg);
    }

    void pgwAssert(const char* msg, const char* file, int lineNo)
    {
        fprintf(stderr, "Assertion failed in %s (%d): %s\n", file, lineNo, msg);
        abort();
    }
}
