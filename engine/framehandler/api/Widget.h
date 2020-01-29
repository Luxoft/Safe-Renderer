#ifndef LUXOFTSAFERENDERER_WIDGET_H
#define LUXOFTSAFERENDERER_WIDGET_H

/******************************************************************************
**
**   File:        Widget.h
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

#include <LsrTypes.h>
#include <LSRLimits.h>
#include <LSREngineError.h>
#include <LSRErrorCollector.h>
#include <NonCopyable.h>

#include <Area.h>

#include <DataStatus.h>

namespace lsr
{

class BoolExpression;
class Canvas;
class WidgetPool;

/**
 * Implements base functionality for all widgets.
 *
 * @reqid SW_ENG_068, SW_ENG_070, SW_ENG_071, SW_ENG_073
 */
// coverity[misra_cpp_2008_rule_12_8_2_violation] Base class NonCopyable hides assignment operator
class Widget : private NonCopyable
{
public:
    /**
     * Method call the @c widgets destructor and disposes given @c pWidget from @c WidgetPool.
     *
     * @param[in] factory    the pool, where @c pWidget object was previously allocated.
     * @param[in] pWidget    the object which should be disposed.
     *
     * @return @c LSR_NO_ENGINE_ERROR if dispose was successful, and other values of
     *         @c LSREngineError in other cases.
     */
    static LSREngineError dispose(WidgetPool& factory, Widget* const pWidget);

    /**
     * Informs the widget about the monotonic system time
     * It's called once for every main loop iteration.
     * If there were some changes in the internal information,
     * widget will be set to invalidated state.
     *
     * @param[in] monotonicTimeMs current monotonic system time in milliseconds.
     */
    void update(const U32 monotonicTimeMs);

    /**
     * Draws the widget on the given canvas.
     *
     * @param[in] dst  destination canvas, see @c Canvas.
     * @param[in] rect area in absolute coordinates.
     */
    void draw(Canvas& dst, const Area& rect);

    /**
     * Performs a pixel verification on the given canvas
     *
     * @param[in] dst  destination canvas, see @c Canvas.
     * @param[in] rect area in absolute coordinates.
     *
     * @returns @c false if any error was detected, @c true if there's no error
     *          detected or no error check performed.
     */
    bool verify(Canvas& dst, const Area& rect);

    /**
     * Returns the child at the given index.
     * Indexing starts with 0 value.
     *
     * @param[in] index child index. Should be in [0, @c numChildren].
     *
     * @return NULL pointer if @c index is out of [0, @c numChildren],
     *         correct pointer to @c Widget otherwise.
     */
    Widget* childAt(const std::size_t index) const;

    /**
     * @return the number of child widgets.
     */
    std::size_t numChildren() const;

    /**
     * @return the area which the widget occupies on screen relative to its parent
     */
    const Area& getArea() const;

    /**
     * Method return the worst error, which can occur inside @c Widget children.
     *
     * @return the worst error. See @c LSREngineError.
     */
    LSREngineError getError() const;

    virtual ~Widget();

protected:
    enum WidgetType
    {
        WIDGET_TYPE_WINDOW = 0,
        WIDGET_TYPE_FRAME,
        WIDGET_TYPE_PANEL,
        WIDGET_TYPE_BITMAP_FIELD,
        WIDGET_TYPE_REF_BITMAP_FIELD
    };

    Widget();

    /**
     * Say to object, that it has invalidated state.
     */
    void invalidate();

    /**
     * @return @c true if widget needs to be validated, @c false otherwise.
     */
    bool isInvalidated() const;

    /**
     * Add pointer to widget object as child.
     *
     * @param[in] pChild pointer to widget which should be added as child.
     *
     * @return @c true if object was successfully added, @c false
     *         if maximum count of children has already reached.
     */
    bool addChild(Widget* const pChild);

    /**
     * @param[in] rect area in relative coordinates to widgets parent
     */
    void setArea(const Area& rect);
    bool setArea(const AreaType* const pDdhArea);

