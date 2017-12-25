#ifndef POPULUSSC_DDHARRAYOBJECT_H
#define POPULUSSC_DDHARRAYOBJECT_H

/******************************************************************************
**
**   File:        DdhArrayObject.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include "DdhObject.h"

/**
 * Class performs operation for creating ddh objects with array of children.
 * In cells of array will be stored offsets to each child.
 *
 * @tparam T type of the ddh object.
 * @tparam K type of cell in the array.
 */
template <class T, class K = U16>
class DdhArrayObject: public DdhObject<T>
{
protected:
    DdhArrayObject();

    /**
     * Method adds data an array with size @c arraySize and cell size @c sizeof(K).
     *
     * @param[in] arraySize size of the array need to be created.
     *
     * @return the distance between the beginning of storing object and
     *         beginning of recently added array in bytes.
     */
    std::size_t addArray(std::size_t arraySize);

    /**
     * Method adds data into the storage and store the offset between this data and
     * the beginning of the storage in to the active cell of the array, see @c addArray method.
     *
     * @param[in]  data     pointer to data to be added. Must not be @c NULL.
     * @param[in]  dataSize size of the @c data in bytes.
     */
    void addDataToArray(const U8* data, std::size_t dataSize);

    /**
     * Method sets value to active array cell, pointer to active cell updates to next cell.
     *
     * @param value needs to be set.
     */
    void addValueToArray(K value);

private:
    std::size_t m_curIndex;
    std::size_t m_arrayOffset;
    const std::size_t m_cellSize;
};

template <class T, class K>
DdhArrayObject<T, K>::DdhArrayObject()
    : DdhObject<T>()
    , m_cellSize(sizeof(K))
{
    m_curIndex = 0U;
    m_arrayOffset = 0U;
}

template <class T, class K>
std::size_t DdhArrayObject<T, K>::addArray(std::size_t arraySize)
{
    m_arrayOffset = this->addEmptyData(m_cellSize * arraySize);

    return m_arrayOffset;
}

template <class T, class K>
void DdhArrayObject<T, K>::addDataToArray(const U8* data, std::size_t dataSize)
{
    std::size_t offset = this->addData(data, dataSize);

    this->addValueToArray(offset / 4U);
}

template <class T, class K>
void DdhArrayObject<T, K>::addValueToArray(K value)
{
    const std::size_t cellOffset = m_arrayOffset + m_curIndex * m_cellSize;

    this->setValue(cellOffset, value);

    ++m_curIndex;
}

#endif // POPULUSSC_DDHARRAYOBJECT_H
