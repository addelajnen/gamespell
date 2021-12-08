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

#ifndef GAMESPELL_OS_WINDOW_HH
#define GAMESPELL_OS_WINDOW_HH

#include <memory>
#include <optional>
#include <queue>

#include <gs/noncopyable.hh>
#include <gs/propagate_const.hh>

#include <gs/os/window_handle.hh>

namespace gs {
namespace os {
struct WindowEvent;

class Window : private gs::Noncopyable {
public:
    Window();
    ~Window();

    void open(unsigned int width, unsigned int height, const char* title);
    void close();

    std::optional<WindowEvent> pollEvents();

    inline bool         isClosed() const { return closed; }
    inline WindowHandle getHandle() const { return handle; }

private:
    void                       pushEvent(const WindowEvent& event);
    std::optional<WindowEvent> popEvent();

    struct Implementation;

    gs::PropagateConst<std::unique_ptr<Implementation>> implementation;
    bool                                                closed;
    WindowHandle                                        handle;
    std::queue<WindowEvent>                             events;

    friend struct Implementation;
};
} // namespace os
} // namespace gs

#endif // GAMESPELL_OS_WINDOW_HH
