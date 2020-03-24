/******************************************************************************
**
**   File:        Frame.cpp
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

#include "Frame.h"

#include <Assertion.h>

#include <DDHType.h>
#include <PanelDatabaseType.h>
#include <Database.h>
#include <HMIGlobalSettingsType.h>
#include <DisplaySizeType.h>

#include <new>

namespace lsr
{

Frame::Frame()
    : Widget()
{
}

LSREngineError Frame::setup(const Database& db)
{
    const DDHType* const pDdh = db.getDdh();
    ASSERT(NULL != pDdh);
    const HMIGlobalSettingsType* const pSettings = pDdh->GetHMIGlobalSettings();
    ASSERT(pSettings != NULL);
    const DisplaySizeType* const pDisplaySize = pSettings->GetDisplaySize();
    ASSERT(pDisplaySize != NULL);
    Area rect;
    rect.setWidth(static_cast<I32>(pDisplaySize->GetWidth()));
    rect.setHeight(static_cast<I32>(pDisplaySize->GetHeight()));
    setArea(rect);

    return m_children.setup(db);
}

void Frame::addChild(Panel& childPanel)
{
    const bool added = m_children.addChild(&childPanel);
    if (!added)
    {
        setError(LSR_DB_INCONSISTENT);
    }
}

void Frame::onDraw(Canvas& dst, const Area& rect) const
{
    m_children.draw(dst, rect);
}

bool Frame::onVerify(Canvas& dst, const Area& rect)
{
    return m_children.verify(dst, rect);
}

LSREngineError Frame::getChildError() const
{
    return m_children.getError();
}

bool Frame::isChildInvalidated() const
{
    return m_children.isInvalidated();
}

} // namespace lsr
