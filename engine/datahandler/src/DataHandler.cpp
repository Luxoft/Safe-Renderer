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

#include <algorithm>

namespace lsr
{

bool DynamicDataEntry_Comparer::operator()(DynamicDataEntry const& entry, const U32 value) const
{
    return key(entry.fu->GetFUClassId(), entry.data->GetDataId()) < value;
}

DataHandler::DataHandler(const Database& db)
: IDataHandler()
, m_numDataEntries(0U)
, m_error(LSR_NO_ENGINE_ERROR)
{
    const DDHType* const ddh = db.getDdh();
    if (NULL != ddh)
    {
        for (U16 i = 0U; i < ddh->GetFUCount(); ++i)
        {
            const FUClassType* fu = ddh->GetFU(i);
            ASSERT(NULL != fu);
            for (U16 k = 0U; k < fu->GetDynamicDataEntryCount(); ++k)
            {
                const DynamicDataEntryType* const data = fu->GetDynamicDataEntry(k);
                if (REQUIRE(NULL != data) && (m_numDataEntries < MAX_DYNAMIC_DATA))
                {
                    m_dataEntries[m_numDataEntries].fu = fu;
                    m_dataEntries[m_numDataEntries].data = data;
                    m_dataEntries[m_numDataEntries].value = 0U;
                    m_dataEntries[m_numDataEntries].refreshTimer = Timer();
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

DataStatus DataHandler::getNumber(const DynamicData& id,
    Number &value) const
{
    const DynamicDataEntry* const entry = find(id);
    DataStatus status = DataStatus::NOT_AVAILABLE;
    if (NULL != entry)
    {
        value = Number(entry->value, entry->data->GetDataType());
        const U32 repeatTimeout = static_cast<U32>(entry->data->GetRepeatTimeout());
        status = entry->status;
        if (repeatTimeout > 0U)
        {
            // check for aged data
            if (entry->refreshTimer.hasExpired(repeatTimeout))
            {
                static_cast<void>(status);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
                status = DataStatus::NOT_AVAILABLE;
            }
        }
    }
    return status;
}

bool DataHandler::setData(const DynamicData& id,
    const Number& value,
    const DataStatus status)
{
    DynamicDataEntry* const entry = find(id);
    const bool found = ((NULL != entry) && (entry->data->GetDataType() == value.getType()));
    if (found)
    {
        entry->value = value.getU32();
        entry->status = status;
        entry->refreshTimer.start();
    }
    return found;
}

const DynamicDataEntry* DataHandler::find(const DynamicData& id) const
{
    // coverity[misra_cpp_2008_rule_5_2_5_violation] Avoids code duplication
    return const_cast<DataHandler*>(this)->find(id);
}

DynamicDataEntry* DataHandler::find(const DynamicData& id)
{
    DynamicDataEntry* const pDataEntry = std::lower_bound(
        &m_dataEntries[0],
        &m_dataEntries[m_numDataEntries],
        DynamicDataEntry_Comparer::key(id.getFUClassId(), id.getDataId()),
        DynamicDataEntry_Comparer());

    return (((pDataEntry != &m_dataEntries[m_numDataEntries]) && (pDataEntry->fu->GetFUClassId() == id.getFUClassId()) && (pDataEntry->data->GetDataId() == id.getDataId())) ? pDataEntry : NULL);
}

} // namespace lsr
