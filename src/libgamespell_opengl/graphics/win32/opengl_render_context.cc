// Copyright 2021 addelajnen@outlook.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <iostream>
#include <stdexcept>

#include <windows.h>

#include <gl/gl.h>
#include <gl/wgl.h>

#include <gs/graphics/render_context.hh>

#include "opengl_extensions.hh"

namespace gs {
namespace graphics {
struct RenderContext::Implementation {
    Implementation()
        : wcDummy({0})
        , shouldUnregisterDummyWindowClass(false)
        , hwndDummy(nullptr)
        , hdcDummy(nullptr)
        , hrcDummy(nullptr)
        , hdc(nullptr)
        , hrc(nullptr) {}

    // Dummy window implementation details
    WNDCLASS wcDummy;
    bool     shouldUnregisterDummyWindowClass;
    HWND     hwndDummy;
    HDC      hdcDummy;
    HGLRC    hrcDummy;

    // Window implementation details
    HDC   hdc;
    HGLRC hrc;

    static void debugProc(GLenum        source,
                          GLenum        type,
                          GLuint        id,
                          GLenum        severity,
                          GLsizei       length,
                          const GLchar* message,
                          const void*   userParam) {
        std::cerr << message << std::endl;
    }
};

RenderContext::RenderContext(gs::os::WindowHandle hwnd)
    : implementation(std::make_unique<RenderContext::Implementation>())
    , hwnd(hwnd) {
    HINSTANCE hinstance = GetModuleHandle(nullptr);
    if (!hinstance) {
        throw std::runtime_error("failed to get application module handle");
    }

    implementation->wcDummy.hbrBackground = reinterpret_cast<HBRUSH>(
        COLOR_BACKGROUND);
    implementation->wcDummy.hInstance     = hinstance;
    implementation->wcDummy.lpfnWndProc   = DefWindowProc;
    implementation->wcDummy.lpszClassName = TEXT(
        "gamespelldummyopenglwindowclass");
    implementation->wcDummy.style = CS_OWNDC;

    if (!RegisterClass(&implementation->wcDummy)) {
        throw std::runtime_error("failed to register dummy window class");
    }
    implementation->shouldUnregisterDummyWindowClass = true;

    implementation->hwndDummy = CreateWindow(
        implementation->wcDummy.lpszClassName,
        TEXT(""),
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        640,
        480,
        nullptr,
        nullptr,
        implementation->wcDummy.hInstance,
        nullptr);
    if (!implementation->hwndDummy) {
        throw std::runtime_error("failed to create dummy window");
    }

    implementation->hdcDummy = GetDC(implementation->hwndDummy);
    if (!implementation->hdcDummy) {
        throw std::runtime_error("failed to device context of dummy window");
    }

    PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),
                                 1,
                                 PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                                     PFD_DOUBLEBUFFER,
                                 PFD_TYPE_RGBA,
                                 32,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 24,
                                 8,
                                 0,
                                 PFD_MAIN_PLANE,
                                 0,
                                 0,
                                 0,
                                 0};

    int dummyFormat = ChoosePixelFormat(implementation->hdcDummy, &pfd);
    if (!SetPixelFormat(implementation->hdcDummy, dummyFormat, &pfd)) {
        throw std::runtime_error("failed to set dummy pixel format");
    }

    implementation->hrcDummy = wglCreateContext(implementation->hdcDummy);
    if (!implementation->hrcDummy) {
        throw std::runtime_error("failed to create dummy render context");
    }
    if (!wglMakeCurrent(implementation->hdcDummy, implementation->hrcDummy)) {
        throw std::runtime_error("failed to activate dummy render context");
    }

