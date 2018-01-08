/******************************************************************************
**
**   File:        PgwMsgTransmitter.cpp
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
#include "pgw.h"
#include "PSCError.h"
#include "OdiTypes.h"

namespace psc
{

PSCError convertErrorPgw2Psc(PGWError errCode)
{
    PSCError retErrCode = PSC_UNKNOWN_ERROR;

    switch(errCode)
    {
        case PGW_NO_ERROR:
            retErrCode = PSC_NO_ERROR;
            break;
        case PGW_NOT_INITIALIZED:
            retErrCode = PSC_PGW_NOT_INITIALIZED;
            break;
        case PGW_MBOX_NOT_INITIALIZED:
            retErrCode = PSC_PGW_MBOX_NOT_INITIALIZED;
            break;
        case PGW_MBOX_INVALID:
            retErrCode = PSC_PGW_MBOX_INVALID;
            break;
        case PGW_BUFFER_OVERFLOW:
            retErrCode = PSC_PGW_BUFFER_OVERFLOW;
            break;
        case PGW_INVALID_MSG:
            retErrCode = PSC_PGW_INVALID_MSG;
            break;
        default:
            retErrCode = PSC_UNKNOWN_ERROR;
            break;
    }
    return retErrCode;
}

PSCError PgwMsgTransmitter::transmitMessage(const U8* data, U32 dataLen)
{
    return convertErrorPgw2Psc(pgwMailboxWrite(m_to, m_from, data, dataLen));
}

void PgwMsgTransmitter::setConnection(PGWMailbox from, PGWMailbox to)
{
    m_from = from;
    m_to = to;
}

} // namespace psc

/*! @} */
