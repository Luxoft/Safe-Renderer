/******************************************************************************
**
**   File:        Engine.cpp
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

#include "Engine.h"
#include <pil.h>

namespace lsr
{

Engine::Engine(const DDHType* const ddh)
: m_db(ddh)
, m_display()
, m_dataHandler(m_db)
, m_frameHandler(m_db, m_dataHandler, m_display)
, m_error(m_db.getError())
{
    if (LSR_NO_ENGINE_ERROR == m_error)
    {
        if (!m_frameHandler.start())
        {
            m_error = m_frameHandler.getError();
        }
    }
}

bool Engine::render()
{
    const U32 monotonicTime = pilGetMonotonicTime();
    m_frameHandler.update(monotonicTime);
    return m_frameHandler.render();
}

bool Engine::verify()
{
    return m_frameHandler.verify();
}

bool Engine::setData(const DynamicData& id,
                     const Number& value,
                     const DataStatus status)
{
    return m_dataHandler.setData(id, value, status);
}

DataStatus Engine::getData(const DynamicData& id, Number &value) const
{
    return m_dataHandler.getNumber(id, value);
}

bool Engine::handleWindowEvents()
{
    return m_frameHandler.handleWindowEvents();
}

Engine::Error Engine::getError()
{
    Error err = Error(m_error);
    if (!err.isError())
    {
        // database errors are permanent
        err = Error(m_db.getError());
        if (!err.isError())
        {
            err = Error(m_frameHandler.getError());
            if (!err.isError())
            {
                err = Error(m_display.getError());
            }
        }
    }
    else
    {
        m_error = LSR_NO_ENGINE_ERROR;
    }
    return err;
}

} // namespace lsr
