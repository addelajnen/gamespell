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

#include <fstream>
#include <iostream>
#include <sstream>

#include <gs/graphics/shader.hh>

#include "opengl_extensions.hh"

namespace gs {
namespace graphics {
Shader::Shader(std::filesystem::path filename, Type type)
    : type(type)
    , handle(GS_glCreateShader(fromType(type)))
    , released(false) {
    std::ifstream is(filename.c_str());
    if (!is) {
        throw std::runtime_error("failed to load shader");
    }
    std::stringstream ss;
    ss << is.rdbuf();
    is.close();

    std::string s      = ss.str();
    const char* source = s.c_str();

    GS_glShaderSource(handle, 1, &source, nullptr);

    GS_glCompileShader(handle);
    int isCompiled = 0;
    GS_glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        int messageSize = 0;
        GS_glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &messageSize);

        std::string message;
        message.resize(messageSize);

        GS_glGetShaderInfoLog(
            handle, messageSize, &messageSize, message.data());
        message.push_back('\0');

        std::cout << message << std::endl;

        throw std::runtime_error(std::string("failed to compile shader: ") +
                                 message.data());
    }
}

Shader::~Shader() {
    release();
}

void Shader::release() {
    if (!released) {
        GS_glDeleteShader(handle);
        handle = 0;
    }

    released = true;
}

unsigned int Shader::fromType(Type type) {
    switch (type) {
    case Shader::Type::Vertex:
        return GL_VERTEX_SHADER;
    case Shader::Type::Fragment:
        return GL_FRAGMENT_SHADER;
    default:
        throw std::runtime_error("unknown shader type");
    }
}
} // namespace graphics
} // namespace gs