    GS_wglChoosePixelFormatARB =
        reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(
            wglGetProcAddress("wglChoosePixelFormatARB"));
    if (!GS_wglChoosePixelFormatARB) {
        throw std::runtime_error(
            "failed to load opengl function \"wglChoosePixelFormatARB\"");
    }
    GS_wglCreateContextAttribsARB =
        reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
            wglGetProcAddress("wglCreateContextAttribsARB"));
    if (!GS_wglCreateContextAttribsARB) {
        throw std::runtime_error(
            "failed to load opengl function \"wglChoosePixelFormatARB\"");
    }
    GS_glDebugMessageCallback = reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKPROC>(
        wglGetProcAddress("glDebugMessageCallback"));
    if (!GS_glDebugMessageCallback) {
        throw std::runtime_error(
            "failed to load opengl function \"glDebugMessageCallback\"");
    }
    GS_glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(
        wglGetProcAddress("glAttachShader"));
    if (!GS_glAttachShader) {
        throw std::runtime_error(
            "failed to load opengl function \"glAttachShader\"");
    }
    GS_glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(
        wglGetProcAddress("glBindBuffer"));
    if (!GS_glBindBuffer) {
        throw std::runtime_error(
            "failed to load opengl function \"glBindBuffer\"");
    }
    GS_glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(
        wglGetProcAddress("glBindVertexArray"));
    if (!GS_glBindVertexArray) {
        throw std::runtime_error(
            "failed to load opengl function \"glBindVertexArray\"");
    }
    GS_glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(
        wglGetProcAddress("glBufferData"));
    if (!GS_glBufferData) {
        throw std::runtime_error(
            "failed to load opengl function \"glBufferData\"");
    }
    GS_glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(
        wglGetProcAddress("glCompileShader"));
    if (!GS_glCompileShader) {
        throw std::runtime_error(
            "failed to load opengl function \"glCompileShader\"");
    }
    GS_glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(
        wglGetProcAddress("glCreateProgram"));
    if (!GS_glCreateProgram) {
        throw std::runtime_error(
            "failed to load opengl function \"glCreateProgram\"");
    }
    GS_glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(
        wglGetProcAddress("glCreateShader"));
    if (!GS_glCreateShader) {
        throw std::runtime_error(
            "failed to load opengl function \"glCreateShader\"");
    }
    GS_glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(
        wglGetProcAddress("glDeleteBuffers"));
    if (!GS_glDeleteBuffers) {
        throw std::runtime_error(
            "failed to load opengl function \"glDeleteBuffers\"");
    }
    GS_glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(
        wglGetProcAddress("glDeleteProgram"));
    if (!GS_glDeleteProgram) {
        throw std::runtime_error(
            "failed to load opengl function \"glDeleteProgram\"");
    }
    GS_glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(
        wglGetProcAddress("glDeleteShader"));
    if (!GS_glDeleteShader) {
        throw std::runtime_error(
            "failed to load opengl function \"glDeleteShader\"");
    }
    GS_glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(
        wglGetProcAddress("glDeleteVertexArrays"));
    if (!GS_glDeleteVertexArrays) {
        throw std::runtime_error(
            "failed to load opengl function \"glDeleteVertexArrays\"");
    }
    GS_glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(
        wglGetProcAddress("glDetachShader"));
    if (!GS_glDetachShader) {
        throw std::runtime_error(
            "failed to load opengl function \"glDetachShader\"");
    }
    GS_glEnableVertexAttribArray =
        reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(
            wglGetProcAddress("glEnableVertexAttribArray"));
    if (!GS_glEnableVertexAttribArray) {
        throw std::runtime_error(
            "failed to load opengl function \"glEnableVertexAttribArray\"");
    }
    GS_glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(
        wglGetProcAddress("glGenBuffers"));
    if (!GS_glGenBuffers) {
        throw std::runtime_error(
            "failed to load opengl function \"glGenBuffers\"");
    }
    GS_glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(
        wglGetProcAddress("glGenVertexArrays"));
    if (!GS_glGenVertexArrays) {
        throw std::runtime_error(
            "failed to load opengl function \"glGenVertexArrays\"");
    }
    GS_glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(
        wglGetProcAddress("glGetAttribLocation"));
    if (!GS_glGetAttribLocation) {
        throw std::runtime_error(
            "failed to load opengl function \"glGetAttribLocation\"");
    }
    GS_glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(
        wglGetProcAddress("glGetProgramInfoLog"));
    if (!GS_glGetProgramInfoLog) {
        throw std::runtime_error(
            "failed to load opengl function \"glGetProgramInfoLog\"");
    }
    GS_glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(
        wglGetProcAddress("glGetProgramiv"));
    if (!GS_glGetProgramiv) {
        throw std::runtime_error(
            "failed to load opengl function \"glGetProgramiv\"");
    }
    GS_glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(
        wglGetProcAddress("glGetShaderInfoLog"));
    if (!GS_glGetShaderInfoLog) {
        throw std::runtime_error(
            "failed to load opengl function \"glGetShaderInfoLog\"");
    }
    GS_glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(
        wglGetProcAddress("glGetShaderiv"));
    if (!GS_glGetShaderiv) {
        throw std::runtime_error(
            "failed to load opengl function \"glGetShaderiv\"");
    }
    GS_glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(
        wglGetProcAddress("glLinkProgram"));
    if (!GS_glLinkProgram) {
        throw std::runtime_error(
            "failed to load opengl function \"glLinkProgram\"");
    }
    GS_glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(
        wglGetProcAddress("glShaderSource"));
    if (!GS_glShaderSource) {
        throw std::runtime_error(
            "failed to load opengl function \"glShaderSource\"");
    }
    GS_glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(
        wglGetProcAddress("glUseProgram"));
    if (!GS_glUseProgram) {
        throw std::runtime_error(
            "failed to load opengl function \"glUseProgram\"");
    }
    GS_glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(
        wglGetProcAddress("glVertexAttribPointer"));
    if (!GS_glVertexAttribPointer) {
        throw std::runtime_error(
            "failed to load opengl function \"glVertexAttribPointer\"");
    }
    GS_glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(
        wglGetProcAddress("glBindAttribLocation"));
    if (!GS_glBindAttribLocation) {
        throw std::runtime_error(
            "failed to load opengl function \"glBindAttribLocation\"");
    }
    GS_glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(
        wglGetProcAddress("glGetUniformLocation"));
    if (!GS_glGetUniformLocation) {
        throw std::runtime_error(
            "failed to load opengl function \"glGetUniformLocation\"");
    }
    GS_glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(
        wglGetProcAddress("glUniformMatrix4fv"));
    if (!GS_glUniformMatrix4fv) {
        throw std::runtime_error(
            "failed to load opengl function \"glUniformMatrix4fv\"");
    }
    GS_glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(
        wglGetProcAddress("glActiveTexture"));
    if (!GS_glActiveTexture) {
        throw std::runtime_error(
            "failed to load opengl function \"glActiveTexture\"");
    }
    GS_glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(
        wglGetProcAddress("glUniform1i"));
    if (!GS_glUniform1i) {
        throw std::runtime_error(
            "failed to load opengl function \"glUniform1i\"");
    }
    GS_glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(
        wglGetProcAddress("glGenerateMipmap"));
    if (!GS_glGenerateMipmap) {
        throw std::runtime_error(
            "failed to load opengl function \"glGenerateMipmap\"");
    }
    GS_glDisableVertexAttribArray =
        reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(
            wglGetProcAddress("glDisableVertexAttribArray"));
    if (!GS_glDisableVertexAttribArray) {
        throw std::runtime_error(
            "failed to load opengl function \"glDisableVertexAttribArray\"");
    }
    GS_glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>(
        wglGetProcAddress("glUniform1f"));
    if (!GS_glUniform1f) {
        throw std::runtime_error(
            "failed to load opengl function \"glUniform1f\"");
    }
    GS_glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(
        wglGetProcAddress("glUniform3fv"));
    if (!GS_glUniform3fv) {
        throw std::runtime_error(
            "failed to load opengl function \"glUniform3fv\"");
    }
    GS_glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>(
        wglGetProcAddress("glUniform4fv"));
    if (!GS_glUniform4fv) {
        throw std::runtime_error(
            "failed to load opengl function \"glUniform4fv\"");
    }

    wglDeleteContext(implementation->hrcDummy);
    implementation->hrcDummy = nullptr;

    ReleaseDC(implementation->hwndDummy, implementation->hdcDummy);
    implementation->hdcDummy = nullptr;

    DestroyWindow(implementation->hwndDummy);
    implementation->hwndDummy = nullptr;

    UnregisterClass(implementation->wcDummy.lpszClassName,
                    implementation->wcDummy.hInstance);
    implementation->shouldUnregisterDummyWindowClass = false;

    glEnable(GL_DEBUG_OUTPUT);
    GS_glDebugMessageCallback(Implementation::debugProc, nullptr);

    implementation->hdc = GetDC(hwnd);
    if (!implementation->hdc) {
        throw std::runtime_error("failed to get device context of main window");
    }

    int format;
    int formatAttributes[] = {WGL_DRAW_TO_WINDOW_ARB,
                              GL_TRUE,
                              WGL_SUPPORT_OPENGL_ARB,
                              GL_TRUE,
                              WGL_DOUBLE_BUFFER_ARB,
                              GL_TRUE,
                              WGL_ACCELERATION_ARB,
                              WGL_FULL_ACCELERATION_ARB,
                              WGL_PIXEL_TYPE_ARB,
                              WGL_TYPE_RGBA_ARB,
                              WGL_COLOR_BITS_ARB,
                              32,
                              WGL_DEPTH_BITS_ARB,
                              24,
                              WGL_STENCIL_BITS_ARB,
                              8,
                              0};

    UINT formatCount = 0;
    GS_wglChoosePixelFormatARB(
        implementation->hdc, formatAttributes, 0, 1, &format, &formatCount);
    if (!formatCount) {
        throw std::runtime_error("failed to select opengl3.3+ pixel format");
    }

    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    DescribePixelFormat(implementation->hdc, format, sizeof(pfd), &pfd);
    if (!SetPixelFormat(implementation->hdc, format, &pfd)) {
        throw std::runtime_error("failed to set opengl3.3+ pixel format");
    }

    int gl33Attributes[] = {WGL_CONTEXT_MAJOR_VERSION_ARB,
                            3,
                            WGL_CONTEXT_MINOR_VERSION_ARB,
                            3,
                            WGL_CONTEXT_PROFILE_MASK_ARB,
                            WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                            0};

    implementation->hrc = GS_wglCreateContextAttribsARB(
        implementation->hdc, 0, gl33Attributes);
    if (!implementation->hrc) {
        throw std::runtime_error("failed to create opengl3.3+ render context");
    }

    if (!wglMakeCurrent(implementation->hdc, implementation->hrc)) {
        throw std::runtime_error(
            "failed to activate opengl3.3+ render context");
    }
}

