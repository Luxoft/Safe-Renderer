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

#include "IDataHandler.h"
#include <LSRLimits.h>
#include "Timer.h"

namespace lsr
{

struct DynamicDataEntry
{
    const FUClassType* fu; ///< FU DB information
    const DynamicDataEntryType* data; ///< Dynamic Data DB information
    U32 value; ///< Raw data value
    Timer refreshTimer; ///< Timestamp of last data update
    DataStatus status; ///< Validity information
};

struct DynamicDataEntry_Comparer
{
    static U32 key(const FUClassId idFu, const DataId idData);
    bool operator()(struct DynamicDataEntry const& entry, U32 const value) const;
};

inline U32 DynamicDataEntry_Comparer::key(const FUClassId idFu, const DataId idData)
{
    const U32 msb = idFu;
    const U32 lsb = idData;
    return (msb << 16U) | lsb;
}

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
    explicit DataHandler(const Database& db);

    virtual DataStatus getNumber(const DynamicData& id,
        Number &value) const P_OVERRIDE;

    virtual bool setData(const DynamicData& id,
        const Number& value,
        const DataStatus status) P_OVERRIDE;

private:
    DynamicDataEntry* find(const DynamicData& id);
    const DynamicDataEntry* find(const DynamicData& id) const;

    DynamicDataEntry m_dataEntries[MAX_DYNAMIC_DATA];
    size_t m_numDataEntries;

    LSREngineError m_error;
};

} // namespace datahandler

#endif // LUXOFTSAFERENDERER_DATAHANDLER_H
