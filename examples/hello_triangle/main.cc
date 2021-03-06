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

#include <gs/os/window.hh>
#include <gs/os/window_event.hh>
#include <gs/graphics/render_context.hh>
#include <gs/graphics/shader.hh>
#include <gs/graphics/shader_program.hh>
#include <gs/graphics/vertex_buffer.hh>

int main(int argc, char** argv) {
    try {
        gs::os::Window window;
        window.open(640, 480, "test");

        gs::graphics::RenderContext rc;
        rc.attach(window.getHandle());

        gs::graphics::Shader vs;
        vs.load("assets/shaders/vertex_shader.glsl",
                                gs::graphics::Shader::Type::Vertex);
        gs::graphics::Shader fs;
        fs.load("assets/shaders/fragment_shader.glsl",
                                gs::graphics::Shader::Type::Fragment);

        gs::graphics::ShaderProgram program;
        program.load(vs, fs);

        float vertices[3][7] = {
            { -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
            {  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
            {  0.0f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
        };
       
        gs::graphics::VertexBuffer vb;
        vb.assign(vertices, 3, sizeof(float) * 7, 0, {
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


        gs::math::Matrix4x4 transform = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };

        transform.translate(0.25f, 0.25f, 0.0f);

        float angle = 0.0f;
        while (!window.isClosed()) {
            auto before = std::chrono::high_resolution_clock::now();

            auto event = window.pollEvents();
            if (event) {
                if (event->type == gs::os::WindowEvent::Type::Closed) {
                    window.close();
                } else if (event->type == gs::os::WindowEvent::Type::Resized) {
                    rc.updateViewport(0, 0, event->data.resized.width, event->data.resized.height);
                }
            }
            rc.clear();
            program.use();
            program.setMatrix4("transform", transform.m);
            rc.draw(vb, 0, 3, gs::graphics::Primitive::Triangles);
            rc.swapBuffers();

            auto after = std::chrono::high_resolution_clock::now();            
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
            auto d = (ms * 0.001f).count();

            angle += d;

            transform.rotateZAxis(angle);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        system("PAUSE");
    }
    return 0;
}