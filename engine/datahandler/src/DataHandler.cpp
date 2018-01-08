/******************************************************************************
**
**   File:        DataHandler.cpp
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

#include "Assertion.h"
#include "DataHandler.h"
#include "Database.h"
#include "DDHType.h"
#include "FUDatabaseType.h"
#include "FUClassType.h"
#include "DynamicDataEntryType.h"
#include "PscTypes.h"
#include "OdiTypes.h"
#include "OdiMsgHeader.h"
#include "DataResponseMessage.h"
#include "EventMessage.h"
#include "pgw.h"

#include <algorithm>

namespace
{
    // TODO: find common place - check if overflow is implemented correctly
    bool isElapsed(const U32 startTime, const U32 timeout)
    {
        const U32 currentTime = pgwGetMonotonicTime();
        bool result = false;
        if (currentTime >= startTime)
        {
            // normal case
            result = (currentTime - startTime) > timeout;
        }
        else
        {
            // integer overflow for monotonic time
            result = (0xffffffff - (startTime - currentTime)) > timeout;
        }
        return result;
    }
}

namespace psc
{

bool DynamicDataEntry_Comparer::operator ()(DynamicDataEntry const& entry, U32 const value) const
{
    return key(entry.fu->fUClassId, entry.data->dataId) < value;
}

DataHandler::DataHandler(const Database& db)
: m_numDataEntries(0)
, m_error(PSC_NO_ERROR)
{
    const DDHType* ddh = db.getDdh();
    if (NULL != ddh)
    {
        const FUDatabaseType* fudb = ddh->GetFUDatabase();
        if (NULL != fudb)
        {
            for (U16 i = 0u; i < fudb->GetFUCount(); ++i)
            {
                const FUClassType* fu = fudb->GetFU(i);
                ASSERT(NULL != fu);
                for (U16 k = 0u; k < fu->GetDynamicDataEntryCount(); ++k)
                {
                    const DynamicDataEntryType* data = fu->GetDynamicDataEntry(k);
                    ASSERT(NULL != data);
                    if (m_numDataEntries < MAX_DYNAMIC_DATA)
                    {
                        m_dataEntries[m_numDataEntries].fu = fu;
                        m_dataEntries[m_numDataEntries].data = data;
                        m_dataEntries[m_numDataEntries].value = 0;
                        m_dataEntries[m_numDataEntries].status = fu->GetInternalFU() ? DataStatus::VALID : DataStatus::NOT_AVAILABLE;
                        ++m_numDataEntries;
                    }
                    else
                    {
                        m_error = PSC_DB_ERROR;
                    }
                }
            }
        }
        else
        {
            m_error = PSC_DB_ERROR;
        }
    }
    else
    {
        m_error = PSC_DB_ERROR;
    }
}

bool DataHandler::subscribeData(FUClassId fuClassId,
    DataId dataId,
    IDataHandler::IListener* pListener)
{
    return false;
}

bool DataHandler::subscribeIndication(FUClassId fuClassId,
    IndicationId indicationId,
    IDataHandler::IListener* pListener)
{
    return false;
}

void DataHandler::unsubscribeData(FUClassId fuClassId,
    DataId dataId,
    IDataHandler::IListener* pListener)
{
}

void DataHandler::unsubscribeIndication(FUClassId fuClassId,
    IndicationId indicationId,
    IDataHandler::IListener* pListener)
{
}

DataStatus DataHandler::getNumber(FUClassId fuClassId,
    DataId dataId,
    Number &value) const
{
    const DynamicDataEntry* entry = find(fuClassId, dataId);
    DataStatus status = DataStatus::NOT_AVAILABLE;
    if (entry)
    {
        value = Number(entry->value, entry->data->GetDataType());
        const U16 repeatTimeout = entry->data->GetRepeatTimeout();
        status = entry->status;
        if (repeatTimeout > 0)
        {
            // check for aged data
            if (isElapsed(entry->timestamp, repeatTimeout))
            {
                status = DataStatus::NOT_AVAILABLE;
            }
        }
    }
    return status;
}

DataStatus DataHandler::getIndication(FUClassId fuClassId,
    IndicationId indicationId,
    bool& value) const
{
    return DataStatus::NOT_AVAILABLE;
}

bool DataHandler::setData(FUClassId fuClassId,
    DataId dataId,
    const Number& value,
    DataStatus status)
{
    bool success = false;
    DynamicDataEntry* entry = find(fuClassId, dataId);
    if (entry && entry->data->GetDataType() == value.getType())
    {
        entry->value = value.getU32();
        entry->status = status;
        entry->timestamp = pgwGetMonotonicTime();
        success = true;
    }
    return success;
}

PSCError DataHandler::onMessage(IMsgTransmitter* pMsgTransmitter,
    const U8 messageType,
    InputStream& stream)
{
    PSCError retValue = PSC_NO_ERROR;

    // TODO: Alive and Registration messages?
    ASSERT_MSG(MessageTypes::ODI == messageType, "Invalid message type");

    const OdiMsgHeader odiMsgHeader = OdiMsgHeader::fromStream(stream);
    const DataMessageTypes::Val odiMsgType = odiMsgHeader.getOdiType();

    switch(odiMsgType)
    {
    case DataMessageTypes::DYN_DATA_RESP:
        retValue = dynamicDataResponseHandler(stream);
        break;
    case DataMessageTypes::EVENT:
    case DataMessageTypes::INDICATION:
    default:
        retValue = PSC_DH_INVALID_MESSAGE_TYPE;
        // call pgwError() ?
        break;
    };

    return retValue;
}

void DataHandler::onConnect(IMsgTransmitter* pMsgTransmitter)
{
}

void DataHandler::onDisconnect(IMsgTransmitter* pMsgTransmitter)
{
}

const DynamicDataEntry* DataHandler::find(const FUClassId fu, const DataId data) const
{
    return const_cast<DataHandler*>(this)->find(fu, data);
}

DynamicDataEntry* DataHandler::find(const FUClassId fuId, const DataId dataId)
{
    DynamicDataEntry* pDataEntry = std::lower_bound(
        &m_dataEntries[0],
        &m_dataEntries[m_numDataEntries],
        DynamicDataEntry_Comparer::key(fuId, dataId),
        DynamicDataEntry_Comparer());

    return ((pDataEntry != &m_dataEntries[m_numDataEntries] && pDataEntry->fu->fUClassId == fuId && pDataEntry->data->dataId == dataId) ? pDataEntry : NULL);
}

PSCError DataHandler::dynamicDataResponseHandler(InputStream& stream)
{
    PSCError error = PSC_NO_ERROR;
    DataResponseMessage dataResponse = DataResponseMessage::fromStream(stream);
    const U32 currentTime = pgwGetMonotonicTime();

    DynamicDataEntry* pDataEntry = find(dataResponse.getFuId(), dataResponse.getDataId());
    if (pDataEntry)
    {
        if (pDataEntry->data->GetDataType() == dataResponse.getDataType())
        {
            pDataEntry->value = dataResponse.getDataValue();
            pDataEntry->status = dataResponse.getInvalidFlag() ? DataStatus::INVALID : DataStatus::VALID;
            pDataEntry->timestamp = currentTime;
            // TODO: range check if minimum/maximum value is specified
            // TODO: Notify listeners ?
        }
        else
        {
            // FU sent wrong type
            error = PSC_DH_INVALID_MESSAGE_TYPE; // TODO: separate error ?
            // call pgwError() ?
        }
    }
    else
    {
        // Unknown FU/Data pair
        error = PSC_DH_INVALID_MESSAGE_TYPE; // TODO: separate error ?
        // call pgwError() ?
    }

    return error;
}

}
