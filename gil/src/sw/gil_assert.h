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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
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
