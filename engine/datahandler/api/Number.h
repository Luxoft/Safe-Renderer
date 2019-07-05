#ifndef LUXOFTSAFERENDERER_NUMBER_H
#define LUXOFTSAFERENDERER_NUMBER_H

/******************************************************************************
**
**   File:        Number.h
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

#include <LsrTypes.h>

#include <ddh_defs.h>

namespace lsr
{

/**
 * This class combines the value of some data and type of this data.
 */
class Number
{
public:
    /**
     * Constructs the object and initializes it with default values:
     * - value will be equal to 0;
     * - type will be equal to @c lsr::DATATYPE_UNKNOWN.
     */
    Number();

    /**
     * Constructs the object and initializes it with Boolean value:
     * - value will be equal to 1 if @c value is equal to @c true and to 0 otherwise;
     * - type will be equal to @c lsr::DATATYPE_BOOLEAN.
     */
    explicit Number(const bool value);

    /**
     * Constructs the object and initializes it with provided values.
     *
     * @param[in] val  value of the data
     * @param[in] type type of the data
     */
    Number(const U32 val, const DynamicDataTypeEnumeration type);

    /**
     * Constructs the object and initializes it with another @c Number object.
     *
     * @param[in] rhs object which should be cloned.
     */
    Number(const Number& rhs);

    Number& operator=(const Number& rhs);

    /**
     * Returns value in U32 representation.
     *
     * @return value.
     */
    U32 getU32() const;

    /**
     * Returns value in Boolean representation.
     *
     * @return @c false if value is equal to 0, @c true otherwise.
     */
    bool getBool() const;

    /**
     * Returns the type of value.
     *
     * @return the value type. See @c lsr::DynamicDataTypeEnumeration.
     */
    DynamicDataTypeEnumeration getType() const;

    ~Number();

private:
    friend bool operator<(const Number& lhs, const Number& rhs);
    friend bool operator==(const Number& lhs, const Number& rhs);

    U32 m_value;
    DynamicDataTypeEnumeration m_type;
};

inline Number::Number()
    : m_value(0U)
    , m_type(DATATYPE_ENUM_SIZE)
{}

inline Number::Number(const bool value)
    : m_value((value) ? 1U : 0U)
    , m_type(DATATYPE_BOOLEAN)
{}

inline Number::Number(const U32 val, const DynamicDataTypeEnumeration type)
    : m_value(val)
    , m_type(type)
{}

inline Number::Number(const Number& rhs)
    : m_value(rhs.m_value)
    , m_type(rhs.m_type)
{}

inline Number::~Number()
{}

inline Number& Number::operator=(const Number& rhs)
{
    if (this != &rhs)
    {
        m_value = rhs.m_value;
        m_type = rhs.m_type;
    }
    return *this;
}

inline U32 Number::getU32() const
{
    return m_value;
}

inline bool Number::getBool() const
{
    return m_value != 0U;
}

inline DynamicDataTypeEnumeration Number::getType() const
{
    return m_type;
}

inline bool operator<(const Number& lhs, const Number& rhs)
{
    return lhs.m_value < rhs.m_value;
}

inline bool operator==(const Number& lhs, const Number& rhs)
{
    return lhs.m_value == rhs.m_value && lhs.m_type == rhs.m_type;
}

inline bool operator!=(const Number& lhs, const Number& rhs)
{
    return !(lhs == rhs);
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_NUMBER_H
