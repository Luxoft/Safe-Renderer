#ifndef LUXOFTSAFERENDERER_IDATAHANDLER_H
#define LUXOFTSAFERENDERER_IDATAHANDLER_H

/******************************************************************************
**
**   File:        IDataHandler.h
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

#include "Number.h"
#include "DataStatus.h"

#include <LsrTypes.h>
#include <DynamicDataType.h>

namespace lsr
{
    /**
    * Helper class to store dynamic data identifiers (FU + DataId)
    */
    class DynamicData
    {
    public:
        explicit DynamicData(U32 fudataid) : m_fu(static_cast<FUClassId>(fudataid >> 16U)), m_data(static_cast<DataId>(fudataid)) {}
        DynamicData() : m_fu(0U), m_data(0U) {}
        DynamicData(FUClassId fuId, DataId dataId) : m_fu(fuId), m_data(dataId) {}
        DynamicData(const DynamicDataType* pDataId) : m_fu(static_cast<FUClassId>(pDataId->GetFUDataId() >> 16U)), m_data(static_cast<DataId>(pDataId->GetFUDataId())) {}
        DataId getDataId() const { return m_data; }
        FUClassId getFUClassId() const { return m_fu; }

        U32 getCombined() const
        {
            const U32 msb = m_fu;
            const U32 lsb = m_data;
            return static_cast<U32>(msb << 16U) | lsb;
        }

        bool operator==(const DynamicData& rhs) const { return (m_fu == rhs.m_fu) && (m_data == rhs.m_data); }
        bool operator!=(const DynamicData& rhs) const { return !operator==(rhs); }
        bool operator<(const DynamicData& rhs) const { return getCombined() < rhs.getCombined(); }
    private:
        FUClassId m_fu;
        DataId m_data;
    };

class IDataHandler
{
public:
    /**
     * Returns the data, identified by @c fuClassId and @c dataId.
     * Value is calculated in accordance with the data type.
     *
     * @param[in]  dataId    the identifier of the data
     * @param[out] value     the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    virtual DataStatus getNumber(const DynamicData& dataId, Number &value) const = 0;

    /**
     * Sets a data entry in the data handler
     * @param[in]  dataId    the identifier of the data
     * @param[in]  value     the value which shall be set
     * @param[in]  status    the status which shall be applied to the data
     * @return true if the data was set, false on error
     */
    virtual bool setData(const DynamicData& dataId, const Number& value, const DataStatus status) = 0;

    virtual ~IDataHandler() {}
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_IDATAHANDLER_H
