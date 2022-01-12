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

#ifndef GAMESPELL_FRAMEWORK_APPLICATION_HH
#define GAMESPELL_FRAMEWORK_APPLICATION_HH

#include <memory>
#include <string_view>

#include <gs/os/window.hh>
#include <gs/os/window_event.hh>

namespace gs {
namespace framework {
class Application {
public:
    virtual ~Application();

    static std::unique_ptr<Application> create();

    int main(int argc, char** argv);

protected:
    Application(unsigned int width, unsigned int height, const char* title);

    virtual void onStartup();
    virtual void onShutdown();
    virtual void onUpdate();
    virtual void onWindowClosed(gs::os::WindowEvent& event);
    virtual void onWindowResized(gs::os::WindowEvent& event);
    virtual void onWindowMoved(gs::os::WindowEvent& event);

    void displayError(std::string_view message);

    inline gs::os::Window& getWindow() { return window; }

private:
    bool           running;
    gs::os::Window window;
};
} // namespace framework
} // namespace gs

#endif // GAMESPELL_FRAMEWORK_APPLICATION_HH
