#ifndef LUXOFTSAFERENDERER_WINDOWDEFINITION_H
#define LUXOFTSAFERENDERER_WINDOWDEFINITION_H

/******************************************************************************
**
**   File:        WindowDefinition.h
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

#include "LsrTypes.h"
#include "DDHType.h"
#include "HMIGlobalSettingsType.h"
#include "DisplaySizeType.h"
#include "Assertion.h"

namespace lsr
{

/**
 * Provides configuration values for the gil Window
 */
struct WindowDefinition
{
public:
    /**
     * Creates a window configuration
     * @param pDdh HMI configuration root
     * @param windowId identifies the window in the GIL
     */
    WindowDefinition(const DDHType* const pDdh, const U8 windowId)
    : m_x(0)
    , m_y(0)
    , m_width(0)
    , m_height(0)
    , m_id(windowId)
    {
        if (pDdh != NULL)
        {
            const HMIGlobalSettingsType* const pSettings = pDdh->GetHMIGlobalSettings();
            ASSERT(pSettings != NULL);
            const DisplaySizeType* const pDisplaySize = pSettings->GetDisplaySize();
            ASSERT(pDisplaySize != NULL);
            m_width = static_cast<I32>(pDisplaySize->GetWidth());
            m_height = static_cast<I32>(pDisplaySize->GetHeight());
        }
    }

    // coverity[misra_cpp_2008_rule_0_1_10_violation] used by unit tests
    void setSize(const I32 width, const I32 height)
    {
        m_width = width;
        m_height = height;
    }

    I32 getX() const
    {
        return m_x;
    }

    I32 getY() const
    {
        return m_y;
    }

    I32 getWidth() const
    {
        return m_width;
    }

    I32 getHeight() const
    {
        return m_height;
    }

    U8 getWindowId() const
    {
        return m_id;
    }

private:
    I32 m_x;     ///< window x position in pixels
    I32 m_y;     ///< window y position in pixels
    I32 m_width;    ///< window width in pixels
    I32 m_height;   ///< window heigh in pixels
    U8 m_id;        ///< window id (gil implementation specific)
};

}

#endif // LUXOFTSAFERENDERER_WINDOWDEFINITION_H
