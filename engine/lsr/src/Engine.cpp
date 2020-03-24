/******************************************************************************
**
**   File:        Engine.cpp
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

#include "Engine.h"
#include <pil.h>

namespace lsr
{

Engine::Engine(const DDHType* const ddh, IHMI& hmi)
: m_db(ddh)
, m_display()
, m_frameHandler(hmi, m_db, m_display)
, m_error(m_db.getError())
{
    if (LSR_NO_ENGINE_ERROR == m_error)
    {
        if (!m_display.loadAllTextures(m_db))
        {
            m_error = LSR_DB_INCONSISTENT;
        }
        else if (!m_frameHandler.start())
        {
            m_error = m_frameHandler.getError();
        }
        else
        {
            // no startup error
        }
    }
}

bool Engine::render()
{
    return m_frameHandler.render();
}

bool Engine::verify()
{
    return m_frameHandler.verify();
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
