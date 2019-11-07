#ifndef LUXOFTSAFERENDERER_DATACONTEXT_H
#define LUXOFTSAFERENDERER_DATACONTEXT_H

/******************************************************************************
**
**   File:        DataContext.h
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

namespace lsr
{

/**
 * DataContext is a container (not in stl meaning), which stores some
 * useful variables and values which can be used in evaluation of @c Expressions.
 */
class DataContext
{
public:
    DataContext(IDataHandler& dataHandler);

    /**
     * @return pointer to @c IDataHandler.
     */
    IDataHandler& getDataHandler() const
    {
        return m_dataHandler;
    }

    /**
     * Method increases the nesting counter.
     * Can be used as defense from infinite recursion.
     */
    void increaseNesting();

    /**
     * Method decreases the nesting counter.
     * Can be used as defense from infinite recursion.
     */
    void decreaseNesting();

    /**
     * @return the current nesting counter value.
     */
    U32 getNestingCounter() const;


private:
    DataContext(const DataContext&);
    DataContext& operator=(const DataContext&);

    IDataHandler& m_dataHandler;
    U32 m_nestingCounter;
};

inline DataContext::DataContext(IDataHandler& dataHandler)
    : m_dataHandler(dataHandler)
    , m_nestingCounter(0U)
{}

inline void DataContext::increaseNesting()
{
    ++m_nestingCounter;
}

inline void DataContext::decreaseNesting()
{
    --m_nestingCounter;
}

inline U32 DataContext::getNestingCounter() const
{
    return m_nestingCounter;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_DATACONTEXT_H
