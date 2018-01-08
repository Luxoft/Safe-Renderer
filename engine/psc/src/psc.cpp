/******************************************************************************
**
**   File:        psc.cpp
**   Description:
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

#include "psc.h"
#include "Assertion.h"
#include "Pool.h"
#include "Engine.h"
#include "PgwOdiComSession.h"
#include <new>

using psc::Engine;
const size_t MAX_ENGINES = 2;

enum
{
    MAX_FUS = 10
};
typedef psc::PgwOdiComSession<MessageTypes::LAST - 1, MAX_FUS> ComSession;

class PSCEngineImpl
{
public:
    PSCEngineImpl(const psc::Database& db, PGWMailbox mailbox)
        : session(mailbox, true)
        , engine(db, session)
    {}
    ComSession session;
    Engine engine;
};

typedef psc::Pool<PSCEngineImpl, MAX_ENGINES> EnginePool;
static EnginePool g_enginePool;

extern "C"
{

PSCEngine pscCreate(const PSCDatabase* db, PGWMailbox mailbox)
{
    PSCEngine ret = NULL;
    PSCError error = PSC_NO_ERROR;
    void* mem= g_enginePool.allocate(error);
    if (NULL != mem)
    {
        psc::ResourceBuffer ddhbin(db->ddhbin, db->ddhbinSize);
        psc::ResourceBuffer imgbin(db->imgbin, db->imgbinSize);
        PSCEngineImpl* engine = new(mem)PSCEngineImpl(psc::Database(ddhbin, imgbin), mailbox);
        ret = engine;
    }
    return ret;
}

PSCError pscDelete(PSCEngine engine)
{
    PSCError error = PSC_NO_ERROR;
    if (NULL != engine)
    {
        static_cast<PSCEngineImpl*>(engine)->~PSCEngineImpl();
        error = g_enginePool.deallocate(engine);
    }
    return error;
}

PSCBoolean pscRender(PSCEngine e)
{
    PSCEngineImpl* engine = static_cast<PSCEngineImpl*>(e);
    ASSERT(engine != NULL);
    return engine->engine.render() ? PSC_TRUE : PSC_FALSE;
}

PSCBoolean pscVerify(PSCEngine e)
{
    PSCEngineImpl* engine = static_cast<PSCEngineImpl*>(e);
    ASSERT(engine != NULL);
    return engine->engine.verify() ? PSC_TRUE : PSC_FALSE;
}

PSCError pscGetError(PSCEngine e)
{
    PSCEngineImpl* engine = static_cast<PSCEngineImpl*>(e);
    ASSERT(engine != NULL);
    return engine->engine.getError();
}

} // extern "C"

