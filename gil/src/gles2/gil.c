/******************************************************************************
**
**   File:        gil.c
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

#include <gil.h>
#include <stdlib.h>
//GLSC2 only supports binary shaders, which is not suitable for testing on desktop systems
//#include <GLSC2/glsc2.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void dbg_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

#define DEBUG 1
#define LOG_VERB(x) do { if (DEBUG) dbg_printf x; } while (0)
#define LOG_WARN(x) do { if (DEBUG) dbg_printf x; } while (0)
#define LOG_ERR(x) do { if (DEBUG) dbg_printf x; } while (0)

// constants for attribute positions
const GLuint a_position = 0;
const GLuint a_texCoord = 1;

const char vColorShaderStr[] =
    "attribute vec4 a_position;                  \n"
    "uniform mat4 mvp_matrix;                    \n"
    "void main()                                 \n"
    "{                                           \n"
    "   gl_Position = mvp_matrix * a_position;   \n"
    "}                                           \n";

const char fColorShaderStr[] =
    "#ifdef GL_ES\n"
    "precision mediump float;                   \n"
    "#endif\n"
    "uniform vec4 color;                        \n"
    "void main()                                \n"
    "{                                          \n"
    "  gl_FragColor = color;                    \n"
    "}                                          \n";

const char vTexShaderStr[] =
    "attribute vec4 a_position;   \n"
    "attribute vec2 a_texCoord;   \n"
    "uniform mat4 mvp_matrix;     \n"
    "varying vec2 v_texCoord;     \n"
    "void main()                  \n"
    "{                            \n"
    "   gl_Position = mvp_matrix * a_position; \n"
    "   v_texCoord = a_texCoord;  \n"
    "}                            \n";

const char fTexShaderStr[] =
    "#ifdef GL_ES\n"
    "precision mediump float;                            \n"
    "#endif\n"
    "varying vec2 v_texCoord;                            \n"
    "uniform sampler2D s_texture;                        \n"
    "void main()                                         \n"
    "{                                                   \n"
    "  gl_FragColor = texture2D(s_texture, v_texCoord ); \n"
    "}                                                   \n";

typedef struct
{
    union
    {
        GLfloat m[4][4];
        GLfloat f[16];
    };
} ESMatrix;

typedef struct gil_display_t
{
    EGLDisplay egl;
    NativeDisplayType native;
} gil_display_t;

typedef struct gil_surface_t
{
    EGLSurface egl;
    int32_t width;
    int32_t height;
} gil_surface_t;

typedef struct gil_context_t
{
    EGLContext egl;
    GLuint colorShader;
    GLuint textureShader;
    // uniform positions
    GLint colorShader_color;
    GLint colorShader_mvpMatrix;
    GLint textureShader_texture;
    GLint textureShader_mvpMatrix;
    // color
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
    // model view matrix
    ESMatrix mvpMatrix;
} gil_context_t;

struct gil_texture_t
{
};

struct gil_config_t
{
};


static EGLConfig m_config = 0;
static gil_display_t m_display = {EGL_NO_DISPLAY, 0};
static gil_context_t m_context = { EGL_NO_CONTEXT, 0, 0};
static gil_surface_t m_window = { EGL_NO_SURFACE, 0, 0};

static void loadIdentity(ESMatrix* m)
{
    memset(m, 0, sizeof(ESMatrix));
    m->m[0][0] = 1.0f;
    m->m[1][1] = 1.0f;
    m->m[2][2] = 1.0f;
    m->m[3][3] = 1.0f;
}

static void loadOrtho(ESMatrix* m, float left, float right, float bottom, float top, float nearZ, float farZ)
{
    loadIdentity(m);
    const float deltaX = right - left;
    const float deltaY = top - bottom;
    const float deltaZ = farZ - nearZ;
    if(deltaX != 0.0f && deltaY != 0.0f && deltaZ != 0.0f)
    {
        m->m[0][0] = 2.0f / deltaX;
        m->m[3][0] = -(right + left) / deltaX;
        m->m[1][1] = 2.0f / deltaY;
        m->m[3][1] = -(top + bottom) / deltaY;
        m->m[2][2] = -2.0f / deltaZ;
        m->m[3][2] = -(nearZ + farZ) / deltaZ;
    }
}

static NativeDisplayType getNativeDisplay()
{
    NativeDisplayType dsp = XOpenDisplay(NULL);
    if(!dsp)
    {
        fprintf(stderr, "Could not connect to X server\n");
    }
    return dsp;
}

static NativeWindowType getNativeWindow(NativeDisplayType dsp, int32_t width, int32_t height)
{
    const int scrnum = DefaultScreen(dsp);
    Window root = RootWindow(dsp, scrnum);
    XVisualInfo *visInfo, visTemplate;
    int num_visuals;
    XSetWindowAttributes attr;

    /* The X window visual must match the EGL config */
    EGLint format;
    eglGetConfigAttrib(m_display.egl, m_config, EGL_NATIVE_VISUAL_ID, &format);
    visTemplate.visualid = format;
    visInfo = XGetVisualInfo(dsp, VisualIDMask, &visTemplate, &num_visuals);
    if (!visInfo)
    {
        LOG_ERR(("AppWindowEGL_X11::AppWindowEGL_X11, couldn't get X visual"));
        return 0;
    }

    /* window attributes */
    attr.background_pixel = 0;
    attr.border_pixel = 0;
    attr.colormap = XCreateColormap( dsp, root, visInfo->visual, AllocNone);
    attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | PointerMotionHintMask;
    unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    NativeWindowType wnd = XCreateWindow( dsp, root, 0, 0, width, height, 0, visInfo->depth,
        InputOutput, visInfo->visual, mask, &attr );

    /* set hints and properties */
    {
        XSizeHints sizehints;
        sizehints.x = 0;
        sizehints.y = 0;
        sizehints.width  = width;
        sizehints.height = height;
        sizehints.flags = USSize | USPosition;

        XSetNormalHints(dsp, wnd, &sizehints);

        XSetStandardProperties(dsp, wnd, "LSR Engine", "LSR Engine",
            None, (char **)NULL, 0, &sizehints);
    }
    XFree(visInfo);
    XMapWindow(dsp, wnd);
    return wnd;
}

