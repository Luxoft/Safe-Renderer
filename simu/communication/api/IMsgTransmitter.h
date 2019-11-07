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
    * @return LSR_NO_ERROR for success, error code otherwise
    *
    */
    virtual LSRError transmitMessage(const U8* const data, const U32 dataLen) = 0;

};

} // namespace lsr

/*! @} */

#endif // LUXOFTSAFERENDERER_IMSGTRANSMITTER_H
