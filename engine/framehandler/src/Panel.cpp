/******************************************************************************
**
**   File:        Panel.cpp
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

#include "Panel.h"

#include <Assertion.h>

#include <DDHType.h>
#include <PanelType.h>

#include <new>

namespace lsr
{

Panel::Panel(const PanelType* const pDdh)
    : Widget()
    , m_pDdh(pDdh)
{
}

LSREngineError Panel::setup(const Database& db)
{
    const bool successful = setArea(m_pDdh->GetArea()) && setVisible(m_pDdh->GetVisible());

    LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    if (successful)
    {
        error = m_children.setup(db);
    }
    else
    {
        error = LSR_DB_INCONSISTENT;
    }

    return error.get();
}

void Panel::addChild(Field& childField)
{
    const bool successful = m_children.addChild(&childField);
    if (!successful)
    {
        setError(LSR_DB_INCONSISTENT);
    }
}

void Panel::onDraw(Canvas& dst, const Area& rect) const
{
    m_children.draw(dst, rect);
}

bool Panel::onVerify(Canvas& dst, const Area& rect)
{
    return m_children.verify(dst, rect);
}

LSREngineError Panel::getChildError() const
{
    return m_children.getError();
}

bool Panel::isChildInvalidated() const
{
    return m_children.isInvalidated();
}

} // namespace lsr
