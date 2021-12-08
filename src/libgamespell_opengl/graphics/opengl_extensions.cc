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

#include "opengl_extensions.hh"

namespace gs {
namespace graphics {
#ifdef _WIN32
PFNWGLGETPROCADDRESSPROC          GS_wglGetProcAddress          = nullptr;
PFNWGLCHOOSEPIXELFORMATARBPROC    GS_wglChoosePixelFormatARB    = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC GS_wglCreateContextAttribsARB = nullptr;
#endif
PFNGLDEBUGMESSAGECALLBACKPROC     GS_glDebugMessageCallback     = nullptr;
PFNGLATTACHSHADERPROC             GS_glAttachShader             = nullptr;
PFNGLBINDBUFFERPROC               GS_glBindBuffer               = nullptr;
PFNGLBINDVERTEXARRAYPROC          GS_glBindVertexArray          = nullptr;
PFNGLBUFFERDATAPROC               GS_glBufferData               = nullptr;
PFNGLCOMPILESHADERPROC            GS_glCompileShader            = nullptr;
PFNGLCREATEPROGRAMPROC            GS_glCreateProgram            = nullptr;
PFNGLCREATESHADERPROC             GS_glCreateShader             = nullptr;
PFNGLDELETEBUFFERSPROC            GS_glDeleteBuffers            = nullptr;
PFNGLDELETEPROGRAMPROC            GS_glDeleteProgram            = nullptr;
PFNGLDELETESHADERPROC             GS_glDeleteShader             = nullptr;
PFNGLDELETEVERTEXARRAYSPROC       GS_glDeleteVertexArrays       = nullptr;
PFNGLDETACHSHADERPROC             GS_glDetachShader             = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC  GS_glEnableVertexAttribArray  = nullptr;
PFNGLGENBUFFERSPROC               GS_glGenBuffers               = nullptr;
PFNGLGENVERTEXARRAYSPROC          GS_glGenVertexArrays          = nullptr;
PFNGLGETATTRIBLOCATIONPROC        GS_glGetAttribLocation        = nullptr;
PFNGLGETPROGRAMINFOLOGPROC        GS_glGetProgramInfoLog        = nullptr;
PFNGLGETPROGRAMIVPROC             GS_glGetProgramiv             = nullptr;
PFNGLGETSHADERINFOLOGPROC         GS_glGetShaderInfoLog         = nullptr;
PFNGLGETSHADERIVPROC              GS_glGetShaderiv              = nullptr;
PFNGLLINKPROGRAMPROC              GS_glLinkProgram              = nullptr;
PFNGLSHADERSOURCEPROC             GS_glShaderSource             = nullptr;
PFNGLUSEPROGRAMPROC               GS_glUseProgram               = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC      GS_glVertexAttribPointer      = nullptr;
PFNGLBINDATTRIBLOCATIONPROC       GS_glBindAttribLocation       = nullptr;
PFNGLGETUNIFORMLOCATIONPROC       GS_glGetUniformLocation       = nullptr;
PFNGLUNIFORMMATRIX4FVPROC         GS_glUniformMatrix4fv         = nullptr;
PFNGLACTIVETEXTUREPROC            GS_glActiveTexture            = nullptr;
PFNGLUNIFORM1IPROC                GS_glUniform1i                = nullptr;
PFNGLGENERATEMIPMAPPROC           GS_glGenerateMipmap           = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC GS_glDisableVertexAttribArray = nullptr;
PFNGLUNIFORM1FPROC                GS_glUniform1f                = nullptr;
PFNGLUNIFORM3FVPROC               GS_glUniform3fv               = nullptr;
PFNGLUNIFORM4FVPROC               GS_glUniform4fv               = nullptr;
} // namespace graphics
} // namespace gs
