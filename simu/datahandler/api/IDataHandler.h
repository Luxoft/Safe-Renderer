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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "Number.h"
#include "DataStatus.h"

#include <LsrTypes.h>
#include <NonCopyable.h>

namespace lsr
{

/**
 * Helper class to store dynamic data identifiers (FUClassId + DataId)
 */
class DynamicData
{
public:
    explicit DynamicData(const U32 fudataid) : m_fu(static_cast<FUClassId>(fudataid >> 16U)), m_data(static_cast<DataId>(fudataid)) {}
    DynamicData() : m_fu(0U), m_data(0U) {}
    DynamicData(const FUClassId idFu, const DataId idData) : m_fu(idFu), m_data(idData) {}
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

// coverity[misra_cpp_2008_rule_12_8_2_violation] Base class NonCopyable hides copy assignment operator
class IDataHandler : private NonCopyable
{
public:
    /**
     * Returns the data, identified by @c fuClassId and @c dataId.
     * Value is calculated in accordance with the data type.
     *
     * @param[in]  id        the identifier of the data
     * @param[out] value     the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    virtual DataStatus getNumber(const DynamicData& id, Number &value) const = 0;

    /**
     * Sets a data entry in the data handler
     * @param[in]  id        the identifier of the data
     * @param[in]  value     the value which shall be set
     * @param[in]  status    the status which shall be applied to the data
     * @return true if the data was set, false on error
     */
    virtual bool setData(const DynamicData& id, const Number& value, const DataStatus status) = 0;

protected:
    IDataHandler()
    : NonCopyable()
    {
    }

    virtual ~IDataHandler() {}
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_IDATAHANDLER_H
