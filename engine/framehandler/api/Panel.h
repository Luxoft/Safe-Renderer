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

#include "Widget.h"

#include <ddh_defs.h>

#include <BoolExpression.h>

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
     * Method creates a @c Panel object and all its children  with given @c WidgetPool according
     * to configuration @c pDdhPanel.
     *
     * @param[in]  factory    pool which provides allocation an @c Panel object.
     * @param[in]  db         object provides work with database.
     * @param[in]  pDdhPanel  @c PanelType ddh configuration.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                        operation succeeded, other @c LSREngineError values otherwise.
     *
     * @return pointer to @c Panel object if initialization of object was successful,
     *         @c NULL otherwise.
     */
    static Panel* create(WidgetPool& factory,
                         const Database& db,
                         const PanelType* const pDdhPanel,
                         DataContext* const pContext,
                         LSRErrorCollector& error);

private:
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
    bool setup(WidgetPool& factory,
               const Database& db,
               DataContext* const pContext,
               LSRErrorCollector& error);

    /**
     * Method does nothing. It is a stub method
     */
    virtual void onUpdate(const U32 monotonicTimeMs) P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     */
    virtual void onDraw(Canvas& dst, const Area& rect) const P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) P_OVERRIDE;

    /**
     * Method returns type of the widget.
     *
     * @return @c WIDGET_TYPE_PANEL value.
     */
    virtual WidgetType getType() const P_OVERRIDE;

    bool setupVisibilityExpr(DataContext* const pContext);

    const PanelType* m_pDdh;
    BoolExpression m_visibilityExpr;
};

inline Panel::WidgetType Panel::getType() const
{
    return WIDGET_TYPE_PANEL;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_PANEL_H
