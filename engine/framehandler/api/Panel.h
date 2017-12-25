#ifndef POPULUSSC_PANEL_H
#define POPULUSSC_PANEL_H

/******************************************************************************
**
**   File:        Panel.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

namespace psc
{
struct PanelType;
class Area;

class Database;
class DataContext;
class WidgetPool;

/**
 * Panel implements the widget which is parent for @c BitmapFiled widgets.
 *
 * @reqid SW_ENG_076
 */
class Panel P_FINAL : public Widget
{
public:
    /**
     * Method creates a @c Panel object and all its children  with given @c widgetPool according
     * to configuration @c pDdhPanel.
     *
     * @param[in]  widgetPool pool which provides allocation an @c Panel object.
     * @param[in]  db         object provides work with database.
     * @param[in]  pDdhPanel  @c PanelType ddh configuration.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c PSC_NO_ERROR if
     *                        operation succeeded, other @c PSCError values otherwise.
     *
     * @return pointer to @c Panel object if initialization of object was successful,
     *         @c NULL otherwise.
     */
    static Panel* create(WidgetPool& widgetPool,
                         const Database& db,
                         const PanelType* pDdhPanel,
                         DataContext* pContext,
                         PSCErrorCollector& error);

private:
    /**
     * Create an object.
     *
     * @param[in] pDdh @c psc::PanelType ddh configuration.
     */
    Panel(const PanelType* pDdh);

    /**
     * Method initialize object.
     *
     * @param[in]  widgetPool pool which provides allocation an @c Frame object.
     * @param[in]  db         object provides work with database.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c PSC_NO_ERROR if
     *                        operation succeeded, other @c PSCError values otherwise.
     *
     * @return @c true if object initialization succeeded, @c false otherwise.
     */
    bool setup(WidgetPool& widgetPool,
               const Database& db,
               DataContext* pContext,
               PSCErrorCollector& error);

    /**
     * Method does nothing. It is a stub method
     */
    virtual void onUpdate(const U32 monotonicTimeMs) P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     */
    virtual void onDraw(Canvas& canvas, const Area& area) P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     */
    virtual bool onVerify(Canvas& canvas, const Area& area) P_OVERRIDE;

    /**
     * Method returns type of the widget.
     *
     * @return @c WIDGET_TYPE_PANEL value.
     */
    virtual WidgetType getType() const P_OVERRIDE;

    bool setupVisibilityExpr(DataContext* pContext);

    const PanelType* m_pDdh;
    BoolExpression m_visibilityExpr;
};

inline Panel::WidgetType Panel::getType() const
{
    return WIDGET_TYPE_PANEL;
}

} // namespace psc

#endif // POPULUSSC_PANEL_H
