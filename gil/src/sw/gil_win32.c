/******************************************************************************
**
**   File:        gil_win32.c
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

// To do: Which functions are independent / and wich are dependent?

// --> We have a SW bitblitting library (platform independent)
// --> We have functions to get memory pointers - render targets (platform dependent)

#include "gil_win32.h"
#include "gil_sw_renderer.h"
#include "gil_assert.h"

/*  Trim fat from windows*/
#define WIN32_LEAN_AND_MEAN
//#pragma comment(linker, "/subsystem:windows")
/*  Pre-processor directives*/
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct gil_surface_t
{
    HWND mHWND;
    BITMAPINFO mBitmapInfo;
    uint8_t * mBitmapMemory;
    uint32_t mSize; // Size in memory in bytes
    GILFormat mFormat;
    GILBoolean mValid;
	uint32_t windowWidth;
} gil_surface_t;

typedef struct
{
    uint8_t window;
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
    GILSurface surface;
} gil_window_creation_t;

static HINSTANCE gs_Instance = 0;
static GILBoolean   windowClassTypeRegistered = GIL_FALSE;              //flag saying if the window class type is already registered

static gil_surface_t gsSurfaces[GIL_MAX_SURFACES] = { 0 };

/*  Windows Procedure Event Handler*/
// As we have no synchronisation or double buffering between the threads we may get tearing artifacts visible in the window
// As we do not do animations and fast updates this problem can't happen
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT paintStruct;
    LRESULT retVal = 0;
    /*  Device Context*/
    HDC hDC;

    GILSurface rt =(GILSurface) GetWindowLongPtr(hwnd, GWLP_USERDATA);

    /*  Switch message, condition that is met will execute*/
    switch (message)
    {
        /*  Window is being created*/
    case WM_CREATE:
        break;
        /*  Window is closing*/
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
        /*  Window needs update*/
    case WM_PAINT:
        hDC = BeginPaint(hwnd, &paintStruct);
        if (gilIsValidSurface(rt,GIL_TRUE) && rt->mBitmapMemory)
        {

            SetDIBitsToDevice(
                hDC,
                0,
                0,
                rt->mBitmapInfo.bmiHeader.biWidth,
                -rt->mBitmapInfo.bmiHeader.biHeight,
                0,
                0,
                0,
                -rt->mBitmapInfo.bmiHeader.biHeight,
                rt->mBitmapMemory,
                (const BITMAPINFO*)&rt->mBitmapInfo,
                DIB_RGB_COLORS
            );
        }

        /*  Set txt color to blue*/
        //SetTextColor(hDC, 0x00FF0000);
        /*  Display text in middle of window*/
        //TCHAR string[] = _T("Test");
        //TextOut(hDC, 150, 150, string, ARRAYSIZE(string));
        EndPaint(hwnd, &paintStruct);
        break;
    default:
        retVal = DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }
    return retVal;
}

void gilUninit(void)
{
}

void gilInit(GILConfig config)
{
    // Under windows this is used to register the window class type and checks are performed that the method is only called once!
    if (GIL_REQUIRE(!windowClassTypeRegistered)) // Ensure that it is not called twice
    {
        WNDCLASSEX  windowClass;        //window class

        /*  Fill out the window class structure*/
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WndProc;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = gs_Instance;
        windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        windowClass.lpszMenuName = NULL;
        windowClass.lpszClassName = _T("LSR");
        windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
        /*  Register window class*/
        windowClassTypeRegistered = (RegisterClassEx(&windowClass) != 0);
    }
}

DWORD createWindow(gil_window_creation_t* param)
{
    HWND        hwnd;               //window handle
    GILBoolean done = GIL_FALSE; //initialize loop condition variable
                                 /* main message loop*/
    _TCHAR title[] = _T("%: Luxoft Safe Renderer ISO26262 ASIL Level B");
    gil_window_creation_t *winparams = (gil_window_creation_t*)param;

    // check that param can really store the value of a pointer! (could be 64 bit issue)
    if (GIL_REQUIRE(sizeof(param) >= sizeof(gil_window_creation_t*))
        && GIL_REQUIRE(winparams && winparams->surface))
    {
        RECT rect = { 0, 0, winparams->w, winparams->h };
        DWORD styleEx = 0;
        DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU;
        AdjustWindowRectEx(&rect, style, FALSE, styleEx);
        title[0] = winparams->window + '0';
        hwnd = CreateWindowEx(styleEx,        //extended style
            _T("LSR"),            //class name
            title,      //app name
            style,
            winparams->x, winparams->y, //100, 100,         //x/y coords
            rect.right-rect.left, rect.bottom-rect.top,         //width,height
            NULL,               //handle to parent
            NULL,               //handle to menu
            gs_Instance,            //application instance
            NULL);              //no extra parameter's
                                /*  Check if window creation failed*/
        if (hwnd)
        {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)winparams->surface); // Assign the surface structure with the window (to make differentiation within WindowProc possible)
            winparams->surface->mHWND = hwnd;
            winparams->surface->mValid = GIL_TRUE;
        }
    }
    return 0u;
}

