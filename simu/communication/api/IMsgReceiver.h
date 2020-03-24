#ifndef LUXOFTSAFERENDERER_IMSGRECEIVER_H
#define LUXOFTSAFERENDERER_IMSGRECEIVER_H

/******************************************************************************
**
**   File:        IMsgReceiver.h
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

class IMsgTransmitter;
class InputStream;

/**
 * Interface that should be implemented for any class receiving ODI messages.
 */
class IMsgReceiver
{
public:

    /**
     * Default destructor.
     */
    virtual ~IMsgReceiver() {}

    /**
    *   Called when a new message with a registered message type has been received.
    *
    *   @param[in] pMsgTransmitter The transmitter for this connection
    *   @param[in] messageType Message type for this message
    *   @param[in] stream object with incoming data. See @c lsr::InputStream
    *   @return COM_NO_ERROR for success, error code otherwise
    */
    virtual ComError onMessage(IMsgTransmitter* const pMsgTransmitter,
        const U8 messageType,
        InputStream& stream) = 0;

    /**
    *   Called when there has been a successful connection.
    *
    *   @param[in] pMsgTransmitter The transmitter for this connection.
    */
    virtual void onConnect(IMsgTransmitter* const pMsgTransmitter) = 0;

    /**
    *   Called when there has been an unsuccessful connection attempt or when a
    *   connection has been disconnected.
    *
    *   \note The transmitter object should not be used after this;
    *         any references must be removed.
    *
    *   @param[in] pMsgTransmitter The transmitter for this connection.
    */
    virtual void onDisconnect(IMsgTransmitter* const pMsgTransmitter) = 0;

};

} // namespace lsr

/*! @} */

#endif // LUXOFTSAFERENDERER_IMSGRECEIVER_H
