#ifndef POPULUSSC_IFUCONNECTION_H
#define POPULUSSC_IFUCONNECTION_H

/******************************************************************************
**
**   File:        IFuConnection.h
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

#include "PgwMsgTransmitter.h"

/*!
* @addtogroup psc
* @{
*/

namespace psc
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
    * @param[in] The pointer to PgwMsgTransmitter transmitter object.
    * @return PSC_NO_ERROR for success, error code otherwise.
    *
    */
    virtual PSCError registerFu(PgwMsgTransmitter*) = 0;
};

} // namespace psc

/*! @} */

#endif // POPULUSSC_IFUCONNECTION_H
