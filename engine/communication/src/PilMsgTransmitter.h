#ifndef LUXOFTSAFERENDERER_PILMSGTRANSMITTER_H
#define LUXOFTSAFERENDERER_PILMSGTRANSMITTER_H

/******************************************************************************
**
**   File:        PilMsgTransmitter.h
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

#include "IMsgTransmitter.h"
#include "pil.h"
#include "LSRError.h"
#include "LsrTypes.h"

/*!
* @addtogroup lsr
* @{
*/
namespace lsr
{

LSRError convertErrorPil2Lsr(PILError errCode);

/**
 * @reqid SW_ENG_002, SW_ENG_129
 */
class PilMsgTransmitter: public IMsgTransmitter
{
public:
    PilMsgTransmitter()
        : m_from(PIL_UNKNOWN_MAILBOX), m_to(PIL_UNKNOWN_MAILBOX)
    {}

    virtual LSRError transmitMessage(const U8* data, U32 dataLen) P_OVERRIDE;

    void setConnection(PILMailbox from, PILMailbox to);
    PILMailbox getFrom() const;
    PILMailbox getTo() const;

private:
    PILMailbox m_from;
    PILMailbox m_to;
};

inline PILMailbox PilMsgTransmitter::getFrom() const
{
    return m_from;
}

inline PILMailbox PilMsgTransmitter::getTo() const
{
    return m_to;
}

} // namespace lsr

/*! @} */
#endif // LUXOFTSAFERENDERER_PILMSGTRANSMITTER_H
