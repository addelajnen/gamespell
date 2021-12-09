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

#include <gs/graphics/shader_program.hh>

#include "opengl_extensions.hh"

namespace gs {
namespace graphics {
ShaderProgram::ShaderProgram()
    : handle(0)
    , released(true) {
}

ShaderProgram::~ShaderProgram() {
    release();
}

void ShaderProgram::use() {
    if (!released) {
        GS_glUseProgram(handle);
    }
}

void ShaderProgram::load(const Shader& vertex, const Shader& fragment) {
    release();

    handle = GS_glCreateProgram();

    if (!vertex.isReleased()) {
        GS_glAttachShader(handle, vertex.getHandle());
    }
    if (!fragment.isReleased()) {
        GS_glAttachShader(handle, fragment.getHandle());
    }
    GS_glLinkProgram(handle);

    int isLinked = 0;
    GS_glGetProgramiv(handle, GL_LINK_STATUS, &isLinked);

    if (!isLinked) {
        int messageSize = 0;
        GS_glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &messageSize);

        std::string message;
        message.resize(messageSize);

        GS_glGetProgramInfoLog(
            handle, messageSize, &messageSize, message.data());
        message.push_back('\0');

        throw std::runtime_error(
            std::string("failed to link shader program: ") + message);
    }

    released = false;
}

void ShaderProgram::release() {
    if (!released) {
        GS_glDeleteProgram(handle);
        handle = 0;
    }

    released = true;
}

void ShaderProgram::setBool(const char* name, bool value) const {
    if (!released) {
        GS_glUniform1i(GS_glGetUniformLocation(handle, name),
                       static_cast<int>(value));
    }
}
void ShaderProgram::setInt(const char* name, int value) const {
    if (!released) {
        GS_glUniform1i(GS_glGetUniformLocation(handle, name), value);
    }
}
void ShaderProgram::setFloat(const char* name, float value) const {
    if (!released) {
        GS_glUniform1f(GS_glGetUniformLocation(handle, name), value);
    }
}

void ShaderProgram::setMatrix4(const char* name, const float value[16]) const {
    if (!released) {
        GS_glUniformMatrix4fv(
            GS_glGetUniformLocation(handle, name), 1, GL_FALSE, value);
    }
}
} // namespace graphics
} // namespace gs