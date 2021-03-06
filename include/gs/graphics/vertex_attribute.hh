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

#ifndef GAMESPELL_GRAPHICS_VERTEX_ATTRIBUTE_HH
#define GAMESPELL_GRAPHICS_VERTEX_ATTRIBUTE_HH

namespace gs {
namespace graphics {

struct VertexAttribute {
    enum class Usage { Position = 0, Texture, Color, Normal };

    enum class Type {
        Byte = 0,
        UnsignedByte,
        Short,
        UnsignedShort,
        Integer,
        UnsignedInteger,
        Float,
        Double
    };

    unsigned int offset;
    Type         type;
    unsigned int size;
    Usage        usage;
};

const std::vector<VertexAttribute> FloatXY = {
    {0,
     VertexAttribute::Type::Float,
     sizeof(float) * 2,
     VertexAttribute::Usage::Position}
};
const std::vector<VertexAttribute> FloatXYRGBA = {
    {0, VertexAttribute::Type::Float, 2, VertexAttribute::Usage::Position},
    {0, VertexAttribute::Type::Float, 4,    VertexAttribute::Usage::Color}
};

const std::vector<VertexAttribute> FloatXYZ = {
    {0, VertexAttribute::Type::Float, 3, VertexAttribute::Usage::Position}
};

const std::vector<VertexAttribute> FloatXYZRGBA = {
    {0, VertexAttribute::Type::Float, 3, VertexAttribute::Usage::Position},
    {0, VertexAttribute::Type::Float, 4,    VertexAttribute::Usage::Color}
};

} // namespace graphics
} // namespace gs

#endif // GAMESPELL_GRAPHICS_VERTEX_ATTRIBUTE_HH
