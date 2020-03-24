/******************************************************************************
**
**   File:        DataHandler.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "Assertion.h"
#include "DataHandler.h"
#include "Database.h"
#include "DDHType.h"
#include "LsrTypes.h"

#include <algorithm>

namespace lsr
{

struct DynamicDataEntry_Comparer
{
    bool operator()(const DataHandler::DynamicDataEntry& entry, const U32 value) const
    {
        return (entry.config.fuDataId < value);
    }
};

DataHandler::DataHandler(const DataEntryType entries[], const U32 size)
: IDataHandler()
, m_numDataEntries(0U)
, m_error(LSR_NO_ENGINE_ERROR)
{
    if (NULL != entries)
    {
        for (U32 i = 0U; i < size; ++i)
        {
            if (m_numDataEntries < MAX_DYNAMIC_DATA)
            {
                m_dataEntries[m_numDataEntries].config = entries[i];
                m_dataEntries[m_numDataEntries].value = 0U;
                m_dataEntries[m_numDataEntries].refreshTimer = Timer();
                m_dataEntries[m_numDataEntries].status = DataStatus::NOT_AVAILABLE;
                ++m_numDataEntries;
            }
            else
            {
                m_error = LSR_DB_ERROR;
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
        value = Number(entry->value, entry->config.type);
        const U32 repeatTimeout = static_cast<U32>(entry->config.timeout);
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
    const bool found = ((NULL != entry) && (entry->config.type == value.getType()));
    if (found)
    {
        entry->value = value.getU32();
        entry->status = status;
        entry->refreshTimer.start();
    }
    return found;
}

const DataHandler::DynamicDataEntry* DataHandler::find(const DynamicData& id) const
{
    // coverity[misra_cpp_2008_rule_5_2_5_violation] Avoids code duplication
    return const_cast<DataHandler*>(this)->find(id);
}

DataHandler::DynamicDataEntry* DataHandler::find(const DynamicData& id)
{
    DynamicDataEntry* const pDataEntry = std::lower_bound(
        &m_dataEntries[0],
        &m_dataEntries[m_numDataEntries],
        id.getCombined(),
        DynamicDataEntry_Comparer());

    return ((pDataEntry != &m_dataEntries[m_numDataEntries]) && (pDataEntry->config.fuDataId == id.getCombined())) ? pDataEntry : NULL;
}

} // namespace lsr
