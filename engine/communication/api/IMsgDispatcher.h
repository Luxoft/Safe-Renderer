#ifndef LUXOFTSAFERENDERER_IMSGDISPATCHER_H
#define LUXOFTSAFERENDERER_IMSGDISPATCHER_H

/******************************************************************************
**
**   File:        IMsgDispatcher.h
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

#include "LSRError.h"
#include "LsrTypes.h"

/*!
* @addtogroup lsr
* @{
*/

namespace lsr
{

class IMsgReceiver;

/**
 * Interface used for message dispatching.
 */
class IMsgDispatcher
{
public:
    enum
    {
        NO_PAYLOAD_LIMIT = 0 //! Indicates that there is no limit on the payload
    };

    /**
     * Default destructor.
     */
    virtual ~IMsgDispatcher() {}

    /**
    * Register a message receiver. The dispatcher will dispatch messages and call the receiver's
    * IMsgReceiver::onMessage() callback function for messages of type messageType.
    *
    * \note If a message outside the limits is received, aborting the connection is recommended.
    *
    * @param pMsgReceiver The receiver that wants to receive messages.
    * @param messageType The type of message to receive.
    * @param minPayload The minimum accepted payload. Set to NO_PAYLOAD_LIMIT for no limit.
    * @param maxPayload The maximum accepted payload. Set to NO_PAYLOAD_LIMIT for no limit.
    * @return LSR_NO_ERROR for success, error code otherwise. See @LSRError.
    *
    **/
    virtual LSRError registerMsgReceiver(IMsgReceiver* pMsgReceiver, const U8 messageType,
                                     U32 minPayload = NO_PAYLOAD_LIMIT, U32 maxPayload = NO_PAYLOAD_LIMIT) = 0;

    /**
    * Unregister a message receiver.
    *
    * @param pMsgReceiver The receiver that wants to unregister.
    * @param messageType The type of message to unregister from.
    * @return LSR_NO_ERROR for success, error code otherwise.
    *
    **/
    virtual LSRError unregisterMsgReceiver(IMsgReceiver* pMsgReceiver, U8 messageType) = 0;

    /**
    * Unregister all message receivers.
    **/
    virtual void unregisterAllMsgReceivers() = 0;

    /**
     * Handles incoming data.
     *
     * @param msTimeout Maximum time to wait for new data.
     * @return LSR_NO_ERROR for success, error code otherwise.
     *
     */
    virtual LSRError handleIncomingData(U32 msTimeout) = 0;
};

} // namespace lsr

/*! @} */

#endif // LUXOFTSAFERENDERER_IMSGDISPATCHER_H
