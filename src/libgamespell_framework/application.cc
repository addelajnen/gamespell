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

#include <stdexcept>

#include <gs/framework/application.hh>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

namespace gs {
namespace framework {
Application::Application(unsigned int width,
                         unsigned int height,
                         const char*  title)
    : running(false) {
    window.open(width, height, title);
}

Application::~Application() {
}

int Application::main(int argc, char** argv) {
    if (running) {
        return EXIT_SUCCESS;
    }

    running = true;

    try {
        onStartup();

        while (!window.isClosed()) {
            auto event = window.pollEvents();
            if (event) {
                switch (event->type) {
                case gs::os::WindowEvent::Type::Closed:
                    onWindowClosed(*event);
                    window.close();
                    break;
                case gs::os::WindowEvent::Type::Resized:
                    onWindowResized(*event);
                    break;
                case gs::os::WindowEvent::Type::Moved:
                    onWindowMoved(*event);
                    break;
                }
            } else {
                onUpdate();
            }
        }

        onShutdown();
    } catch (const std::exception& ex) {
        displayError(ex.what());
    }

    running = false;

    return EXIT_SUCCESS;
}

void Application::onStartup() {
}

void Application::onShutdown() {
}

void Application::onUpdate() {
}

void Application::onWindowClosed(gs::os::WindowEvent& event) {
}

void Application::onWindowResized(gs::os::WindowEvent& event) {
}

void Application::onWindowMoved(gs::os::WindowEvent& event) {
}

} // namespace framework
} // namespace gs