RenderContext::~RenderContext() {
    if (implementation->hrcDummy) {
        wglDeleteContext(implementation->hrcDummy);
        implementation->hrcDummy = nullptr;
    }

    if (implementation->hwndDummy) {
        if (implementation->hdcDummy) {
            ReleaseDC(implementation->hwndDummy, implementation->hdcDummy);
        }
        DestroyWindow(implementation->hwndDummy);
    }
    implementation->hdcDummy  = nullptr;
    implementation->hwndDummy = nullptr;

    if (implementation->shouldUnregisterDummyWindowClass) {
        UnregisterClass(implementation->wcDummy.lpszClassName,
                        implementation->wcDummy.hInstance);
    }

    if (implementation->hrc) {
        wglDeleteContext(implementation->hrc);
    }

    if (hwnd) {
        if (implementation->hdc) {
            ReleaseDC(hwnd, implementation->hdc);
        }
    }

    implementation->hdc = nullptr;
}

void RenderContext::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderContext::draw(const VertexBuffer& buffer,
                         unsigned int        start,
                         unsigned int        end,
                         Primitive           primitive) {
    buffer.use();

    switch (primitive) {
    case Primitive::Points:
        glDrawArrays(GL_POINTS, start, end);
        break;
    case Primitive::LineStrip:
        glDrawArrays(GL_LINE_STRIP, start, end);
        break;
    case Primitive::LineLoop:
        glDrawArrays(GL_LINE_LOOP, start, end);
        break;
    case Primitive::Lines:
        glDrawArrays(GL_LINES, start, end);
        break;
    case Primitive::TriangleStrip:
        glDrawArrays(GL_TRIANGLE_STRIP, start, end);
        break;
    case Primitive::TriangleFan:
        glDrawArrays(GL_TRIANGLE_FAN, start, end);
        break;
    case Primitive::Triangles:
        glDrawArrays(GL_TRIANGLES, start, end);
        break;
    }
}

void RenderContext::swapBuffers() {
    if (implementation->hdc) {
        SwapBuffers(implementation->hdc);
    }
}

void RenderContext::updateViewport(unsigned int x,
                                   unsigned int y,
                                   unsigned int width,
                                   unsigned int height) {
    glViewport(x, y, width, height);
    glOrtho(0, width, height, 0, -1.0f, 1.0f);
}
} // namespace graphics
} // namespace gs
