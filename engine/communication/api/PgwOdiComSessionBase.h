#ifndef POPULUSSC_PGWODISESSION_BASE_H
#define POPULUSSC_PGWODISESSION_BASE_H

/******************************************************************************
**
**   File:        PgwOdiComSessionBase.h
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

#include "PscTypes.h"
#include "IMsgReceiver.h"
#include "IMsgDispatcher.h"
#include "IFuConnection.h"
#include "pgw.h"
#include "PgwMsgTransmitter.h"
#include "PSCError.h"


/*!
* @addtogroup psc
* @{
*/

namespace psc
{

class OdiRecorder;

/**
 * Handles traffic from Engine to FU.
 */
class PgwOdiComSessionBase : public IMsgDispatcher
{
public:

    /**
     * @brief Constructs PgwOdiComSessionBase.
     * @param isEngine The flag that says if @c PgwOdiComSessionBase is used in the Engine
     * or in some FU application.
     */
    PgwOdiComSessionBase(const bool isEngine);

    virtual PSCError registerMsgReceiver(IMsgReceiver* pMsgReceiver, const U8 messageType,
                                     U32 minPayload = NO_PAYLOAD_LIMIT, U32 maxPayload = NO_PAYLOAD_LIMIT) P_OVERRIDE P_FINAL;

    virtual PSCError unregisterMsgReceiver(IMsgReceiver* pMsgReceiver, U8 messageType) P_OVERRIDE P_FINAL;

    virtual void unregisterAllMsgReceivers() P_OVERRIDE P_FINAL;

    virtual PSCError handleIncomingData(U32 msTimeout) P_OVERRIDE P_FINAL;

    /**
     * Sets an OdiRecorder for tracing incoming data.
     * @param pRecorder OdiRecorder instance.
     */
    void setOdiRecorder(OdiRecorder* pRecorder);

    /**
     * Calls IFuConnection::register(PgwMsgTransmitter*)
     * @param pFuConnection FuConnection instance which should be registered in @c PgwOdiComSessionBase.
     */
    PSCError activateFUConnection(IFuConnection* pFuConnection);

protected:
    /**
    *  Returns message type and pointer to the receiver with the given index.
    *  Note: If not found, returns NULL receiver pointer.
    *  @param index Index of the requested receiver.
    *  @param messageType Reference for the message type pointer of the receiver to be returned.
    *  @return receiver Pointer with the given index if success, else NULL.
    */
    virtual IMsgReceiver* getReceiver(U8 index, U8& pMessageType) = 0;

    /**
    *  Stores receiver with the given index and message type in array.
    *  @param index Index of the item where the receiver will be stored.
    *  @param pMsgReceiver Pointer to the stored receiver.
    *  @param pMessageType Message type of the receiver.
    *  @return PSC_NO_ERROR for success, error code otherwise.
    */
    virtual PSCError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) = 0;
    /**
    *  Returns pointer to the transmitter with the given index.
    *  @param index Index of the requested transmitter.
    *  @return Pointer to the transmitter with the given index for success, NULL overwise.
    */
    virtual PgwMsgTransmitter* getTransmitter(U8 index) = 0;

private:
    PSCError onMessage(PGWMailbox transmitter, const U8* data, const U32 dataLen);
    PGWMailbox getConnection();

    OdiRecorder* m_pOdiRecorder;
    const bool m_isEngine;
};

} // namespace psc

/*! @} */

#endif // POPULUSSC_PGWODISESSION_BASE_H

