#ifndef LUXOFTSAFERENDERER_ENGINE_H
#define LUXOFTSAFERENDERER_ENGINE_H

/******************************************************************************
**
**   File:        Engine.h
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

#include <ddh_defs.h>
#include "Database.h"
#include "FrameHandler.h"
#include "DisplayManager.h"


namespace lsr
{

class Engine
{
public:
    Engine(const DDHType* const ddh, IHMI& hmi);

    bool render();
    bool verify();

    bool handleWindowEvents();

    /**
     * Typed error class (to avoid accidential assignments)
     */
    class Error
    {
    public:
        explicit Error(const U32 errorCode)
            : m_errorCode(errorCode)
        {}

        bool isError() const
        {
            return (m_errorCode != 0U);
        }

        U32 getValue() const
        {
            return m_errorCode;
        }
    private:
        U32 m_errorCode;
    };

    Error getError();

private:
    Database m_db;
    DisplayManager m_display;
    FrameHandler m_frameHandler;
    LSREngineError m_error;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_ENGINE_H
