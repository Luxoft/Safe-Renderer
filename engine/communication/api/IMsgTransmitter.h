#ifndef POPULUSSC_IMSGTRANSMITTER_H
#define POPULUSSC_IMSGTRANSMITTER_H

/******************************************************************************
**
**   File:        IMsgTransmitter.h
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

#include "PSCError.h"
#include "PscTypes.h"

/*!
* @addtogroup psc
* @{
*/

namespace psc
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
    *                 message header (see @c psc::MessageHeader) and data.
    * @param[in] dataLen the length of the data in bytes
    * @return PSC_NO_ERROR for success, error code otherwise
    *
    */
    virtual PSCError transmitMessage(const U8* data, U32 dataLen) = 0;

};

} // namespace psc

/*! @} */

#endif  // POPULUSSC_IMSGTRANSMITTER_H