    /**
     * Save error in the widget.
     *
     * @param[in] error error value which should be saved.
     */
    void setError(const LSREngineError error);

    /**
     * Method should be used for updating (evaluating) internal widgets parameters such as
     * bitmapId, visibility flag, etc.
     *
     * This method will be called from @c update method.
     *
     * Should be implemented in children.
     *
     * @param[in] monotonicTimeMs current monotonic system time in milliseconds.
     */
    virtual void onUpdate(const U32 monotonicTimeMs) = 0;

    /**
     * Methods provides functionality to draw widgets child.
     *
     * This method will be called from @c draw method.
     *
     * Should be implemented in children.
     *
     * @param[in] dst  the destination canvas which shall implement drawing.
     * @param[in] rect area of widget, were it shall be drawn.
     */
    virtual void onDraw(Canvas& dst, const Area& rect) const = 0;

    /**
     * Methods provides functionality to check video output.
     *
     * This method will be called from @c verify method.
     *
     * Should be implemented in children.
     *
     * @param[in] dst  the destination canvas which shall implement drawing.
     * @param[in] rect area of widget, were it shall be drawn.
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) = 0;

    /**
     * Returns the widgets type, see @c WidgetType.
     *
     * Should be implemented in children.
     *
     * @return widgets type.
     */
    virtual WidgetType getType() const = 0;

    /**
     * @return @c false if visibility expression was set (see @c setVisibilityExpression) and
     *         widget is marked as not visible, @c true otherwise.
     */
    bool isVisible() const;

    /**
     * Method sets an expression for evaluating visibility flag.
     *
     * @param[in] pExpr pointer to visibility expression. See @c BoolExpression.
     */
    void setVisibilityExpression(const BoolExpression* const pExpr);

    /**
     * Method tries to get value from @c Expression @c T.
     * If the result has status @c DataStatus::VALID,
     * this result is copied to @c value param, otherwise @c value will be unchanged,
     * and an error flag will be set (see @c setError)
     *
     * @tparam T expression type
     * @tparam K value type
     *
     * @param[in]  expr Expression which is needed to evaluate.
     * @param[out] value the result of expression evaluation.
     *
     * @return @c true if the result of evaluation @c expr has
     *         status @c DataStatus::VALID, @c false otherwise.
     */
    template <class T, class K>
    bool tryToUpdateValue(const T& expr, K& value);

    /**
     * Method updates the visibility flag.
     * It reevaluates the visibility expression which was set be @c setVisibilityExpression.
     */
    void updateVisibility(/* const U32 monotonicTimeMs */);
private:

    Area m_area;
    std::size_t m_childrenCount;
    bool m_isInvalidated;
    LSRErrorCollector m_error;
    const BoolExpression* m_pVisibilityExpr;
    bool m_isVisible;

    // TODO:
    // Should we optimize it?
    // if yes, we can store inside each widget and configure it with
    // specific number. thus widget will become template with
    // count of childs as template parameter value.
    // this number can be calculated by Editor.
    // from other hand, it will be not very large array.
    // but existing in each widget object.
    Widget* m_children[MAX_WIDGET_CHILDREN_COUNT];
};

inline std::size_t Widget::numChildren() const
{
    return m_childrenCount;
}

inline const Area& Widget::getArea() const
{
    return m_area;
}

inline void Widget::setError(const LSREngineError error)
{
    m_error = error;
}

inline bool Widget::isVisible() const
{
    return m_isVisible;
}

inline void Widget::setVisibilityExpression(const BoolExpression* const pExpr)
{
    m_pVisibilityExpr = pExpr;
}

template <class T, class K>
bool Widget::tryToUpdateValue(const T& expr, K& value)
{
    const DataStatus status = expr.getValue(value);

    const bool valueIsValid = (status == DataStatus::VALID);
    if (!valueIsValid)
    {
        setError(status.convertToLSRError());
    }

    return valueIsValid;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_WIDGET_H