static GLuint checkCompileStatus(GLuint shader)
{
    GLint compiled;
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if ( infoLen > 1 )
        {
            char infoLog[256];
            glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            LOG_ERR(("Error compiling shader:\n%s\n", infoLog));
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint compileShader( GLuint shader )
{
    glCompileShader(shader);
    return checkCompileStatus(shader);
}

static GLuint loadProgramSource(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
    GLuint vertexShader;
    GLuint fragmentShader;

    // Create the shader object
    vertexShader = glCreateShader ( GL_VERTEX_SHADER );
    if (vertexShader == 0)
    {
        return 0;
    }

    fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER );
    if (fragmentShader == 0)
    {
        glDeleteShader( vertexShader );
        return 0;
    }

    // Load the shader source
    glShaderSource ( vertexShader, 1, &vertexShaderSrc, NULL );
    glShaderSource ( fragmentShader, 1, &fragmentShaderSrc, NULL );

    // Compile the vertex/fragment shaders
    vertexShader = compileShader ( vertexShader );
    if ( vertexShader == 0 )
        return 0;

    fragmentShader = compileShader ( fragmentShader );
    if ( fragmentShader == 0 )
    {
        glDeleteShader( vertexShader );
        return 0;
    }

    GLuint programObject;
    GLint linked;

    // Create the program object
    programObject = glCreateProgram ( );

    if (programObject == 0)
        return 0;

    glAttachShader ( programObject, vertexShader );
    glAttachShader ( programObject, fragmentShader );

    // Link the program
    glLinkProgram ( programObject );

    // Check the link status
    glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

    if ( !linked )
    {
        GLint infoLen = 0;
        glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
        if (infoLen > 1)
        {
            char infoLog[256];
            glGetProgramInfoLog(programObject, sizeof(infoLog), NULL, infoLog );
            LOG_ERR(("Error linking program:\n%s\n", infoLog));
        }
        glDeleteProgram(programObject);
        return 0;
    }

    // Free up no longer needed shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return programObject;
}

void gilInit(GILConfig config)
{
    // EGLDisplay
    m_display.native = getNativeDisplay();
    m_display.egl = eglGetDisplay(m_display.native);
    if(m_display.egl == EGL_NO_DISPLAY)
    {
        LOG_ERR(("EGL_NO_DISPLAY"));
    }
    EGLint iMajorVersion, iMinorVersion;
    if (!eglInitialize(m_display.egl, &iMajorVersion, &iMinorVersion))
    {
        LOG_ERR(("eglInitialize failed"));
        m_display.egl = EGL_NO_DISPLAY;
    }
    LOG_VERB(("EGL_VERSION:%s", eglQueryString(m_display.egl, EGL_VERSION)));
    LOG_VERB(("EGL_VENDOR:%s", eglQueryString(m_display.egl, EGL_VENDOR)));
    LOG_VERB(("EGL_CLIENT_APIS:%s", eglQueryString(m_display.egl, EGL_CLIENT_APIS)));
    LOG_VERB(("EGL_EXTENSIONS:%s", eglQueryString(m_display.egl, EGL_EXTENSIONS)));

    eglBindAPI(EGL_OPENGL_ES_API);

    // EGLConfig
    EGLint conflist[] =
    {
        EGL_CONFIG_CAVEAT, EGL_NONE,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, EGL_DONT_CARE,
        EGL_DEPTH_SIZE, EGL_DONT_CARE,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SAMPLE_BUFFERS, 0,
        EGL_SAMPLES, 0,
        EGL_LEVEL, 0,
        EGL_NONE
    };

    EGLint iConfigs;
    EGLBoolean ecc = eglChooseConfig(m_display.egl, conflist, &m_config, 1, &iConfigs);
    if ((!ecc) || (iConfigs != 1))
    {
        LOG_ERR(("OpenGLWindowES::Initialize, Failed to choose a EGL config."));
    }
}

GILSurface gilCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h)
{
    NativeWindowType wnd = getNativeWindow(m_display.native, w, h);
    struct
    {
        EGLint render_buffer[2];
        EGLint none;
    } egl_surf_attr = {{ EGL_RENDER_BUFFER, EGL_BACK_BUFFER },EGL_NONE }; //EGL_BACK_BUFFER should be default anyway

    m_window.egl = eglCreateWindowSurface(m_display.egl, m_config, wnd, (EGLint*)&egl_surf_attr);
    m_window.width = w;
    m_window.height = h;

    if(m_window.egl == EGL_NO_SURFACE)
    {
        LOG_ERR(("AppWindowEGL::CreateWindowSurface, (m_windowSurface == EGL_NO_SURFACE) %x", eglGetError()));
    }
    return &m_window;
}

