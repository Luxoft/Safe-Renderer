#ifndef LUXOFTSAFERENDERER_ASSERTION_H
#define LUXOFTSAFERENDERER_ASSERTION_H

/******************************************************************************
**
**   File:        Assertion.h
**   Description: Provides assertion macros: ASSERT, ASSERT_MSG,
**                REQUIRE, REQUIRE_MSG
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

#undef ASSERT
#undef ASSERT_MSG
#undef REQUIRE
#undef REQUIRE_MSG

#ifdef NDEBUG

#define ASSERT(expression)               ((void)0)
#define ASSERT_MSG(expression, message)  ((void)0)
#define REQUIRE(expression)              (expression)
#define REQUIRE_MSG(expression, message) (expression)

#else

#include <stdint.h>

namespace lsr
{

namespace impl
{

/**
 * @internal
 *
 * This function is called when an assertion fails.
 * It will execute @c pilAssert function.
 *
 * @param msg a text string describing the failed assertion - must not be null
 * @param file the source file where the assertion was generated - must not be null
 * @param line the line number where the assertion was generated
 */
bool executeAssert(const char* const msg, const char* const file, const int32_t line);

} // namespace impl

} // namespace lsr

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
#define ASSERT(expression) \
((void)((expression) || (::lsr::impl::executeAssert(#expression, __FILE__, __LINE__) || true)))

/**
 * ASSERT_MSG is quite similar to ASSERT but provides a user defined
 * message instead of an auto-generated one.
 *
 * @param expression A boolean expression to be evaluated
 * @param message A user defined message that will be logged.
 */
#define ASSERT_MSG(expression, message) \
((void)((expression) || (::lsr::impl::executeAssert(message, __FILE__, __LINE__) || true)))

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
#define REQUIRE(expression) \
(((expression) || (::lsr::impl::executeAssert(#expression, __FILE__, __LINE__))))

/**
 * REQUIRE_MSG is quite similar to REQUIRE but provides a user defined
 * message instead of an auto-generated one.
 *
 * @param expression A boolean expression to be evaluated
 * @param message A user defined message that will be logged.
 *
 * @return the boolean value of the given expression
 */
#define REQUIRE_MSG(expression, message) \
(((expression) || (::lsr::impl::executeAssert(message, __FILE__, __LINE__))))

#endif // NDEBUG

#endif // LUXOFTSAFERENDERER_ASSERTION_H
