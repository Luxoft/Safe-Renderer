#ifndef POPULUSSC_ASSERTION_H
#define POPULUSSC_ASSERTION_H

/******************************************************************************
**
**   File:        Assertion.h
**   Description: Provides assertion macros: ASSERT, ASSERT_MSG,
**                REQUIRE, REQUIRE_MSG
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
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

namespace psc
{

namespace impl
{

/**
 * @internal
 *
 * This function is called when an assertion fails.
 * It will execute @c pgwAssert function.
 *
 * @param msg a text string describing the failed assertion - must not be null
 * @param file the source file where the assertion was generated - must not be null
 * @param line the line number where the assertion was generated
 */
bool executeAssert(const char* msg, const char* file, int line);

} // namespace impl

} // namespace psc

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
((void)((expression) || (::psc::impl::executeAssert(#expression, __FILE__, __LINE__) || true)))

/**
 * ASSERT_MSG is quite similar to ASSERT but provides a user defined
 * message instead of an auto-generated one.
 *
 * @param expression A boolean expression to be evaluated
 * @param message A user defined message that will be logged.
 */
#define ASSERT_MSG(expression, message) \
((void)((expression) || (::psc::impl::executeAssert(message, __FILE__, __LINE__) || true)))

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
(((expression) || (::psc::impl::executeAssert(#expression, __FILE__, __LINE__))))

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
(((expression) || (::psc::impl::executeAssert(message, __FILE__, __LINE__))))

#endif // NDEBUG

#endif // POPULUSSC_ASSERTION_H
