/******************************************************************************
**
**   File:        PilMsgTransmitter.cpp
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
#include "pil.h"
#include "LSRError.h"
#include "OdiTypes.h"

namespace lsr
{

LSRError convertErrorPil2Lsr(PILError errCode)
{
    LSRError retErrCode = LSR_UNKNOWN_ERROR;

    switch(errCode)
    {
        case PIL_NO_ERROR:
            retErrCode = LSR_NO_ERROR;
            break;
        case PIL_NOT_INITIALIZED:
            retErrCode = LSR_PIL_NOT_INITIALIZED;
            break;
        case PIL_MBOX_NOT_INITIALIZED:
            retErrCode = LSR_PIL_MBOX_NOT_INITIALIZED;
            break;
        case PIL_MBOX_INVALID:
            retErrCode = LSR_PIL_MBOX_INVALID;
            break;
        case PIL_BUFFER_OVERFLOW:
            retErrCode = LSR_PIL_BUFFER_OVERFLOW;
            break;
        case PIL_INVALID_MSG:
            retErrCode = LSR_PIL_INVALID_MSG;
            break;
        default:
            retErrCode = LSR_UNKNOWN_ERROR;
            break;
    }
    return retErrCode;
}

LSRError PilMsgTransmitter::transmitMessage(const U8* data, U32 dataLen)
{
    return convertErrorPil2Lsr(pilMailboxWrite(m_to, m_from, data, dataLen));
}

void PilMsgTransmitter::setConnection(PILMailbox from, PILMailbox to)
{
    m_from = from;
    m_to = to;
}

} // namespace lsr

/*! @} */
