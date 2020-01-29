#ifndef LUXOFTSAFERENDERER_INPUTSTREAM_H
#define LUXOFTSAFERENDERER_INPUTSTREAM_H

/******************************************************************************
**
**   File:        InputStream.h
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

#include <stdint.h>  // <cstdint> cannot be used (C++11)

#include "ComError.h"

namespace lsr
{

/**
 * This class is needed to encapsulate reading data from the buffer.
 * Internal state of the class can be read by method @c getError, which returns
 * @c LSREngineError flag. Each method can set this flag and user can analyze it.
 * If error flag is raised up, it can't be overwritten by success value of this flag.
 * If error flag is raised up, no future operations will be evaluated.
 */
class InputStream
{
public:
    /**
     * Construct the object.
     * It checks the values of @c pBuffer and @c bufferSize.
     * If at least one of them is invalid, the flag @c COM_NOT_ENOUGH_BUFFER_SIZE
     * will be set.
     * Class doesn't take the ownership of the buffer.
     * It only encapsulates access to this buffer and helps with reading data from it.
     *
     * @param[in] pBuffer    pointer to the buffer with data which should be read.
     * @param[in] bufferSize size of the buffer @c pBuffer. If the buffer size is larger than
     *                       the amount of the information contained within, then the information size
     *                       should be mentioned here.
     */
    InputStream(const void* const pBuffer, const uint32_t bufferSize);

    /**
     * With this method we can understand if the last executed operation was successful or not.
     * If there was an error in the sequence of operations, the error from first operation
     * will be returned.
     *
     * @return value of error flag. See @c LSREngineError.
     */
    ComError getError() const;

    /**
     * With this method user can set error inside the stream.
     * It can be used when an error is encountered while parsing some data from @c InputStream
     * and user wants to store this error inside the stream.
     *
     * If error has been set already by someone, new value of the error (even success value) won't
     * be set.
     *
     * @param[in] error value of the error which should be set.
     */
    void setError(const ComError error);

    /**
     * Method provides information about how much unread data in bytes still remains in the buffer.
     *
     * @return amount of not read data.
     */
    uint32_t bytesToRead() const;

    /**
     * Method copies data with size @c dataSize from buffer to @c pData.
     * Data is copied starting with the last unread data.
     *
     * @param[out] pData    pointer to buffer where data from the internal buffer should be copied.
     * @param[out] dataSize size of data which should be copied.
     *
     * @return count of copied data in bytes.
     */
    uint32_t read(void* const pData, const uint32_t dataSize);

    /**
     * These methods copy data from buffer to some typed variable.
     *
     * Each method shifts the unread data start pointer by the amount of data
     * that have been processed in this method.
     */
    InputStream& operator>>(bool& value);
    InputStream& operator>>(int8_t& value);
    InputStream& operator>>(uint8_t& value);
    InputStream& operator>>(int16_t& value);
    InputStream& operator>>(uint16_t& value);
    InputStream& operator>>(int32_t& value);
    InputStream& operator>>(uint32_t& value);

private:
    const uint8_t* m_pBuffer;
    uint32_t m_bufferSize;
    uint32_t m_pos;
    ComError m_error;
};

inline ComError InputStream::getError() const
{
    return m_error;
}

inline void InputStream::setError(const ComError error)
{
    if (m_error == COM_NO_ERROR)
    {
        m_error = error;
    }
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_INPUTSTREAM_H
