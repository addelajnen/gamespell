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

#ifndef GAMESPELL_GRAPHICS_OPENGL_EXTENSIONS_HH
#define GAMESPELL_GRAPHICS_OPENGL_EXTENSIONS_HH

#include <windows.h>

#include <gl/gl.h>
#include <gl/glext.h>

#ifdef _WIN32
#include <gl/wgl.h>
#endif

namespace gs {
namespace graphics {
#ifdef _WIN32
extern PFNWGLCHOOSEPIXELFORMATARBPROC    GS_wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC GS_wglCreateContextAttribsARB;
#endif
extern PFNGLDEBUGMESSAGECALLBACKPROC     GS_glDebugMessageCallback;
extern PFNGLATTACHSHADERPROC             GS_glAttachShader;
extern PFNGLBINDBUFFERPROC               GS_glBindBuffer;
extern PFNGLBINDVERTEXARRAYPROC          GS_glBindVertexArray;
extern PFNGLBUFFERDATAPROC               GS_glBufferData;
extern PFNGLCOMPILESHADERPROC            GS_glCompileShader;
extern PFNGLCREATEPROGRAMPROC            GS_glCreateProgram;
extern PFNGLCREATESHADERPROC             GS_glCreateShader;
extern PFNGLDELETEBUFFERSPROC            GS_glDeleteBuffers;
extern PFNGLDELETEPROGRAMPROC            GS_glDeleteProgram;
extern PFNGLDELETESHADERPROC             GS_glDeleteShader;
extern PFNGLDELETEVERTEXARRAYSPROC       GS_glDeleteVertexArrays;
extern PFNGLDETACHSHADERPROC             GS_glDetachShader;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  GS_glEnableVertexAttribArray;
extern PFNGLGENBUFFERSPROC               GS_glGenBuffers;
extern PFNGLGENVERTEXARRAYSPROC          GS_glGenVertexArrays;
extern PFNGLGETATTRIBLOCATIONPROC        GS_glGetAttribLocation;
extern PFNGLGETPROGRAMINFOLOGPROC        GS_glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC             GS_glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC         GS_glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC              GS_glGetShaderiv;
extern PFNGLLINKPROGRAMPROC              GS_glLinkProgram;
extern PFNGLSHADERSOURCEPROC             GS_glShaderSource;
extern PFNGLUSEPROGRAMPROC               GS_glUseProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC      GS_glVertexAttribPointer;
extern PFNGLBINDATTRIBLOCATIONPROC       GS_glBindAttribLocation;
extern PFNGLGETUNIFORMLOCATIONPROC       GS_glGetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC         GS_glUniformMatrix4fv;
extern PFNGLACTIVETEXTUREPROC            GS_glActiveTexture;
extern PFNGLUNIFORM1IPROC                GS_glUniform1i;
extern PFNGLGENERATEMIPMAPPROC           GS_glGenerateMipmap;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC GS_glDisableVertexAttribArray;
extern PFNGLUNIFORM1FPROC                GS_glUniform1f;
extern PFNGLUNIFORM3FVPROC               GS_glUniform3fv;
extern PFNGLUNIFORM4FVPROC               GS_glUniform4fv;
} // namespace graphics
} // namespace gs

#endif // GAMESPELL_GRAPHICS_OPENGL_EXTENSIONS_HH