GILSurface gilCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h)
{
    GILSurface retVal = NULL;
    BITMAPINFO * bmi = NULL;
    gil_window_creation_t winparams = { window, x, y, w, h };

    if (GIL_REQUIRE(window < GIL_MAX_SURFACES) && GIL_REQUIRE(x >= 0) && GIL_REQUIRE(y >= 0) && GIL_REQUIRE(w > 0) && GIL_REQUIRE(h > 0) && GIL_REQUIRE(gsSurfaces[window].mValid == GIL_FALSE))
    {
        /*  Class registerd, so now create window*/
        if (GIL_REQUIRE(windowClassTypeRegistered)) // test if gilInit was called --> Class has been registered
        {
            retVal = &gsSurfaces[window];
            //SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR) retVal); // Assign the surface structure with the window (to make differentiation within WindowProc possible)
            //retVal->mHWND = hwnd;
            //retVal->mValid = GIL_TRUE;
            retVal->mValid = GIL_FALSE;
            retVal->mFormat = GIL_FORMAT_BGRA_8888;
            // retVal->mFormat = GIL_FORMAT_BGR_888;
            const uint8_t bpp = gil_helper_getbpp(retVal->mFormat);
            retVal->mSize = w * h * bpp;
            retVal->mBitmapMemory = malloc(retVal->mSize); // for simplicity under windows always 4 bpp (32 bits) are allocated (as being the maximum format)
            bmi = &retVal->mBitmapInfo;
            bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi->bmiHeader.biWidth = w;
            bmi->bmiHeader.biHeight = -h;
            bmi->bmiHeader.biPlanes = 1;

            const uint8_t bitInByte = 8;
            bmi->bmiHeader.biBitCount = bitInByte * bpp;
            bmi->bmiHeader.biCompression = BI_RGB;
            bmi->bmiHeader.biSizeImage = 0;
            bmi->bmiHeader.biXPelsPerMeter = 1;
            bmi->bmiHeader.biYPelsPerMeter = 1;
            bmi->bmiHeader.biClrUsed = 0;
            bmi->bmiHeader.biClrImportant = 0;

            winparams.surface = retVal;
            createWindow(&winparams);
        }
    }

    return retVal;
}

GILBoolean gilIsValidSurface(GILSurface surface, GILBoolean check4content)
{
    return GIL_REQUIRE(surface) // check if context is valid - additional check to see if surface is special NULL pointer
        && (!check4content || GIL_REQUIRE(surface->mValid)) // valid flag set?
        && GIL_REQUIRE(surface >= &gsSurfaces[0]) // check if surface points to valid memory
        && GIL_REQUIRE(surface < &gsSurfaces[GIL_MAX_SURFACES]);
}

GILBoolean gilSwapBuffers(GILSurface surface)
{
    GILBoolean retVal = gilIsValidSurface(surface,GIL_TRUE);
    if (retVal && surface)
    {
        InvalidateRect(surface->mHWND, NULL, TRUE);
        // As it is for manual debugging only (windows output) we take seldom tearing artifacts in account and it is OK (just in case of heavy drawing operations and single buffering)
    }
    return retVal;
}

GILBoolean gilHandleWindowEvents(GILContext context)
{
    MSG msg;
    GILBoolean close = GIL_FALSE;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) //check for a quit message
        {
            close = GIL_TRUE; //if found, quit app
        }
        else
        {
            /*  Translate and dispatch to event queue*/
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return close;
}

GILBoolean gilSurfaceToSWSurface(GILSurface s, GIL_SW_Surface * swsurface)
{
    GILBoolean bRet = swsurface && gilIsValidSurface(s, GIL_TRUE);

    if (swsurface)
    {
        swsurface->alignment = bRet ? gil_helper_getbpp(s->mFormat)*s->mBitmapInfo.bmiHeader.biWidth : 0;
        swsurface->bytes = bRet ? s->mSize : 0;
        swsurface->x = 0;
        swsurface->y = 0;
        swsurface->w = bRet ? s->mBitmapInfo.bmiHeader.biWidth : 0;
        swsurface->h = bRet ? (-s->mBitmapInfo.bmiHeader.biHeight) : 0;
        swsurface->p = bRet ? s->mBitmapMemory : NULL;
        swsurface->format = bRet ? s->mFormat : GIL_FORMAT_INVALID;
    }

    return bRet;
}

//GILFormat gilSurfaceGetFormat(GILSurface surface)
//{
//  GILFormat retVal = GIL_FORMAT_INVALID;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = s->mFormat;
//  }
//
//  return retVal;
//}

//int32_t gilSurfaceGetWidth(GILSurface surface)
//{
//  int32_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface,GIL_FALSE))
//  {
//      retVal = s->mBitmapInfo.bmiHeader.biWidth;
//  }
//
//  return retVal;
//}
//
//int32_t gilSurfaceGetHeight(GILSurface surface)
//{
//  int32_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = (- s->mBitmapInfo.bmiHeader.biHeight);
//  }
//
//  return retVal;
//}
//
//uint8_t gilSurfaceGetBPP(GILSurface surface)
//{
//  uint8_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = gil_helper_getbpp(s->mFormat);
//  }
//
//  return retVal;
//}
//
//uint32_t gilSurfaceGetMemorySize(GILSurface surface)
//{
//  uint32_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = s->mSize;
//  }
//
//  return retVal;
//}
