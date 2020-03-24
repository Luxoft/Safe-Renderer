#ifndef LUXOFTSAFERENDERER_OUTPUTSTREAM_H
#define LUXOFTSAFERENDERER_OUTPUTSTREAM_H

/******************************************************************************
**
**   File:        OutputStream.h
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

#include <stdint.h>  // <cstdint> cannot be used (C++11)

#include "ComError.h"

namespace lsr
{

/**
 * This class is needed to encapsulate writing data to the buffer.
 * Internal state of the class can be read by method @c getError, which returns
 * @c LSREngineError flag. Each method can set this flag and user can analyze it.
 * If error flag is raised up, it can't be overwritten by success value of this flag.
 * if error flag is raised up, no operations will be evaluated.
 */
class OutputStream
{
public:
    /**
     * Construct the object.
     * It checks the values of @c pBuffer and @c bufferSize.
     * If at least one of them is invalid, the flag @c COM_NOT_ENOUGH_BUFFER_SIZE
     * will be set.
     * Class doesn't take the ownership of the buffer.
     * It only encapsulates access to this buffer and helps with putting data to it.
     *
     * @param[in] pBuffer    pointer to the buffer where data should be placed.
     * @param[in] bufferSize size of the buffer @c pBuffer.
     */
    OutputStream(void* const pBuffer, const uint32_t bufferSize);

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
     * Method provides information how many bytes were written to the buffer.
     *
     * @return how many bytes were written to the buffer.
     */
    uint32_t bytesWritten() const;

    /**
     * Method provides information about the amount of free space in the buffer.
     *
     * @return the amount of free space in the buffer.
     */
    uint32_t bytesAvailable() const;

    /**
     * Method copy data from @c pData with size @c dataSize to buffer.
     * Data is written starting with the first free byte in the buffer.
     *
     * @param[in] pData    pointer to the data which should be copied.
     * @param[in] dataSize size of data which should be copied.
     *
     * @return count of copied data in bytes.
     */
    uint32_t write(const void* const pData, const uint32_t dataSize);

    /**
     * Method allowing to get pointer to the buffer, where all information is copied.
     *
     * @return pointer to the buffer.
     */
    const void* getBuffer() const;

    /**
     * These methods copy data from typed variable to buffer.
     *
     * Each method shifts the empty space start pointer by the amount of data
     * that have been processed in this method.
     */
    OutputStream& operator<<(const bool&);
    OutputStream& operator<<(const int8_t&);
    OutputStream& operator<<(const uint8_t&);
    OutputStream& operator<<(const int16_t&);
    OutputStream& operator<<(const uint16_t&);
    OutputStream& operator<<(const int32_t&);
    OutputStream& operator<<(const uint32_t&);

private:
    uint8_t* m_pBuffer;
    uint32_t m_bufferSize;
    uint32_t m_pos;
    ComError m_error;
};

inline ComError OutputStream::getError() const
{
    return m_error;
}

inline void OutputStream::setError(const ComError error)
{
    if (m_error == COM_NO_ERROR)
    {
        m_error = error;
    }
}

inline const void* OutputStream::getBuffer() const
{
    return m_pBuffer;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_OUTPUTSTREAM_H
