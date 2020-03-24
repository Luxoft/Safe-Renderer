#ifndef LUXOFTSAFERENDERER_DATAHANDLER_H
#define LUXOFTSAFERENDERER_DATAHANDLER_H

/******************************************************************************
**
**   File:        DataHandler.h
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

#include "IDataHandler.h"
#include <LSRLimits.h>
#include "Timer.h"

namespace lsr
{

/**
 * Datahandler implements functionality to handle incoming data and store its content.
 *
 * @reqid SW_ENG_083
 * @reqid SW_ENG_084
 * @reqid SW_ENG_085
 * @reqid SW_ENG_088
 * @reqid SW_ENG_089
 * @reqid SW_ENG_093
 * @reqid SW_ENG_101
 * @reqid SW_ENG_112
 */
class DataHandler : public IDataHandler
{
public:
    struct DataEntryType
    {
        U32 fuDataId;
        DynamicDataTypeEnumeration type;
        U32 timeout;
    };

    struct DynamicDataEntry
    {
        DataEntryType config;
        U32 value; ///< Raw data value
        Timer refreshTimer; ///< Timestamp of last data update
        DataStatus status; ///< Validity information
    };

    typedef const DynamicDataEntry* iterator;

    /**
     * @param dataEntries a list of dataIds that shall be stored by this data handler
     * must be sorted by fuDataId in ascending order
     * @param size number of elements in dataEntries array
     */
    DataHandler(const DataEntryType dataEntries[], const U32 size);

    virtual DataStatus getNumber(const DynamicData& id,
        Number &value) const P_OVERRIDE;

    virtual bool setData(const DynamicData& id,
        const Number& value,
        const DataStatus status) P_OVERRIDE;

    iterator begin()
    {
        return &m_dataEntries[0];
    }

    iterator end()
    {
        return &m_dataEntries[m_numDataEntries];
    }

private:
    DynamicDataEntry* find(const DynamicData& id);
    const DynamicDataEntry* find(const DynamicData& id) const;

    DynamicDataEntry m_dataEntries[MAX_DYNAMIC_DATA];
    size_t m_numDataEntries;

    LSREngineError m_error;
};

} // namespace datahandler

#endif // LUXOFTSAFERENDERER_DATAHANDLER_H
