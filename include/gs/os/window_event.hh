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

#ifndef GAMESPELL_OS_WINDOW_EVENT_HH
#define GAMESPELL_OS_WINDOW_EVENT_HH

namespace gs {
namespace os {
struct WindowEvent {
    enum class Type {
        Closed,
        Resized,
        Moved,
    };

    struct ResizedData {
        unsigned int width;
        unsigned int height;
    };

    struct MovedData {
        unsigned int x;
        unsigned int y;
    };

    union Data {
        ResizedData resized;
        MovedData   moved;
    };

    Type type;
    Data data;
};
} // namespace os
} // namespace gs

#endif // GAMESPELL_OS_WINDOW_EVENT_HH
