/******************************************************************************
**
**   File:        lsr.cpp
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

#include "lsr_p.h"
#include "lsr.h"
#include "Assertion.h"
#include "Pool.h"
#include "Engine.h"
#include "pil.h"

#include <ddh_defs.h>
#include <Number.h>
#include <DataStatus.h>
#include <new>

using lsr::Engine;

namespace
{

// coverity[misra_cpp_2008_rule_0_1_4_violation] Used as template parameter to avoid magic numbers
// coverity[misra_cpp_2008_rule_0_1_6_violation : FALSE] Used as template parameter
const size_t MAX_ENGINES = 2U;

typedef lsr::Pool<lsr_engine_t, MAX_ENGINES> EnginePool;
EnginePool g_enginePool;

} // anonymous namespace


extern "C"
{

LSREngine lsrCreate(const LSRDatabase db)
{
    LSREngineError error = LSR_NO_ENGINE_ERROR;
    void* const mem = g_enginePool.allocate(error);
    LSREngine engine = (NULL != mem) ? new(mem)lsr_engine_t(static_cast<const lsr::DDHType* const>(db)) : NULL;
    return engine;
}

void lsrDelete(const LSREngine engine)
{
    if (NULL != engine)
    {
        engine->~lsr_engine_t();
        static_cast<void>(g_enginePool.deallocate(engine));
    }
}

LSRBoolean lsrRender(const LSREngine engine)
{
    ASSERT(engine != NULL);
    return engine->getEngine().render() ? static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

LSRBoolean lsrVerify(const LSREngine engine)
{
    ASSERT(engine != NULL);
    return engine->getEngine().verify() ? static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

LSRBoolean lsrSetBoolean(const LSREngine engine,
                       const LSRFUDataId fuDataId,
                       const LSRBoolean value)
{
    ASSERT(engine != NULL);

    lsr::Number tmpValue(value == LSR_TRUE);
    const lsr::DataStatus status = lsr::DataStatus::VALID;

    return engine->getEngine().setData(lsr::DynamicData(fuDataId), tmpValue, status) ?
        static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

LSRBoolean lsrSetInteger(const LSREngine engine,
                       const LSRFUDataId fuDataId,
                       const LSRBoolean value)
{
    ASSERT(engine != NULL);
    lsr::Number tmpValue(static_cast<U32>(value), lsr::DATATYPE_INTEGER);
    const lsr::DataStatus status = lsr::DataStatus::VALID;

    return engine->getEngine().setData(lsr::DynamicData(fuDataId), tmpValue, status) ?
        static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

// coverity[misra_cpp_2008_rule_7_1_2_violation] C interface
LSRDataStatus lsrGetBoolean(const LSREngine engine, const LSRFUDataId fuDataId, LSRBoolean* const value)
{
    ASSERT(engine != NULL);
    lsr::Number tmpValue;
    lsr::DataStatus status = engine->getEngine().getData(lsr::DynamicData(fuDataId), tmpValue);
    if (tmpValue.getType() == lsr::DATATYPE_BOOLEAN)
    {
        if (value != NULL)
        {
            *value = tmpValue.getBool() ? static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
        }
    }
    else
    {
        static_cast<void>(status);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        status = lsr::DataStatus::INCONSISTENT;
    }
    return static_cast<LSRDataStatus>(status.getValue());
}

// coverity[misra_cpp_2008_rule_7_1_2_violation] C interface
LSRDataStatus lsrGetInteger(const LSREngine engine, const LSRFUDataId fuDataId, int32_t* const value)
{
    ASSERT(engine != NULL);
    lsr::Number tmpValue;
    // coverity[misra_cpp_2008_rule_0_1_6_violation] Status is initialized here and overwritten in else case
    lsr::DataStatus status = engine->getEngine().getData(lsr::DynamicData(fuDataId), tmpValue);
    if (tmpValue.getType() == lsr::DATATYPE_INTEGER)
    {
        if (value != NULL)
        {
            *value = static_cast<int32_t>(tmpValue.getU32());
        }
    }
    else
    {
        status = lsr::DataStatus::INCONSISTENT;
    }
    return static_cast<LSRDataStatus>(status.getValue());
}

LSRError lsrGetError(const LSREngine engine)
{
    return (NULL != engine) ? engine->getEngine().getError().getValue() : LSR_UNKNOWN_ERROR;
}

} // extern "C"
