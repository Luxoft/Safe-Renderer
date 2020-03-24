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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "ComError.h"
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
    * @return COM_NO_ERROR for success, error code otherwise. See @ComError.
    *
    **/
    virtual ComError registerMsgReceiver(IMsgReceiver* const pMsgReceiver, const U8 messageType,
                                         const U32 minPayload = NO_PAYLOAD_LIMIT, const U32 maxPayload = NO_PAYLOAD_LIMIT) = 0;

    /**
    * Unregister a message receiver.
    *
    * @param pMsgReceiver The receiver that wants to unregister.
    * @param messageType The type of message to unregister from.
    * @return COM_NO_ERROR for success, error code otherwise.
    *
    **/
    virtual ComError unregisterMsgReceiver(IMsgReceiver* const pMsgReceiver, const U8 messageType) = 0;

    /**
    * Unregister all message receivers.
    **/
    virtual void unregisterAllMsgReceivers() = 0;

    /**
     * Handles incoming data.
     *
     * @param msTimeout Maximum time to wait for new data.
     * @return COM_NO_ERROR for success, error code otherwise.
     *
     */
    virtual ComError handleIncomingData(const U32 msTimeout) = 0;
};

} // namespace lsr

/*! @} */

#endif // LUXOFTSAFERENDERER_IMSGDISPATCHER_H