// TODO: if multiple configs should be supported, we need to add a configuration parameter for gilCreateContext
GILContext gilCreateContext(void)
{
    const EGLint contextAttribList[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    m_context.egl = eglCreateContext(m_display.egl, m_config, EGL_NO_CONTEXT, contextAttribList);

    if(m_context.egl == EGL_NO_CONTEXT)
    {
        LOG_ERR(("gilCreateContext failed"));
    }

    // make context current
    if(!eglMakeCurrent(m_display.egl, EGL_NO_SURFACE, EGL_NO_SURFACE, m_context.egl))
    {
        LOG_ERR(("eglMakeCurrent failed"));
    }

    // all subsequent gl commands need a "current" context
    LOG_VERB(("GL_VENDOR:%s", glGetString(GL_VENDOR)));
    LOG_VERB(("GL_RENDERER:%s", glGetString(GL_RENDERER)));
    LOG_VERB(("GL_VERSION:%s", glGetString(GL_VERSION)));
    LOG_VERB(("GL_EXTENSIONS:%s", glGetString(GL_EXTENSIONS)));

    m_context.colorShader = loadProgramSource(vColorShaderStr, fColorShaderStr);
    m_context.textureShader = loadProgramSource(vTexShaderStr, fTexShaderStr);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glBindAttribLocation(m_context.colorShader, a_position, "a_position");
    glBindAttribLocation(m_context.textureShader, a_position, "a_position");
    glBindAttribLocation(m_context.textureShader, a_texCoord, "a_texCoord");
    m_context.colorShader_color = glGetUniformLocation(m_context.colorShader, "color");
    m_context.colorShader_mvpMatrix = glGetUniformLocation(m_context.colorShader, "mvp_matrix");
    m_context.textureShader_texture = glGetUniformLocation(m_context.textureShader, "s_texture");
    m_context.textureShader_mvpMatrix = glGetUniformLocation(m_context.textureShader, "mvp_matrix");

    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        LOG_ERR(("gilCreateContext(): GlError detected, err:%x", err));
    }

    return &m_context;
}

