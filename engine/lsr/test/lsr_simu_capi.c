/******************************************************************************
**
**   File:        lsr_simu_capi.c
**   Description: lsr_simu executable written in C
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

#include <lsr.h>
#include <Telltales.h>
#include <stdio.h>


/**
 * Verifies that the lsr.h can be used with a C compiler
 */
int main(int argc, char* argv[])
{
    LSRDatabase database = getTelltalesDDH();
    LSREngine engine = lsrCreate(database);
    LSRError err = lsrGetError(engine);

    if (LSR_NO_ERROR == err)
    {
        printf("Render 4 times\n");
        int i;
        for (i = 0; i < 4; ++i)
        {
            printf("*****************\n");
            lsrSetBoolean(engine, TELLTALES_FUTELLTALES_AIRBAG, LSR_TRUE);
            lsrRender(engine);
            lsrVerify(engine);
        }
    }
    else
    {
        printf("Error creating Engine: %d\n", err);
    }
    lsrDelete(engine);
    return 0;
}