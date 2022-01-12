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

#ifndef GAMESPELL_TOOL_SHADER_VIEWER_HH
#define GAMESPELL_TOOL_SHADER_VIEWER_HH

#include <atomic>

#include <gs/framework/application.hh>

#include <gs/graphics/render_context.hh>
#include <gs/graphics/shader.hh>
#include <gs/graphics/shader_program.hh>
#include <gs/graphics/vertex_buffer.hh>

#include <gs/math/matrix4x4.hh>

#include <gs/os/file_watcher.hh>

class ShaderViewer : public gs::framework::Application {
public:
    ShaderViewer();
    ~ShaderViewer();

    virtual void onStartup() final;
    virtual void onUpdate() final;
    virtual void onWindowResized(gs::os::WindowEvent& event) final;

private:
    gs::graphics::Shader        vertexShader;
    gs::graphics::Shader        fragmentShader;
    gs::graphics::ShaderProgram shaderProgram;
    gs::graphics::VertexBuffer  vertexBuffer;
    gs::math::Matrix4x4         transform;
    gs::graphics::RenderContext renderContext;
    gs::os::FileWatcher         watcher;
    std::atomic_bool            shouldReloadVertexShader;
    std::atomic_bool            shouldReloadFragmentShader;
};

#endif // GAMESPELL_TOOL_SHADER_VIEWER_HH
