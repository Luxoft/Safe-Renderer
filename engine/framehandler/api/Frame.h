#ifndef LUXOFTSAFERENDERER_FRAME_H
#define LUXOFTSAFERENDERER_FRAME_H

/******************************************************************************
**
**   File:        Frame.h
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

#include "Widget.h"
#include "WidgetChildren.h"
#include <Panel.h>

#include <ddh_defs.h>

namespace lsr
{

/**
 * Frame implements the widget which is parent for @c Panel widgets.
 *
 * @reqid SW_ENG_076
 */
class Frame P_FINAL : public Widget
{
public:
    /**
     * Creates a frame object.
     */
    Frame();

    /**
     * Connects the Frame and its children with the Database component
     * @param[in] db database provides access to the bitmap resources
     * @return error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                      operation succeeded, other @c LSREngineError values otherwise.
     */
    LSREngineError setup(const Database& db);

    /**
     * Adds a child panel to the frame
     * Sets the internal error state to LSR_DB_INCONSISTENT if no child could be added
     * @param childPanel panel to add as a child
     */
    void addChild(Panel& childPanel);

private:
    /**
     * Method does nothing. It is a stub method
     */
    virtual void onDraw(Canvas& dst, const Area& rect) const P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     *
     * @return @c true.
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) P_OVERRIDE;

    virtual LSREngineError getChildError() const P_OVERRIDE;

    virtual bool isChildInvalidated() const P_OVERRIDE;

    WidgetChildren<Panel, MAX_PANELS_COUNT> m_children;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_FRAME_H
