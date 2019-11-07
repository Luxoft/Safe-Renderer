#ifndef LUXOFTSAFERENDERER_IFUCONNECTION_H
#define LUXOFTSAFERENDERER_IFUCONNECTION_H

/******************************************************************************
**
**   File:        IFuConnection.h
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

#include "PilMsgTransmitter.h"

/*!
* @addtogroup lsr
* @{
*/

namespace lsr
{

/**
 * Interface for FU activation.
 */
class IFuConnection
{
public:
    /**
    * Send registration message to given transmitter.
    *
    * @param[in] The pointer to PilMsgTransmitter transmitter object.
    * @return LSR_NO_ERROR for success, error code otherwise.
    *
    */
    virtual LSRError registerFu(PilMsgTransmitter*) = 0;
};

} // namespace lsr

/*! @} */

#endif // LUXOFTSAFERENDERER_IFUCONNECTION_H
