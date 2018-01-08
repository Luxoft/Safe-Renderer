#ifndef POPULUSSC_DISPLAYACCESSOR_H
#define POPULUSSC_DISPLAYACCESSOR_H

/******************************************************************************
**
**   File:        DisplayAccessor.h
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

namespace psc
{

class DisplayAccessor
{
public:
    static DisplayAccessor& instance()
    {
        static DisplayAccessor obj;
        return obj;
    }

    void toDefault();

    void drawBitmapWasExecuted(bool flag);
    bool wasDrawBitmapExecuted() const;

    void setVerifyFlag(bool flag);
    bool getVerifyFlag() const;

    ~DisplayAccessor();

private:
    DisplayAccessor();

    bool m_drawBitmap;
    bool m_verifyFlag;
};

inline DisplayAccessor::DisplayAccessor()
{
    toDefault();
}

inline DisplayAccessor::~DisplayAccessor()
{}

inline void DisplayAccessor::toDefault()
{
    m_drawBitmap = false;
    m_verifyFlag = true;
}

inline void DisplayAccessor::drawBitmapWasExecuted(bool flag)
{
    m_drawBitmap = flag;
}

inline bool DisplayAccessor::wasDrawBitmapExecuted() const
{
    return m_drawBitmap;
}

inline void DisplayAccessor::setVerifyFlag(bool flag)
{
    m_verifyFlag = flag;
}

inline bool DisplayAccessor::getVerifyFlag() const
{
    return m_verifyFlag;
}


} // namespace psc


#endif // POPULUSSC_DISPLAYACCESSOR_H
