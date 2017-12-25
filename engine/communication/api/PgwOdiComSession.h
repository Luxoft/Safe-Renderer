#ifndef POPULUSSC_PGWODISESSION_H
#define POPULUSSC_PGWODISESSION_H

/******************************************************************************
**
**   File:        PgwOdiComSession.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include "PscTypes.h"
#include "IMsgReceiver.h"
#include "PgwOdiComSessionBase.h"
#include "PgwMsgTransmitter.h"
#include "OdiTypes.h"


/*!
* @addtogroup psc
* @{
*/

namespace psc
{

/**
* PgwOdiComSession contains array of receivers having the size of @c ReceiversArrayLength
* and array of transmitters having the size of @c TransmittersArrayLength. The purpose of
* this class is to be container for receivers and transmitters.
* All functionality of communication component was separated into base class.
*/
template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
class PgwOdiComSession P_FINAL : public PgwOdiComSessionBase
{
    P_STATIC_ASSERT(TransmittersArrayLength > 0 && (TransmittersArrayLength  < U8_MAX), "Template argument TransmittersArrayLength must be greater than zero");
public:
    PgwOdiComSession(const PGWMailbox connection, const bool isEngine);

protected:
    virtual IMsgReceiver* getReceiver(U8 index, U8& messageType) P_OVERRIDE;
    virtual PSCError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE;
    virtual PgwMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE;
private:
    U8 m_receiversType[ReceiversArrayLength];
    IMsgReceiver* m_receivers[ReceiversArrayLength];
    PgwMsgTransmitter m_transmitters[TransmittersArrayLength];
};

template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
PgwOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::PgwOdiComSession(const PGWMailbox connection, const bool isEngine)
    : PgwOdiComSessionBase(isEngine)
{
    for (U8 receiverIndex = 0; receiverIndex < ReceiversArrayLength; ++receiverIndex)
    {
        m_receivers[receiverIndex] = NULL;
        m_receiversType[receiverIndex] = MessageTypes::UNKNOWN;
    }

    for (U8 transmitterIndex = 0; transmitterIndex < TransmittersArrayLength; ++transmitterIndex)
    {
        m_transmitters[transmitterIndex].setConnection(connection, static_cast<PGWMailbox>(transmitterIndex));
    }
}

template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
IMsgReceiver* PgwOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::getReceiver(U8 index, U8& messageType)
{
    IMsgReceiver* pMsgReceiver = NULL;
    messageType = MessageTypes::UNKNOWN;

    if (index < ReceiversArrayLength)
    {
        pMsgReceiver = m_receivers[index];
        messageType = m_receiversType[index];
    }

    return pMsgReceiver;
}

template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
PSCError PgwOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType)
{
    PSCError errValue = PSC_SESSION_TOO_MANY_RECEIVERS;

    if (index < ReceiversArrayLength)
    {
        m_receiversType[index] = messageType;
        m_receivers[index] = pMsgReceiver;
        errValue = PSC_NO_ERROR;
    }

    return errValue;
}

template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
PgwMsgTransmitter* PgwOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::getTransmitter(U8 index)
{
    PgwMsgTransmitter* pTransmitter = NULL;

    if (index < TransmittersArrayLength)
    {
        pTransmitter = &m_transmitters[index];
    }

    return pTransmitter;
}


/**
* Partial specialization PgwOdiComSession template for zero receivers number
*/
template <U8 TransmittersArrayLength>
class PgwOdiComSession<0, TransmittersArrayLength> P_FINAL : public PgwOdiComSessionBase
{
    P_STATIC_ASSERT((TransmittersArrayLength > 0) && (TransmittersArrayLength  < U8_MAX), "Template argument TransmittersArrayLength must be greater than zero");
public:
    PgwOdiComSession(const PGWMailbox connection, const bool isEngine);

protected:
    virtual PgwMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE;
private:
    virtual IMsgReceiver* getReceiver(U8 index, U8& messageType) P_OVERRIDE;
    virtual PSCError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE;

    PgwMsgTransmitter m_transmitters[TransmittersArrayLength];
};

template <U8 TransmittersArrayLength>
PgwOdiComSession<0, TransmittersArrayLength>::PgwOdiComSession(const PGWMailbox connection, const bool isEngine)
    : PgwOdiComSessionBase(isEngine)
{
    for (U8 transmitterIndex = 0; transmitterIndex < TransmittersArrayLength; ++transmitterIndex)
    {
        m_transmitters[transmitterIndex].setConnection(connection, static_cast<PGWMailbox>(transmitterIndex));
    }
}

template <U8 TransmittersArrayLength>
IMsgReceiver* PgwOdiComSession<0, TransmittersArrayLength>::getReceiver(U8 index, U8& messageType)
{
    messageType = MessageTypes::UNKNOWN;
    return NULL;
}

template <U8 TransmittersArrayLength>
PSCError PgwOdiComSession<0, TransmittersArrayLength>::setReceiver(U8, IMsgReceiver*, const U8)
{
    return PSC_SESSION_TOO_MANY_RECEIVERS;
}

template <U8 TransmittersArrayLength>
PgwMsgTransmitter* PgwOdiComSession<0, TransmittersArrayLength>::getTransmitter(U8 index)
{
    PgwMsgTransmitter* pTransmitter = NULL;

    if (index < TransmittersArrayLength)
    {
        pTransmitter = &m_transmitters[index];
    }

    return pTransmitter;
}

} // namespace psc
/*! @} */

#endif // POPULUSSC_PGWODISESSION_H
