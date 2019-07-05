#ifndef LUXOFTSAFERENDERER_PILODISESSION_H
#define LUXOFTSAFERENDERER_PILODISESSION_H

/******************************************************************************
**
**   File:        PilOdiComSession.h
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

#include "LsrTypes.h"
#include "IMsgReceiver.h"
#include "PilOdiComSessionBase.h"
#include "PilMsgTransmitter.h"
#include "OdiTypes.h"


/*!
* @addtogroup lsr
* @{
*/

namespace lsr
{

/**
* PilOdiComSession contains array of receivers having the size of @c ReceiversArrayLength
* and array of transmitters having the size of @c TransmittersArrayLength. The purpose of
* this class is to be container for receivers and transmitters.
* All functionality of communication component was separated into base class.
*
* @reqid SW_ENG_126
*/
template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
class PilOdiComSession P_FINAL : public PilOdiComSessionBase
{
    P_STATIC_ASSERT(TransmittersArrayLength > 0 && (TransmittersArrayLength  < U8_MAX), "Template argument TransmittersArrayLength must be greater than zero");
public:
    PilOdiComSession(const PILMailbox connection, const bool isEngine);

protected:
    virtual IMsgReceiver* getReceiver(U8 index, U8& messageType) P_OVERRIDE;
    virtual LSRError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE;
    virtual PilMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE;
private:
    U8 m_receiversType[ReceiversArrayLength];
    IMsgReceiver* m_receivers[ReceiversArrayLength];
    PilMsgTransmitter m_transmitters[TransmittersArrayLength];
};

template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
PilOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::PilOdiComSession(const PILMailbox connection, const bool isEngine)
    : PilOdiComSessionBase(isEngine)
{
    for (U8 receiverIndex = 0; receiverIndex < ReceiversArrayLength; ++receiverIndex)
    {
        m_receivers[receiverIndex] = NULL;
        m_receiversType[receiverIndex] = MessageTypes::UNKNOWN;
    }

    for (U8 transmitterIndex = 0; transmitterIndex < TransmittersArrayLength; ++transmitterIndex)
    {
        m_transmitters[transmitterIndex].setConnection(connection, static_cast<PILMailbox>(transmitterIndex));
    }
}

template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
IMsgReceiver* PilOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::getReceiver(U8 index, U8& messageType)
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
LSRError PilOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType)
{
    LSRError errValue = LSR_SESSION_TOO_MANY_RECEIVERS;

    if (index < ReceiversArrayLength)
    {
        m_receiversType[index] = messageType;
        m_receivers[index] = pMsgReceiver;
        errValue = LSR_NO_ERROR;
    }

    return errValue;
}

template <U8 ReceiversArrayLength, U8 TransmittersArrayLength>
PilMsgTransmitter* PilOdiComSession<ReceiversArrayLength, TransmittersArrayLength>::getTransmitter(U8 index)
{
    PilMsgTransmitter* pTransmitter = NULL;

    if (index < TransmittersArrayLength)
    {
        pTransmitter = &m_transmitters[index];
    }

    return pTransmitter;
}


/**
* Partial specialization PilOdiComSession template for zero receivers number
*/
template <U8 TransmittersArrayLength>
class PilOdiComSession<0, TransmittersArrayLength> P_FINAL : public PilOdiComSessionBase
{
    P_STATIC_ASSERT((TransmittersArrayLength > 0) && (TransmittersArrayLength  < U8_MAX), "Template argument TransmittersArrayLength must be greater than zero");
public:
    PilOdiComSession(const PILMailbox connection, const bool isEngine);

protected:
    virtual PilMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE;
private:
    virtual IMsgReceiver* getReceiver(U8 index, U8& messageType) P_OVERRIDE;
    virtual LSRError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE;

    PilMsgTransmitter m_transmitters[TransmittersArrayLength];
};

template <U8 TransmittersArrayLength>
PilOdiComSession<0, TransmittersArrayLength>::PilOdiComSession(const PILMailbox connection, const bool isEngine)
    : PilOdiComSessionBase(isEngine)
{
    for (U8 transmitterIndex = 0; transmitterIndex < TransmittersArrayLength; ++transmitterIndex)
    {
        m_transmitters[transmitterIndex].setConnection(connection, static_cast<PILMailbox>(transmitterIndex));
    }
}

template <U8 TransmittersArrayLength>
IMsgReceiver* PilOdiComSession<0, TransmittersArrayLength>::getReceiver(U8 index, U8& messageType)
{
    messageType = MessageTypes::UNKNOWN;
    return NULL;
}

template <U8 TransmittersArrayLength>
LSRError PilOdiComSession<0, TransmittersArrayLength>::setReceiver(U8, IMsgReceiver*, const U8)
{
    return LSR_SESSION_TOO_MANY_RECEIVERS;
}

template <U8 TransmittersArrayLength>
PilMsgTransmitter* PilOdiComSession<0, TransmittersArrayLength>::getTransmitter(U8 index)
{
    PilMsgTransmitter* pTransmitter = NULL;

    if (index < TransmittersArrayLength)
    {
        pTransmitter = &m_transmitters[index];
    }

    return pTransmitter;
}

} // namespace lsr
/*! @} */

#endif // LUXOFTSAFERENDERER_PILODISESSION_H
