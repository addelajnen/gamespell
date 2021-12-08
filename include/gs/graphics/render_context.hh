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

#ifndef GAMESPELL_GRAPHICS_RENDER_CONTEXT_HH
#define GAMESPELL_GRAPHICS_RENDER_CONTEXT_HH

#include <memory>

#include <gs/graphics/primitive.hh>
#include <gs/graphics/vertex_buffer.hh>
#include <gs/math/matrix4x4.hh>
#include <gs/os/window_handle.hh>

namespace gs {
namespace graphics {
class RenderContext {
public:
    explicit RenderContext(gs::os::WindowHandle hwnd);
    ~RenderContext();

    void clear();
    void draw(const VertexBuffer& buffer,
              unsigned int        start,
              unsigned int        end,
              Primitive           primitive);
    void swapBuffers();

    void updateViewport(unsigned int x,
                        unsigned int y,
                        unsigned int width,
                        unsigned int height);

private:
    struct Implementation;

    std::unique_ptr<Implementation> implementation;
    gs::os::WindowHandle            hwnd;
};
} // namespace graphics
} // namespace gs

#endif // GAMESPELL_GRAPHICS_RENDER_CONTEXT_HH