GILBoolean gilSetSurface(GILContext context, GILSurface surface)
{
    GILBoolean ret = GIL_FALSE;
    if (context == NULL || surface == NULL)
    {
        // special error code?
    }
    else
    {
        ret =  eglMakeCurrent(m_display.egl, surface->egl, surface->egl, context->egl);
        glViewport(0, 0, surface->width, surface->height);
        loadOrtho(&context->mvpMatrix, 0.0f, surface->width, surface->height, 0.0f, 500.0f, -500.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    return ret;
}

GILBoolean gilSetColor(GILContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    context->red = red / 255.f;
    context->green = green / 255.f;
    context->blue = blue / 255.f;
    context->alpha = alpha / 255.f;
    // used for next command
    return GIL_TRUE;
}

GILTexture gilCreateTexture(GILContext context)
{
    GLuint texture;
    glGenTextures(1, &texture);
    return (GILTexture)(uintptr_t)texture;
}

GILBoolean gilLoadTexture(GILTexture t, uint32_t width, uint32_t height, GILFormat format, GILBoolean copy, const void* data)
{
    GLint glType = GL_UNSIGNED_BYTE;
    GLint glFormat = GL_RGBA;
    // TODO: check format and return false if not supported
    glBindTexture(GL_TEXTURE_2D, (uintptr_t) t);
    glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glType, data);
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    return GIL_TRUE;
}

void gilBindTexture(GILContext context, GILTexture t)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, (uintptr_t) t);
}

void gilClear(GILContext ctx)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void gilDrawArea(GILContext ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    GLfloat arrayBuffer[] = {x1/16.0f, y1/16.0f, x2/16.0f, y1/16.0f, x1/16.0f, y2/16.0f, x2/16.0f, y2/16.0f };
    glUseProgram(ctx->colorShader);
    glEnableVertexAttribArray(a_position);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, arrayBuffer);
    glUniform4f(ctx->colorShader_color, ctx->red, ctx->green, ctx->blue, ctx->alpha);
    glUniformMatrix4fv(ctx->colorShader_mvpMatrix, 1, GL_FALSE, ctx->mvpMatrix.f);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void gilDrawQuad(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    GLfloat arrayBuffer[] = {x1/16.0f, y1/16.0f, x2/16.0f, y1/16.0f, x1/16.0f, y2/16.0f, x2/16.0f, y2/16.0f };
    GLfloat textureBuffer[] = {0,0, 1,0, 0,1, 1, 1};
    glUseProgram(ctx->textureShader);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glUniform1i(ctx->textureShader_texture, 0);
    glEnableVertexAttribArray(a_position);
    glEnableVertexAttribArray(a_texCoord);
    glVertexAttribPointer(a_position, 2, GL_FLOAT, GL_FALSE, 0, arrayBuffer);
    glVertexAttribPointer(a_texCoord, 2, GL_FLOAT, GL_FALSE, 0, textureBuffer);
    glUniformMatrix4fv(ctx->textureShader_mvpMatrix, 1, GL_FALSE, ctx->mvpMatrix.f);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

GILBoolean gilVerify(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    return GIL_FALSE;
}

GILBoolean gilSwapBuffers(GILSurface surface)
{
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        LOG_ERR(("gilSwapBuffers(): GlError detected, err:%x", err));
    }
    return eglSwapBuffers(m_display.egl, surface->egl);
}

GILError gilGetError(GILContext context)
{
    GILError ret = GIL_NO_ERROR;
    EGLint eglErr = eglGetError();
    if (EGL_SUCCESS != eglErr)
    {
        ret = eglErr;
    }
    if (GIL_NO_ERROR == ret)
    {
        ret = glGetError(); // GIL_NO_ERROR == GL_NO_ERROR
    }
    return ret;
}

GILBoolean gilHandleWindowEvents(GILContext context)
{
    return GIL_FALSE;
}
