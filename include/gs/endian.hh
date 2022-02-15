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

#ifndef GAMESPELL_ENDIAN_HH
#define GAMESPELL_ENDIAN_HH

#include <bit>
#include <cstdint>

namespace gs {
extern bool isBigEndian();
extern bool isLittleEndian();
extern uint32_t
toBigEndian(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
extern uint32_t
toLittleEndian(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
extern uint32_t
toEndian(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
} // namespace gs

#endif // GAMESPELL_ENDIAN_HH
