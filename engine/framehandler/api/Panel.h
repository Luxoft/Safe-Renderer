#ifndef LUXOFTSAFERENDERER_PANEL_H
#define LUXOFTSAFERENDERER_PANEL_H

/******************************************************************************
**
**   File:        Panel.h
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
#include <Field.h>

#include <ddh_defs.h>

namespace lsr
{

/**
 * Panel implements the widget which is parent for @c BitmapFiled widgets.
 *
 * @reqid SW_ENG_076
 */
class Panel P_FINAL : public Widget
{
public:
    /**
     * Create an object.
     *
     * @param[in] pDdh @c lsr::PanelType ddh configuration.
     */
    explicit Panel(const PanelType* const pDdh);

    /**
     * Method initialize object.
     *
     * @param[in]  factory    pool which provides allocation an @c Frame object.
     * @param[in]  db         object provides work with database.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                        operation succeeded, other @c LSREngineError values otherwise.
     *
     * @return @c true if object initialization succeeded, @c false otherwise.
     */
    LSREngineError setup(const Database& db);

    /**
     * Adds a child field to the panel.
     * Sets the internal error state to LSR_DB_INCONSISTENT if no child could be added
     * @param childField child field to add
     */
    void addChild(Field& childField);

private:
    /**
     * Method does nothing. It is a stub method
     */
    virtual void onDraw(Canvas& dst, const Area& rect) const P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) P_OVERRIDE;

    virtual LSREngineError getChildError() const P_OVERRIDE;

    virtual bool isChildInvalidated() const P_OVERRIDE;

    const PanelType* m_pDdh;
    WidgetChildren<Field, MAX_WIDGET_CHILDREN_COUNT> m_children;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_PANEL_H
