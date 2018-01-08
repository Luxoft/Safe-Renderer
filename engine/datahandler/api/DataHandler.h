#ifndef POPULUSSC_DATAHANDLER_H
#define POPULUSSC_DATAHANDLER_H

/******************************************************************************
**
**   File:        DataHandler.h
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

#include "IDataHandler.h"
#include "IMsgReceiver.h"
#include "InputStream.h"
#include "PscLimits.h"

namespace psc
{

class Database;
struct DynamicDataEntryType;
struct FUClassType;

struct DynamicDataEntry
{
    const FUClassType* fu; ///< FU DB information
    const DynamicDataEntryType* data; ///< Dynamic Data DB information
    U32 value; ///< Raw data value
    U32 timestamp; ///< Timestamp of last data update
    DataStatus status; ///< Validity information
};

struct DynamicDataEntry_Comparer
{
    static U32 key(FUClassId fuId, DataId dataId);
    bool operator ()(struct DynamicDataEntry const& entry, U32 const value) const;
};

inline U32 DynamicDataEntry_Comparer::key(FUClassId fuId, DataId dataId)
{
    return ((fuId << 16) | dataId);
}


class DataHandler : public IDataHandler, public IMsgReceiver
{
public:
    explicit DataHandler(const Database& db);

    // IDataHandler
    virtual bool subscribeData(FUClassId fuClassId,
        DataId dataId,
        IDataHandler::IListener* pListener) P_OVERRIDE;

    virtual bool subscribeIndication(FUClassId fuClassId,
        IndicationId indicationId,
        IDataHandler::IListener* pListener) P_OVERRIDE;

    virtual void unsubscribeData(FUClassId fuClassId,
        DataId dataId,
        IDataHandler::IListener* pListener) P_OVERRIDE;

    virtual void unsubscribeIndication(FUClassId fuClassId,
        IndicationId indicationId,
        IDataHandler::IListener* pListener) P_OVERRIDE;

    virtual DataStatus getNumber(FUClassId fuClassId,
        DataId dataId,
        Number &value) const P_OVERRIDE;

    virtual DataStatus getIndication(FUClassId fuClassId,
        IndicationId indicationId,
        bool& value) const P_OVERRIDE;

    virtual bool setData(FUClassId fuClassId,
        DataId dataId,
        const Number& value,
        DataStatus status) P_OVERRIDE;

    // IMsgReceiver
    virtual PSCError onMessage(IMsgTransmitter* pMsgTransmitter,
        const U8 messageType,
        InputStream& stream) P_OVERRIDE;

    virtual void onConnect(IMsgTransmitter* pMsgTransmitter) P_OVERRIDE;

    virtual void onDisconnect(IMsgTransmitter* pMsgTransmitter) P_OVERRIDE;

    PSCError dynamicDataResponseHandler(InputStream& stream);

private:
    DynamicDataEntry* find(const FUClassId fu, const DataId data);
    const DynamicDataEntry* find(const FUClassId fu, const DataId data) const;

    DynamicDataEntry m_dataEntries[MAX_DYNAMIC_DATA];
    size_t m_numDataEntries;

    PSCError m_error;
};

} // namespace datahandler

#endif // POPULUSSC_DATAHANDLER_H
