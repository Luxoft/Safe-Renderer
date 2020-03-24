/******************************************************************************
**
**   File:        FrameHandler.cpp
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

#include "FrameHandler.h"

#include <DDHType.h>
#include <Database.h>
#include <HMIGlobalSettingsType.h>

#include <WindowDefinition.h>
#include <DisplaySizeType.h>
#include "Assertion.h"

namespace lsr
{

FrameHandler::FrameHandler(IHMI& hmi, Database& db, DisplayManager& dsp)
    : NonCopyable()
    , m_db(db)
    , m_display(dsp)
    , m_error(LSR_NO_ENGINE_ERROR)
    , m_window(dsp, WindowDefinition(m_db.getDdh(), 0U))
    , m_hmi(hmi)
{
    // since we don't use exceptions we need an extra initialize method to capture errors (start())
}

bool FrameHandler::start()
{
    ASSERT(m_db.getError() == LSR_NO_ENGINE_ERROR);

    m_error = m_window.setup(m_hmi, m_db);
    return (LSR_NO_ENGINE_ERROR == m_error.get());
}

bool FrameHandler::render()
{
    return m_window.render();
}

bool FrameHandler::verify()
{
    return m_window.verify();
}

bool FrameHandler::handleWindowEvents()
{
    return m_window.handleWindowEvents();
}

LSREngineError FrameHandler::getError()
{
    m_error = m_window.getError();
    return m_error.get();
}

}
