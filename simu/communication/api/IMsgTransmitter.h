#ifndef LUXOFTSAFERENDERER_IMSGTRANSMITTER_H
#define LUXOFTSAFERENDERER_IMSGTRANSMITTER_H

/******************************************************************************
**
**   File:        IMsgTransmitter.h
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

/**
 * Interface implemented for classes that send messages.
 */
class IMsgTransmitter
{
public:

    /**
     * Default destructor.
     */
    virtual ~IMsgTransmitter(){}

    /**
    * Send a message.
    *
    * @param[in] data pointer to the data to send. This data should have
    *                 message header (see @c lsr::MessageHeader) and data.
    * @param[in] dataLen the length of the data in bytes
    * @return COM_NO_ERROR for success, error code otherwise
    *
    */
    virtual ComError transmitMessage(const U8* const data, const U32 dataLen) = 0;

};

} // namespace lsr

/*! @} */

#endif // LUXOFTSAFERENDERER_IMSGTRANSMITTER_H
