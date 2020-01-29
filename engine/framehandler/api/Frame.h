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
     * Method creates a @c Frame object and all its children with given @c WidgetPool according
     * to configuration from @c db object.
     *
     * @param[in]  factory    pool which provides allocation an @c Frame object.
     * @param[in]  db         object provides work with database.
     * @param[in]  id         frame id.
     * @param[in]  pParent    parent of the frame.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                        operation succeeded, other @c LSREngineError values otherwise.
     *
     * @return pointer to @c Frame object if initialization of object was successful,
     *         @c NULL otherwise.
     */
    static Frame* create(WidgetPool& factory,
                         const Database& db,
                         const FrameId id,
                         Window* pParent,
                         DataContext* const pContext,
                         LSRErrorCollector& error);

private:
    /**
     * Create an object.
     *
     * @param[in] pDdh @c lsr::PageType ddh configuration.
     */
    explicit Frame(const PageType* const pDdh);

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
     *
     * @return @c true.
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) P_OVERRIDE;

    /**
     * Method returns type of the widget.
     *
     * @return @c WIDGET_TYPE_FRAME value.
     */
    virtual WidgetType getType() const P_OVERRIDE;

    const PageType* m_pDdh;
};

inline Widget::WidgetType Frame::getType() const
{
  return WIDGET_TYPE_FRAME;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_FRAME_H
