#ifndef PIL_H
#define PIL_H

/******************************************************************************
**
**   File:        pil.h
**   Description: Platform Interface Laayer for Luxoft Safe Renderer
**                Provides basic platform / OS dependent features for the
**                LSR Engine.
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


#ifdef __cplusplus
extern "C"
{
#endif

// coverity[misra_cpp_2008_rule_18_0_1_violation] <cstdint> cannot be used (C++11)
// coverity[misra_cpp_2008_rule_16_0_1_violation] C interface
#include <stdint.h>

/**
 * @brief returns the system's monotonic system time in milliseconds
 * @note There will be an overflow every 49 days
 * @return time in milliseconds
 */
uint32_t pilGetMonotonicTime(void);

/**
 * @brief Function to report failed assertions.
 * @param msg Error message.
 * @param file Source file name where assertion failed.
 * @param lineNo Line number where assertion failed.
 */
// coverity[misra_cpp_2008_rule_3_9_2_violation] Common use of char*
void pilAssert(const char* msg, const char* file, int32_t lineNo);

#ifdef __cplusplus
}
#endif

#endif //PIL_H
