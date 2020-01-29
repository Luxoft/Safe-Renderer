#ifndef LUXOFTSAFERENDERER_POOLEDOBJECTFACTORY_H
#define LUXOFTSAFERENDERER_POOLEDOBJECTFACTORY_H

/******************************************************************************
**
**   File:        PooledObjectFactory.h
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

#include "Pool.h"
#include "LsrTypes.h"
#include "LSREngineError.h"

#include <cstddef>

namespace lsr
{

/**
 * This factory can create objects with type @c T in some fixed size (see @c PoolSize)
 * memory pool and destroy objects which were previously created by
 * @c PooledObjectFactory::createObject method.
 *
 * Objects which were created with @c PooledObjectFactory::createObject method must be destroyed only
 * with @c PooledObjectFactory::deleteObject method.
 *
 * @note
 * The @c PooledObjectFactory::createObject methods do not have 100% branch coverage
 * in calling placement new operator.
 * gcc and cl compilers check placement new operators for NULL pointers.
 * In the @c PooledObjectFactory::createObject methods there is an additional check for this condition,
 * that's why operator new::condition never goes via false branch, that's why we don't have 100%
 * branch coverage. But we needed to add such additional check
 * because we cannot be sure that every compiler behaves like gcc or cl in this case.
 *
 * @tparam T the type of objects which would be created and will be stored in the pool.
 *           Objects of this type should have constant size during runtime.
 * @tparam PoolSize the maximum number of objects with type @c T which the pool can hold.
 * @tparam AlignValue the alignment value in the pool in bytes.
 */
template<class T, std::size_t PoolSize, std::size_t AlignValue = sizeof(P_MAX_ALIGN)>
class PooledObjectFactory
{
public:
    PooledObjectFactory()
        : m_pool()
    {
    }

    /**
     * Allocates an instance from the pool using placement new.
     * Constructor will be called.
     *
     * @param[out] error the error value which should be set during operation execution.
     *                   If this value is equal to @c LSR_NO_ENGINE_ERROR, operation
     *                   finished successfully, and failed in other cases.
     *
     * @return pointer to the instance of type @c T.
     *         Returned pointer is not equal to NULL only if @c error == @c LSR_NO_ENGINE_ERROR.
     */
    inline T* createObject(LSREngineError& error)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T());
        }
        return res;
    }

    /**
     * Allocates an instance from the pool using placement new.
     * Constructor with one parameter will be called.
     *
     * @param[out] error the error value which should be set during allocation.
     *                   If this value is equal to @c LSR_NO_ENGINE_ERROR, operation
     *                   finished successfully, and failed in other cases.
     * @param[in]  arg1 some argument which is needed for constructor.
     *
     * @return pointer to the instance of type @c T.
     *         Returned pointer is not equal to NULL only if @c error == @c LSR_NO_ENGINE_ERROR.
     */
    template<class TArg1>
    inline T* createObject(LSREngineError& error, TArg1 arg1)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1));
        }
        return res;
    }

    template<class TArg1, class TArg2>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2));
        }
        return res;
    }

    template<class TArg1, class TArg2, class TArg3>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3));
        }
        return res;
    }

    template<class TArg1, class TArg2, class TArg3, class TArg4>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3, arg4));
        }
        return res;
    }

    template<class TArg1, class TArg2, class TArg3, class TArg4, class TArg5>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3, arg4, arg5));
        }
        return res;
    }

    template<class TArg1, class TArg2,
             class TArg3, class TArg4,
             class TArg5, class TArg6>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3, arg4, arg5, arg6));
        }
        return res;
    }

    template<class TArg1, class TArg2,
             class TArg3, class TArg4,
             class TArg5, class TArg6,
             class TArg7>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4,
                           TArg5 arg5, TArg6 arg6, TArg7 arg7)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
        }
        return res;
    }

    template<class TArg1, class TArg2,
             class TArg3, class TArg4,
             class TArg5, class TArg6,
             class TArg7, class TArg8>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4,
                           TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));
        }
        return res;
    }

    template<class TArg1, class TArg2,
             class TArg3, class TArg4,
             class TArg5, class TArg6,
             class TArg7, class TArg8,
             class TArg9>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4,
                           TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9));
        }
        return res;
    }

    template<class TArg1, class TArg2,
             class TArg3, class TArg4,
             class TArg5, class TArg6,
             class TArg7, class TArg8,
             class TArg9, class TArg10>
    inline T* createObject(LSREngineError& error, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4,
                           TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8,
                           TArg9 arg9, TArg10 arg10)
    {
        T* res = NULL;
        void* ptr = m_pool.allocate(error);
        if (NULL != ptr)
        {
            res = static_cast<T*>(new (ptr)T(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10));
        }
        return res;
    }

    /**
     * Frees an instance from the pool.
     * Destructor will be called.
     *
     * @param[in] instance the instance of type @c T which should be freed.
     *
     * @return @c LSR_NO_ENGINE_ERROR if object deletion was successful, and other values of
     *         @c LSREngineError in other cases.
     */
    LSREngineError deleteObject(T* instance)
    {
        LSREngineError res = LSR_NO_ENGINE_ERROR;
        if(NULL != instance && m_pool.isAllocated(instance))
        {
            instance->~T();
            res = m_pool.deallocate(instance);
        }
        else
        {
            res = LSR_POOL_INVALID_OBJECT;
        }
        return res;
    }

    /**
     * Methods checks the internal storage for correctness.
     *
     * @return @c true if internal storage is in the correct state, @c false otherwise.
     *         @c false result can be interpreted as @c LSR_POOL_IS_CORRUPTED
     *         value.
     */
    bool checkFactory() const
    {
        return m_pool.checkPool();
    }

private:
    Pool<T, PoolSize, AlignValue> m_pool;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_POOLEDOBJECTFACTORY_H
