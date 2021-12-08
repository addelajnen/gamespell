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

#include <queue>
#include <stdexcept>

#include <windows.h>

#include <gs/os/window.hh>
#include <gs/os/window_event.hh>

namespace gs {
namespace os {
class Window::Implementation {
public:
    Implementation(Window& owner);
    ~Implementation();

    void createWindow(unsigned int width,
                      unsigned int height,
                      const char*  title);
    void destroyWindow();
    void processWindowMessages();

    WNDCLASSEX wc;
    bool       shouldUnregisterWindowClass;
    Window&    owner;

protected:
    static LRESULT CALLBACK winProc(HWND   hwnd,
                                    UINT   msg,
                                    WPARAM wParam,
                                    LPARAM lParam);
};

Window::Implementation::Implementation(Window& owner)
    : wc({0})
    , shouldUnregisterWindowClass(false)
    , owner(owner) {
}

Window::Implementation::~Implementation() {
    destroyWindow();

    if (shouldUnregisterWindowClass) {
        UnregisterClass(wc.lpszClassName, wc.hInstance);
    }
}

void Window::Implementation::createWindow(unsigned int width,
                                          unsigned int height,
                                          const char*  title) {
    HINSTANCE hinstance = GetModuleHandle(nullptr);
    if (!hinstance) {
        throw std::runtime_error("failed to get windows module handle");
    }

    wc.lpszClassName = TEXT("gamespellwindowclass");
    if (!GetClassInfoEx(hinstance, wc.lpszClassName, &wc)) {
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc   = Window::Implementation::winProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hinstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
        wc.lpszMenuName  = NULL;
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc)) {
            throw std::runtime_error("failed to register window class");
        }

        shouldUnregisterWindowClass = true;
    }

    RECT rc = {.left   = 0,
               .top    = 0,
               .right  = static_cast<LONG>(width),
               .bottom = static_cast<LONG>(height)};
    AdjustWindowRectEx(
        &rc, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, false, WS_EX_APPWINDOW);

    int cx = (GetSystemMetrics(SM_CXSCREEN) / 2) - (rc.right - rc.left) / 2;
    int cy = (GetSystemMetrics(SM_CYSCREEN) / 2) - (rc.bottom - rc.top) / 2;

    HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW,
                               wc.lpszClassName,
                               title,
                               WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN |
                                   WS_CLIPSIBLINGS,
                               cx,
                               cy,
                               rc.right - rc.left,
                               rc.bottom - rc.top,
                               nullptr,
                               nullptr,
                               wc.hInstance,
                               this);
    if (!hwnd) {
        throw std::runtime_error("failed to create window");
    }

    UpdateWindow(hwnd);
    ShowWindow(hwnd, SW_SHOW);

    owner.handle = hwnd;
    owner.closed = false;
}

void Window::Implementation::destroyWindow() {
    if (owner.handle) {
        DestroyWindow(owner.handle);
        owner.handle = nullptr;
    }

    owner.closed = true;
}

void Window::Implementation::processWindowMessages() {
    if (owner.handle) {
        MSG msg;
        while (PeekMessage(&msg, owner.handle, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

LRESULT CALLBACK Window::Implementation::winProc(HWND   hwnd,
                                                 UINT   msg,
                                                 WPARAM wParam,
                                                 LPARAM lParam) {
    Window::Implementation* implementation = nullptr;

    if (msg == WM_NCCREATE) {
        auto cs        = reinterpret_cast<LPCREATESTRUCT>(lParam);
        implementation = reinterpret_cast<Window::Implementation*>(
            cs->lpCreateParams);
        if (implementation) {
            SetWindowLongPtr(hwnd,
                             GWLP_USERDATA,
                             reinterpret_cast<LONG_PTR>(implementation));
        }

        return TRUE;
    }

    implementation = reinterpret_cast<Window::Implementation*>(
        GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (implementation) {
        switch (msg) {
        case WM_CLOSE:
            implementation->owner.pushEvent(
                {.type = WindowEvent::Type::Closed});
            return 0;

        case WM_MOVE:
            implementation->owner.pushEvent({.type = WindowEvent::Type::Moved,
                                             .data = {.moved = {
                                                          .x = LOWORD(lParam),
                                                          .y = HIWORD(lParam),
                                                      }}});
            return 0;

        case WM_SIZE:
            implementation->owner.pushEvent(
                {.type = WindowEvent::Type::Resized,
                 .data = {.resized = {
                              .width  = LOWORD(lParam),
                              .height = HIWORD(lParam),
                          }}});
            return 0;
        };
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

Window::Window()
    : implementation(std::make_unique<Implementation>(*this))
    , closed(true)
    , handle(nullptr) {
}

Window::~Window() {
    close();
}

void Window::open(unsigned int width, unsigned int height, const char* title) {
    implementation->createWindow(width, height, title);
}

void Window::close() {
    implementation->destroyWindow();
}

std::optional<WindowEvent> Window::pollEvents() {
    implementation->processWindowMessages();

    return popEvent();
}
} // namespace os
} // namespace gs