#ifndef LUXOFTSAFERENDERER_LSR_ENGINE_ERROR_H
#define LUXOFTSAFERENDERER_LSR_ENGINE_ERROR_H

/******************************************************************************
**
**   File:        LSREngineError.h
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

/**
 * List of errors in the LSR Engine
 * This list is sorted by ascending severity
 */
// coverity[misra_cpp_2008_rule_7_3_1_violation] C interface
// coverity[misra_cpp_2008_rule_8_5_3_violation] offset to disambiguate between different error domains
typedef enum
{
    LSR_NO_ENGINE_ERROR = 0U,
    LSR_DH_INVALID_DATA_ID = 0x1000000U, // offset to disambiguate between different error domains
    LSR_POOL_INVALID_OBJECT,
    LSR_ERR_DATASTATUS_NOT_AVAILABLE,
    LSR_ERR_DATASTATUS_INVALID,
    LSR_ERR_DATASTATUS_INCONSISTENT,
    LSR_POOL_IS_FULL,
    LSR_POOL_DOUBLE_DELETE,
    LSR_POOL_IS_CORRUPTED,
    LSR_ERROR_NO_TEXTURE, // no texture could be allocated for an image (configuration error)
    LSR_DB_INCONSISTENT,
    LSR_DB_ERROR,
    LSR_DB_DDHBIN_VERSION_MISMATCH,
    LSR_DB_DDHBIN_EMPTY
} LSREngineError;

#endif // LUXOFTSAFERENDERER_LSR_ENGINE_ERROR_H
