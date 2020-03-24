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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include <LsrTypes.h>
#include <LSRLimits.h>
#include <LSREngineError.h>
#include <LSRErrorCollector.h>
#include <NonCopyable.h>

#include <Area.h>

namespace lsr
{

class Canvas;

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
     * @return @c false if any error was detected, @c true if there's no error
     *          detected or no error check performed.
     */
    bool verify(Canvas& dst, const Area& rect);

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

    /**
     * @return @c true if widget needs to be validated, @c false otherwise.
     */
    bool isInvalidated() const;

    /**
     * @return @c false if visibility expression was set (see @c setVisibilityExpression) and
     *         widget is marked as not visible, @c true otherwise.
     */
    bool isVisible() const;

    /**
     * Sets the visibility of this widget
     * Visibility expression will be removed (if configured)
     * @param visible new visibility status
     */
    void setVisible(const bool visible);

    /**
     * Sets the visibility of this widget
     * @param visible ddh term which contains a boolean information
     * @return false if visible is invalid (bad term type or NULL)
     */
    bool setVisible(const ExpressionTermType* const visible);

protected:
    Widget();

    /**
     * Say to object, that it has invalidated state.
     */
    void invalidate();

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
     * Returns the (highest) error code that a child widget reports
     * @param LSR_NO_ENGINE_ERROR if no error occurred, error code otherwise
     */
    virtual LSREngineError getChildError() const = 0;

    /**
     * Reports invalidation flag for child widgets
     * @return true if any child needs to be redrawn, false otherwise
     */
    virtual bool isChildInvalidated() const = 0;

private:
    Area m_area;
    bool m_isInvalidated;
    LSRErrorCollector m_error;
    bool m_isVisible;
};

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

} // namespace lsr

#endif // LUXOFTSAFERENDERER_WIDGET_H
