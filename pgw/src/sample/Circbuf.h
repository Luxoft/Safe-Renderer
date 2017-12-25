#ifndef POPULUSSC_CIRCBUF_H
#define POPULUSSC_CIRCBUF_H

/******************************************************************************
**
**   File:        Circbuf.h
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

#include <cstddef>
#include <string.h>

#define CIRCBUF_MIN(A,B) ((A)<(B)?(A):(B))
#define CIRCBUF_MAX(A,B) ((A)>(B)?(A):(B))

template <class T, size_t capacity>
class Circbuf
{
public:
    Circbuf()
    {
        wi = 0;
        ri = 0;
        ee = capacity;
        size = 0;
        maxFill = 0;
        largestWriteRelease = 0u;
        transactionsCommited = 0;
    }

    size_t Size()
    {
        return size;
    }

    /**
    * Reserve memory for reader. Reserve only in ONE full block.
    * Note that m_size may be larger than the largest full block.
    */
    T *ReaderReserve(size_t &count)
    {
        T *pData = (T*)NULL;
        size_t wantedSize = count;

        count = 0;

        if (ri == ee && Size() > 0)
        {
            //if (ri == wi)
            //   wi = 0;
            ri = 0;
            ee = capacity;
        }

        if (Size() > 0)
        {
            pData = (T*)&buffer[ri];
            if (ri < wi)
            {
                count = CIRCBUF_MIN(static_cast<size_t>(wi - ri), wantedSize);
            }
            else // We know that if(ri >= wi)
            {
                count = CIRCBUF_MIN(static_cast<size_t>(ee - ri), wantedSize);
            }
        }
        return pData;
    }

    void ReaderRelease(size_t count)
    {
        Flush(count);
    }

    T *WriterReserve(size_t &count)
    {
        size_t areaEnd;
        size_t areaBegin;
        T *pData = (T*)NULL;

        if (count == 0)
        {
            return (T*)NULL;
        }

        if (wi == ee && ri == wi && size > 0)
        {
            // Buffer is full, but it is possible to move ri to 0 and
            // let wi continue without ee
            ee = capacity;
            ri = 0;
            //count = 0;
            //return (T*)NULL;
        }

        GetWriteAreas(areaEnd, areaBegin);

        if (areaEnd == 0 && areaBegin == 0)
        {
            count = 0;
            return (T*)NULL;
        }

        if (count <= areaEnd)
        {
            pData = (T*)&buffer[wi];
        }
        else if (count <= areaBegin)
        {
            pData = buffer;
            setEarlyEnd();
        } /* Use the largest of the 2 buffers */
        else if (areaEnd >= areaBegin)
        {
            pData = (T*)&buffer[wi];
            count = areaEnd;
        }
        else
        {
            pData = buffer;
            count = areaBegin;
            setEarlyEnd();
        }
        return pData;
    }

    void WriterRelease(size_t count)
    {
        if (wi == capacity)
        {
            wi = 0;
        }
        wi += count;
        size += count;
        if (largestWriteRelease < count)
        {
            largestWriteRelease = count;
        }
        if (size > maxFill)
        {
            maxFill = size;
        }
        ++transactionsCommited;
    }

    inline void Flush()
    {
        wi = 0;
        ri = 0;
        ee = capacity;
        size = 0;
    }

    inline void Flush(size_t count)
    {
        //if(count>=Size())
        //{
        //   Flush();
        //}
        //else
        if (count > Size())
        {
            count = Size();
        }

        ri += count;
        size -= count;
        if (ri > ee)
        {
            ri = ri - ee;
            ee = capacity;
        }
    }

    size_t GetLargestConsecutiveWriteSize()
    {
        if (wi > ri)
        {
            return CIRCBUF_MAX(ee - wi, ri);
        }
        else if (ri > wi)
        {
            return ri - wi;
        }
        else
        {
            if (size == 0)
            {
                return ee - wi;
            }
            else
            {
                return 0;
            }
        }
    }


private:
    T buffer[capacity];

    int wi;
    int ri;
    int ee;
    int size;
    int maxFill;
    size_t largestWriteRelease;
    int transactionsCommited;

    void setEarlyEnd()
    {
        ee = wi;
        //if (ri == wi)
        //   ri = 0;
        wi = 0;
    }

    void GetWriteAreas(size_t &areaEnd, size_t &areaBegin)
    {
        if (Size() == 0)
        {
            areaEnd = ee - wi;
            areaBegin = ri;
        }
        else if (ri >= wi)
        {
            areaBegin = 0;
            areaEnd = ri - wi;
        }
        else
        {
            areaBegin = ri;
            areaEnd = capacity - wi;
        }
    }

};

#endif // POPULUSSC_CIRCBUF_H
