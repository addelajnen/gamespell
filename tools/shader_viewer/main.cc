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

#include <atomic>
#include <iostream>
#include <stdexcept>
#include <thread>

#include <gs/os/window.hh>
#include <gs/os/window_event.hh>

#include <gs/graphics/render_context.hh>
#include <gs/graphics/shader.hh>
#include <gs/graphics/shader_program.hh>
#include <gs/graphics/vertex_attribute.hh>
#include <gs/graphics/vertex_buffer.hh>

int main(int argc, const char** argv) {
    try {
        std::cout << "shader viewer by addelajnen" << std::endl << std::endl;
        if (argc < 3) {
            std::cout << "usage: " << std::filesystem::path(argv[0]).filename()
                      << " <vertex_shader> <fragment_shader>" << std::endl;
            return EXIT_FAILURE;
        }

        std::filesystem::path vsPath = argv[1];
        std::filesystem::path fsPath = argv[2];

        gs::os::Window window;
        window.open(640, 480, "hot-reloading shader viewer by addelajnen");

        gs::graphics::RenderContext renderer(window.getHandle());

        gs::graphics::Shader vs;
        vs.load(vsPath, gs::graphics::Shader::Type::Vertex);

        gs::graphics::Shader fs;
        fs.load(fsPath, gs::graphics::Shader::Type::Fragment);

        gs::graphics::ShaderProgram program;
        program.load(vs, fs);

        float vertices[3][7] = {
            {-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f},
            { 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f},
            { 0.0f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f}
        };

        gs::graphics::VertexBuffer vb(
            vertices, 3, sizeof(float) * 7, gs::graphics::FloatXYZRGBA);

        gs::math::Matrix4x4 transform(1.0f,
                                      0.0f,
                                      0.0f,
                                      0.0f,
                                      0.0f,
                                      1.0f,
                                      0.0f,
                                      0.0f,
                                      0.0f,
                                      0.0f,
                                      1.0f,
                                      0.0f,
                                      0.0f,
                                      0.0f,
                                      0.0f,
                                      1.0f);

        std::atomic_bool quit   = false;
        std::atomic_bool reload = false;
        std::thread      t([&]() {
            std::filesystem::path watchPath((std::filesystem::current_path() /
                                             std::filesystem::absolute(vsPath))
                                                .remove_filename());

            std::wcout << L"now watching " << watchPath.c_str() << std::endl;

            HANDLE hwatcher = FindFirstChangeNotificationW(
                watchPath.c_str(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);
            if (!hwatcher || hwatcher == INVALID_HANDLE_VALUE) {
                throw std::runtime_error("failed to watch");
            }

            while (!quit) {
                auto status = WaitForSingleObject(hwatcher, 5000);
                if (status == WAIT_OBJECT_0) {
                    reload = true;
                    if (!FindNextChangeNotification(hwatcher)) {
                        throw std::runtime_error("watcher failed to restart");
                    }
                } else if (status != WAIT_TIMEOUT) {
                    throw std::runtime_error("watcher failed");
                }
            }

            std::cout << "closing watcher" << std::endl;

            FindCloseChangeNotification(hwatcher);
        });

        while (!window.isClosed()) {
            auto event = window.pollEvents();
            if (event) {
                if (event->type == gs::os::WindowEvent::Type::Closed) {
                    window.close();
                }
            }

            if (reload) {
                std::cout << "reloading shaders...";
                try {
                    vs.release();
                    fs.release();
                    program.release();

                    vs.load(vsPath, gs::graphics::Shader::Type::Vertex);
                    fs.load(fsPath, gs::graphics::Shader::Type::Fragment);
                    program.load(vs, fs);

                    std::cout << "ok" << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "failed" << std::endl;
                    std::cout << "error: " << e.what() << std::endl;
                }

                reload = false;
            } else {
                renderer.clear();
                program.use();
                program.setMatrix4("transform", transform.m);
                renderer.draw(vb, 0, 3, gs::graphics::Primitive::Triangles);
                renderer.swapBuffers();
            }
        }

        quit = true;

        t.join();
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
