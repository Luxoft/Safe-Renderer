#ifndef POPULUSSC_PGWMSGTRANSMITTER_H
#define POPULUSSC_PGWMSGTRANSMITTER_H

/******************************************************************************
**
**   File:        PgwMsgTransmitter.h
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

#include "IMsgTransmitter.h"
#include "pgw.h"
#include "PSCError.h"
#include "PscTypes.h"

/*!
* @addtogroup psc
* @{
*/
namespace psc
{

PSCError convertErrorPgw2Psc(PGWError errCode);

class PgwMsgTransmitter: public IMsgTransmitter
{
public:
    PgwMsgTransmitter()
        : m_from(PGW_UNKNOWN_MAILBOX), m_to(PGW_UNKNOWN_MAILBOX)
    {}

    virtual PSCError transmitMessage(const U8* data, U32 dataLen) P_OVERRIDE;

    void setConnection(PGWMailbox from, PGWMailbox to);
    PGWMailbox getFrom() const;
    PGWMailbox getTo() const;

private:
    PGWMailbox m_from;
    PGWMailbox m_to;
};

inline PGWMailbox PgwMsgTransmitter::getFrom() const
{
    return m_from;
}

inline PGWMailbox PgwMsgTransmitter::getTo() const
{
    return m_to;
}

} // namespace psc

/*! @} */
#endif // POPULUSSC_PGWMSGTRANSMITTER_H
