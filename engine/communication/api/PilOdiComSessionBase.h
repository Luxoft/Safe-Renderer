#ifndef LUXOFTSAFERENDERER_PILODISESSION_BASE_H
#define LUXOFTSAFERENDERER_PILODISESSION_BASE_H

/******************************************************************************
**
**   File:        PilOdiComSessionBase.h
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

#include "LsrTypes.h"
#include "IMsgReceiver.h"
#include "IMsgDispatcher.h"
#include "IFuConnection.h"
#include "pil.h"
#include "PilMsgTransmitter.h"
#include "LSRError.h"


/*!
* @addtogroup lsr
* @{
*/

namespace lsr
{

class OdiRecorder;

/**
 * Handles traffic from Engine to FU.
 *
 * @reqid SW_ENG_001, SW_ENG_127, SW_ENG_130, SW_ENG_132, SW_ENG_133
 */
class PilOdiComSessionBase : public IMsgDispatcher
{
public:

    /**
     * @brief Constructs PilOdiComSessionBase.
     * @param isEngine The flag that says if @c PilOdiComSessionBase is used in the Engine
     * or in some FU application.
     */
    PilOdiComSessionBase(const bool isEngine);

    virtual LSRError registerMsgReceiver(IMsgReceiver* pMsgReceiver, const U8 messageType,
                                     U32 minPayload = NO_PAYLOAD_LIMIT, U32 maxPayload = NO_PAYLOAD_LIMIT) P_OVERRIDE P_FINAL;

    virtual LSRError unregisterMsgReceiver(IMsgReceiver* pMsgReceiver, U8 messageType) P_OVERRIDE P_FINAL;

    virtual void unregisterAllMsgReceivers() P_OVERRIDE P_FINAL;

    virtual LSRError handleIncomingData(U32 msTimeout) P_OVERRIDE P_FINAL;

    /**
     * Sets an OdiRecorder for tracing incoming data.
     * @param pRecorder OdiRecorder instance.
     */
    void setOdiRecorder(OdiRecorder* pRecorder);

    /**
     * Calls IFuConnection::register(PilMsgTransmitter*)
     * @param pFuConnection FuConnection instance which should be registered in @c PilOdiComSessionBase.
     */
    LSRError activateFUConnection(IFuConnection* pFuConnection);

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
    *  @return LSR_NO_ERROR for success, error code otherwise.
    */
    virtual LSRError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) = 0;
    /**
    *  Returns pointer to the transmitter with the given index.
    *  @param index Index of the requested transmitter.
    *  @return Pointer to the transmitter with the given index for success, NULL overwise.
    */
    virtual PilMsgTransmitter* getTransmitter(U8 index) = 0;

private:
    LSRError onMessage(PILMailbox transmitter, const U8* data, const U32 dataLen);
    PILMailbox getConnection();

    OdiRecorder* m_pOdiRecorder;
    const bool m_isEngine;
};

} // namespace lsr

/*! @} */

#endif // LUXOFTSAFERENDERER_PILODISESSION_BASE_H

