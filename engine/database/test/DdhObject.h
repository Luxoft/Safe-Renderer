#ifndef LUXOFTSAFERENDERER_DDHOBJECT_H
#define LUXOFTSAFERENDERER_DDHOBJECT_H

/******************************************************************************
**
**   File:        DdhObject.h
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
#include <NonCopyable.h>

#include <algorithm>
#include <iterator>
#include <vector>

template <class T>
class DdhObject: private NonCopyable<DdhObject<T> >
{
public:
    /**
     * @return size of serialized data in bytes.
     */
    std::size_t getDataSize() const;

    /**
     * @return pointer to serialized data. For size of this data see @c getDataSize().
     */
    const U8* getData() const;

    virtual ~DdhObject()
    {}

protected:
    DdhObject();

    /**
     * @return reference to storing object
     */
    T& getObj();

    /**
     * Method adds data as a child into internal storage
     *
     * @param[in] data     pointer to data to be added. Must not be @c NULL.
     * @param[in] dataSize size of the @c data in bytes.
     *
     * @return the distance between the beginning of storing object and
     *         beginning of added data in bytes.
     */
    std::size_t addData(const U8* data, std::size_t dataSize);

    /**
     * Method adds a data with value @c value into internal storage.
     *
     * @param[in] size  size of the data which should be added.
     * @param[in] value value of each item which will be added to storage.
     *
     * @return the distance between the beginning of storing object and
     *         beginning of added data in bytes.
     */
    std::size_t addEmptyData(std::size_t size, U8 value = 0U);

    /**
     * Method sets value of type K by the offset @c offset.
     *
     * @tparam K type of the @c value. sizeof(K) bytes will be copied to internal storage
     *           with @c offset.
     *
     * @param offset offset in the storage, where @c value should be copied.
     * @param value the value which should be copied.
     */
    template <class K>
    void setValue(std::size_t offset, K value);

private:
    union Object
    {
        T obj;
        U8 array[sizeof(T)];
    };

    /**
     * Method modifies input @c value to be integer divided by 4.
     *
     * @param[in] value value to be modified.
     *
     * @return value which can be integer divided by 4. It can be more or equal
     *         to input @c value.
     */
    std::size_t doDividableTo4(const std::size_t value) const;

    Object m_obj;
    mutable std::vector<U8> m_data;
};

template <class T>
std::size_t DdhObject<T>::getDataSize() const
{
    return m_data.size();
}

template <class T>
const U8* DdhObject<T>::getData() const
{
    memcpy(&m_data[0], m_obj.array, sizeof(m_obj.array));
    return &m_data[0];
}

template <class T>
DdhObject<T>::DdhObject()
{
    // reserve place for T data.
    addEmptyData(sizeof(T));
}

template <class T>
T& DdhObject<T>::getObj()
{
    return m_obj.obj;
}

template <class T>
std::size_t DdhObject<T>::addData(const U8* data, std::size_t dataSize)
{
    std::size_t offset = getDataSize();

    std::size_t realSize = doDividableTo4(dataSize);
    m_data.reserve(m_data.size() + realSize);

    std::copy(&data[0], &data[dataSize], std::back_inserter(m_data));

    if (realSize > dataSize)
    {
        m_data.insert(m_data.end(), realSize - dataSize, 0U);
    }

    return offset;
}

template <class T>
std::size_t DdhObject<T>::addEmptyData(std::size_t size, U8 value)
{
    std::size_t offset = getDataSize();
    std::size_t realSize = doDividableTo4(size);
    m_data.insert(m_data.end(), realSize, value);
    return offset;
}

template <class T>
template <class K>
void DdhObject<T>::setValue(std::size_t offset, K value)
{
    memcpy(&m_data[offset], reinterpret_cast<U8*>(&value), sizeof(K));
}

template <class T>
std::size_t DdhObject<T>::doDividableTo4(std::size_t value) const
{
    if (value % 4U != 0U)
    {
        value = value / 4U + 1;
        value *= 4U;
    }

    return value;
}

#endif // LUXOFTSAFERENDERER_DDHOBJECT_H
