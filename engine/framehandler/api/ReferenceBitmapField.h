#ifndef LUXOFTSAFERENDERER_REFERENCEBITMAPFIELD_H
#define LUXOFTSAFERENDERER_REFERENCEBITMAPFIELD_H

/******************************************************************************
**
**   File:        ReferenceBitmapField.h
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

#include "Field.h"

#include <BoolExpression.h>
#include <BitmapExpression.h>

namespace lsr
{

/**
 * A non-drawing widget which checks video output.
 *
 * The ReferenceBitmap does not perform any drawing operations, but uses its connected
 * texture to perform a video output check.
 * The check is enabled if the visible flag is true.
 *
 * @reqid SW_ENG_073, SW_ENG_076
 */
class ReferenceBitmapField P_FINAL : public Field
{
public:
    /**
     * Method creates a @c ReferenceBitmapField object with given @c WidgetPool according
     * to configuration @c pDdh.
     *
     * @param[in]  factory    pool which provides allocation an @c BitmapField object.
     * @param[in]  db         object provides work with database.
     * @param[in]  pDdh       @c lsr::StaticBitmapFieldType ddh configuration.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                        operation succeeded, other @c LSREngineError values otherwise.
     *
     * @return pointer to @c ReferenceBitmapField object if initialization of object
     *         was successful, @c NULL otherwise.
     */
    static ReferenceBitmapField* create(WidgetPool& factory,
                                        const Database& db,
                                        const ReferenceBitmapFieldType* const pDdh,
                                        DataContext* const pContext,
                                        LSRErrorCollector& error);

private:
    /**
     * Create an object.
     *
     * @param[in] db   object provides work with database.
     * @param[in] pDdh @c lsr::ReferenceBitmapFieldType ddh configuration.
     */
    ReferenceBitmapField(const Database& db, const ReferenceBitmapFieldType* const pDdh);

    /**
     * Method initialize object.
     *
     * @param[in]  pContext data context, which shall be used for evaluation.
     * @param[out] error    error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                      operation succeeded, other @c LSREngineError values otherwise.
     *
     * @return @c true if object initialization succeeded, @c false otherwise.
     */
    bool setup(DataContext* const pContext, LSRErrorCollector& error);

    /**
     * Method updates internal variables (evaluates value of bitmap ID).
     * If new value differs from the older one, the invalidated flag
     * will be risen (see @c lsr::Widget::invalidate method).
     *
     * @param[in] monotonicTimeMs current monotonic system time in milliseconds.
     */
    virtual void onUpdate(const U32 monotonicTimeMs) P_OVERRIDE;

    /**
     * Method does nothing. This widget can't be drawn.
     */
    virtual void onDraw(Canvas&, const Area&) const P_OVERRIDE;

    /**
     * If visible flag is enabled, method performs video checking with @c Canvas object.
     *
     * If check fails, the error counter inside @c DataHandler will be incremented.
     * See @c IncrementErrorCounter.
     *
     * @param[in] dst  destination canvas object which provides checking functionality.
     * @param[in] rect area in absolute coordinates.
     *
     * @return @true if check successes or visible flag is @c false, @c false otherwise.
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) P_OVERRIDE;

    /**
     * Method returns type of the widget.
     *
     * @return @c WIDGET_TYPE_REF_BITMAP_FIELD value.
     */
    virtual Widget::WidgetType getType() const P_OVERRIDE;

    bool setupVisibilityExpr(DataContext* const pContext);
    bool setupBitmapExr(DataContext* const pContext);

    /**
     * Method increments error counter inside @c DataHandler object.
     *
     * As error counter is stored in the @c DataHandler object as data linked with internal FU,
     * there can be error while getting this value from @c DataHandler.
     * In this case the appropriate error flag will be risen.
     *
     * If there will be an error in setting data to @c DataHandler
     * (see @c lsr::DataHandler::setData method)
     * the @c lsr::LSR_DH_INVALID_DATA_ID error will be risen.
     */
    void incrementErrorCounter();

    void resetErrorCounter();

    const ReferenceBitmapFieldType* m_pDdh;
    const Database& m_db;
    BoolExpression m_visibilityExpr;
    BitmapExpression m_bitmapExpr;
    DataContext* m_pContext;
    BitmapId m_bitmapId;
};

inline Widget::WidgetType ReferenceBitmapField::getType() const
{
    return WIDGET_TYPE_REF_BITMAP_FIELD;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_REFERENCEBITMAPFIELD_H
