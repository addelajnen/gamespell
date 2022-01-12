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

#include "shader_viewer.hh"

std::unique_ptr<gs::framework::Application>
gs::framework::Application::create() {
    return std::make_unique<ShaderViewer>();
}

ShaderViewer::ShaderViewer()
    : gs::framework::Application(640, 480, "ShaderViewer by addelajnen")
    , shouldReloadVertexShader(false)
    , shouldReloadFragmentShader(false) {
    renderContext.attach(getWindow().getHandle());
}

ShaderViewer::~ShaderViewer() {
}

void ShaderViewer::onStartup() {    
    const auto pathToShaders = std::filesystem::current_path() / "assets" /
                               "shaders";

    vertexShader.load(pathToShaders / "vertex_shader.glsl",
                      gs::graphics::Shader::Type::Vertex);
    vertexShader.load(pathToShaders / "vertex_shader.glsl",
                      gs::graphics::Shader::Type::Vertex);

    fragmentShader.load(pathToShaders / "fragment_shader.glsl",
                        gs::graphics::Shader::Type::Fragment);

    shaderProgram.load(vertexShader, fragmentShader);

    float vertices[3][7] = {
        { -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
        {  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
        {  0.0f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
    };

    vertexBuffer.assign(vertices, 3, sizeof(float) * 7, 0, {
        gs::graphics::VertexAttribute{
            .type = gs::graphics::VertexAttribute::Type::Float,
            .size = 3,
            .usage = gs::graphics::VertexAttribute::Usage::Position,
        },
        gs::graphics::VertexAttribute{
            .type = gs::graphics::VertexAttribute::Type::Float,
            .size = 4,
            .usage = gs::graphics::VertexAttribute::Usage::Color,
        }
    });

    transform = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    transform.translate(0.25f, 0.25f, 0.0f);

    watcher.watch(pathToShaders, [&](auto action, auto path) {
        if (path.string() == vertexShader.getPath()) {
            shouldReloadVertexShader = true;
        } else {
            shouldReloadFragmentShader = true;
        }
    });
}

void ShaderViewer::onUpdate() {
    if (shouldReloadVertexShader || shouldReloadFragmentShader) {
        if (shouldReloadVertexShader) {
            auto vsPath = vertexShader.getPath();
            vertexShader.release();
            vertexShader.load(vsPath, gs::graphics::Shader::Type::Vertex);
        }
        if (shouldReloadFragmentShader) {
            auto fsPath = fragmentShader.getPath();
            fragmentShader.release();
            fragmentShader.load(fsPath, gs::graphics::Shader::Type::Fragment);
        }

        shaderProgram.release();
        shaderProgram.load(vertexShader, fragmentShader);

        shouldReloadVertexShader = false;
        shouldReloadFragmentShader = false;
    }

    renderContext.clear();
    
    shaderProgram.use();
    shaderProgram.setMatrix4("transform", transform.m);

    renderContext.draw(vertexBuffer, 0, 3, gs::graphics::Primitive::Triangles);
    renderContext.swapBuffers();
}

void ShaderViewer::onWindowResized(gs::os::WindowEvent& event) {
    renderContext.updateViewport(0, 0, event.data.resized.width, event.data.resized.height);
}
