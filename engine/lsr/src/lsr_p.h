#ifndef LSR_P_H
#define LSR_P_H

/******************************************************************************
**
**   File:        lsr_p.h
**   Description: Private header for lsr.cpp
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

#include <DDHType.h>
#include <Engine.h>

extern "C"
{

/**
 * Helper struct to use an opaque type LSREngine instead of a void* pointer in
 * the C interface (avoids MISRA 5-2-8).
 */
// coverity[misra_cpp_2008_rule_7_3_1_violation] C interface
struct lsr_engine_t
{
    /**
     * Constructor.
     *
     * @param pDdh Pointer to the database
     */
    explicit lsr_engine_t(const lsr::DDHType* const pDdh);

    /**
     * Destructor.
     */
    ~lsr_engine_t();

    /**
     * Returns a reference to the engine.
     * @return a reference to the engine
     */
    lsr::Engine& getEngine();

private:
    lsr_engine_t(const lsr_engine_t&);  ///< Hidden copy constructor
    lsr_engine_t& operator=(const lsr_engine_t&);  ///< Hidden assignment operator

    lsr::Engine m_engine;  ///< Engine instance
};


inline lsr_engine_t::lsr_engine_t(const lsr::DDHType* const pDdh)
: m_engine(pDdh)
{
}

inline lsr_engine_t::~lsr_engine_t()
{
}

inline lsr::Engine& lsr_engine_t::getEngine()
{
    // coverity[misra_cpp_2008_rule_9_3_2_violation] Struct contains non-POD member (has to be private)
    return m_engine;
}

} // extern "C"

#endif // LSR_P_H
