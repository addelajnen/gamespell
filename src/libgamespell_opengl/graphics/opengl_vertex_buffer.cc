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

#include <optional>
#include <stdexcept>

#include <gs/graphics/vertex_buffer.hh>

#include "opengl_extensions.hh"

namespace gs {
namespace graphics {
struct VertexBuffer::Implementation {
    Implementation();
    ~Implementation();

    void assign(void*                               vertices,
                unsigned int                        count,
                unsigned int                        size,
                unsigned int                        stride,
                const std::vector<VertexAttribute>& attributes);
    void use() const;

    unsigned int                vao;
    unsigned int                vbo;
    std::optional<unsigned int> positionAttribute;
    std::optional<unsigned int> textureAttribute;
    std::optional<unsigned int> colorAttribute;
    std::optional<unsigned int> normalAttribute;
};

void VertexBuffer::Implementation::assign(
    void*                               vertices,
    unsigned int                        count,
    unsigned int                        size,
    unsigned int                        stride,
    const std::vector<VertexAttribute>& attributes) {
    GS_glGenVertexArrays(1, &vao);
    GS_glGenBuffers(1, &vbo);
    GS_glBindVertexArray(vao);
    GS_glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GS_glBufferData(GL_ARRAY_BUFFER, count * size, vertices, GL_STATIC_DRAW);

    unsigned int offset = 0;
    unsigned int index  = 0;
    for (const auto& attribute : attributes) {
        unsigned int type;
        unsigned int typeSize = 0;
        if (attribute.type == VertexAttribute::Type::Byte) {
            type     = GL_BYTE;
            typeSize = sizeof(GLbyte);
        } else if (attribute.type == VertexAttribute::Type::UnsignedByte) {
            type     = GL_UNSIGNED_BYTE;
            typeSize = sizeof(GLubyte);
        } else if (attribute.type == VertexAttribute::Type::Short) {
            type     = GL_SHORT;
            typeSize = sizeof(GLshort);
        } else if (attribute.type == VertexAttribute::Type::UnsignedShort) {
            type     = GL_UNSIGNED_SHORT;
            typeSize = sizeof(GLushort);
        } else if (attribute.type == VertexAttribute::Type::Integer) {
            type     = GL_INT;
            typeSize = sizeof(GLint);
        } else if (attribute.type == VertexAttribute::Type::UnsignedInteger) {
            type     = GL_UNSIGNED_INT;
            typeSize = sizeof(GLuint);
        } else if (attribute.type == VertexAttribute::Type::Float) {
            type     = GL_FLOAT;
            typeSize = sizeof(GLfloat);
        } else if (attribute.type == VertexAttribute::Type::Double) {
            type     = GL_DOUBLE;
            typeSize = sizeof(GLdouble);
        } else {
            continue;
        }

        GS_glVertexAttribPointer(index,
                                 attribute.size,
                                 type,
                                 GL_FALSE,
                                 size,
                                 reinterpret_cast<void*>(offset));

        switch (attribute.usage) {
        case VertexAttribute::Usage::Position:
            positionAttribute = index;
            break;
        case VertexAttribute::Usage::Texture:
            textureAttribute = index;
            break;
        case VertexAttribute::Usage::Color:
            colorAttribute = index;
            break;
        case VertexAttribute::Usage::Normal:
            normalAttribute = index;
            break;
        }

        offset += attribute.size * typeSize;
        ++index;
    }
}

VertexBuffer::Implementation::Implementation() {
}

VertexBuffer::Implementation::~Implementation() {
    GS_glDeleteBuffers(1, &vbo);
    GS_glDeleteVertexArrays(1, &vao);
}

void VertexBuffer::Implementation::use() const {
    GS_glBindVertexArray(vao);
    if (positionAttribute) {
        GS_glEnableVertexAttribArray(*positionAttribute);
    }
    if (textureAttribute) {
        GS_glEnableVertexAttribArray(*textureAttribute);
    }
    if (colorAttribute) {
        GS_glEnableVertexAttribArray(*colorAttribute);
    }
    if (normalAttribute) {
        GS_glEnableVertexAttribArray(*normalAttribute);
    }
}

VertexBuffer::VertexBuffer()
    : implementation(std::make_unique<Implementation>()) {
}

VertexBuffer::~VertexBuffer() {
}

void VertexBuffer::assign(void*                               vertices,
                          unsigned int                        count,
                          unsigned int                        size,
                          unsigned int                        stride,
                          const std::vector<VertexAttribute>& attributes) {
    implementation->assign(vertices, count, size, stride, attributes);
}

void VertexBuffer::use() const {
    implementation->use();
}
} // namespace graphics
} // namespace gs