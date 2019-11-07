/******************************************************************************
**
**   File:        DataHandler.cpp
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

#include "Assertion.h"
#include "DataHandler.h"
#include "Database.h"
#include "DDHType.h"
#include "FUClassType.h"
#include "DynamicDataEntryType.h"
#include "LsrTypes.h"
#include "pil.h"

#include <algorithm>

namespace
{
    // TODO: find common place - check if overflow is implemented correctly
    bool isElapsed(const U32 startTime, const U32 timeout)
    {
        const U32 currentTime = pilGetMonotonicTime();
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

namespace lsr
{

bool DynamicDataEntry_Comparer::operator()(DynamicDataEntry const& entry, const U32 value) const
{
    return key(entry.fu->fUClassId, entry.data->dataId) < value;
}

DataHandler::DataHandler(const Database& db)
: IDataHandler()
, m_numDataEntries(0U)
, m_error(LSR_NO_ERROR)
{
    const DDHType* const ddh = db.getDdh();
    if (NULL != ddh)
    {
        for (U16 i = 0u; i < ddh->GetFUCount(); ++i)
        {
            const FUClassType* fu = ddh->GetFU(i);
            ASSERT(NULL != fu);
            for (U16 k = 0u; k < fu->GetDynamicDataEntryCount(); ++k)
            {
                const DynamicDataEntryType* data = fu->GetDynamicDataEntry(k);
                ASSERT(NULL != data);
                if (m_numDataEntries < MAX_DYNAMIC_DATA)
                {
                    m_dataEntries[m_numDataEntries].fu = fu;
                    m_dataEntries[m_numDataEntries].data = data;
                    m_dataEntries[m_numDataEntries].value = 0U;
                    m_dataEntries[m_numDataEntries].timestamp = 0U;
                    m_dataEntries[m_numDataEntries].status = fu->GetInternal() ? DataStatus::VALID : DataStatus::NOT_AVAILABLE;
                    ++m_numDataEntries;
                }
                else
                {
                    m_error = LSR_DB_ERROR;
                }
            }
        }
    }
    else
    {
        m_error = LSR_DB_ERROR;
    }
}

DataStatus DataHandler::getNumber(const DynamicData& dataId,
    Number &value) const
{
    const DynamicDataEntry* const entry = find(dataId);
    DataStatus status = DataStatus::NOT_AVAILABLE;
    if (NULL != entry)
    {
        value = Number(entry->value, entry->data->GetDataType());
        const U16 repeatTimeout = entry->data->GetRepeatTimeout();
        status = entry->status;
        if (repeatTimeout > 0U)
        {
            // check for aged data
            if (isElapsed(entry->timestamp, static_cast<U32>(repeatTimeout)))
            {
                status = DataStatus::NOT_AVAILABLE;
            }
        }
    }
    return status;
}

bool DataHandler::setData(const DynamicData& dataId,
    const Number& value,
    const DataStatus status)
{
    bool success = false;
    DynamicDataEntry* const entry = find(dataId);
    if ((NULL != entry) && (entry->data->GetDataType() == value.getType()))
    {
        entry->value = value.getU32();
        entry->status = status;
        entry->timestamp = pilGetMonotonicTime();
        success = true;
    }
    return success;
}

const DynamicDataEntry* DataHandler::find(const DynamicData& data) const
{
    return const_cast<DataHandler*>(this)->find(data);
}

DynamicDataEntry* DataHandler::find(const DynamicData& data)
{
    DynamicDataEntry* const pDataEntry = std::lower_bound(
        &m_dataEntries[0],
        &m_dataEntries[m_numDataEntries],
        DynamicDataEntry_Comparer::key(data.getFUClassId(), data.getDataId()),
        DynamicDataEntry_Comparer());

    return (((pDataEntry != &m_dataEntries[m_numDataEntries]) && (pDataEntry->fu->fUClassId == data.getFUClassId()) && (pDataEntry->data->dataId == data.getDataId())) ? pDataEntry : NULL);
}

}
