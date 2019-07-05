#ifndef GIL_ASSERT_H
#define GIL_ASSERT_H

/******************************************************************************
**
**   File:        gil_assert.h
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

#include <gil.h>

GILBoolean gilExecuteAssert(const char* msg, const char* file, int line);

/**
 * ASSERT evaluates boolean expression.
 * If the expression evaluates to false, a callback (executeAssert)
 * will be invoked.
 *
 * @important If assertions are disabled (NDEBUG was defined)
 * the expression will not be evaluated.
 * So please never use expressions with side-effects!
 *
 * @param expression A boolean expression to be evaluated
 */
#define GIL_ASSERT(expression) \
((void)((expression) || ((gilExecuteAssert(#expression, __FILE__, __LINE__) ? GIL_TRUE : GIL_FALSE) || GIL_TRUE)))

/**
 * REQUIRE evaluates boolean expression.
 * If the expression evaluates to false, a callback (executeAssert)
 * will be invoked.
 *
 * In contrast to ASSERT the expression will always be evaluated
 *
 * @param expression A boolean expression to be evaluated
 *
 * @return the boolean value of the given expression
 */
#define GIL_REQUIRE(expression) \
(((expression) || ((gilExecuteAssert(#expression, __FILE__, __LINE__) ? GIL_TRUE : GIL_FALSE))))

#endif // GIL_ASSERT_H
