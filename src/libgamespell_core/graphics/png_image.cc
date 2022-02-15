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

#include <cstddef>
#include <fstream>
#include <iostream>

#include <gs/graphics/png_image.hh>

#include <gs/endian.hh>

namespace gs {
namespace graphics {
PNGImage::PNGImage() {
}

PNGImage::~PNGImage() {
}

bool PNGImage::load(const std::filesystem::path& filename) {
    bool isPNG = false;

    std::ifstream is(filename.c_str(),
                     std::ifstream::in | std::ifstream::binary);
    if (!is) {
        return false;
    }
    uint8_t signature[8] = {0};
    is.read(reinterpret_cast<char*>(signature), 8);
    if (is) {
        isPNG = signature[0] == 0x89 && signature[1] == 0x50 &&
                signature[2] == 0x4E && signature[3] == 0x47 &&
                signature[4] == 0x0D && signature[5] == 0x0A &&
                signature[6] == 0x1A && signature[7] == 0x0A;
        if (isPNG) {
            while (is) {
                Chunk chunk;
                if (!loadChunk(is, &chunk)) {
                    isPNG = false;
                    break;
                }

                switch (chunk.getType()) {
                case Chunk::Type::IHDR:
                    std::cout << "IHDR (" << chunk.length << ")" << std::endl;
                    break;
                case Chunk::Type::IDAT:
                    std::cout << "IDAT (" << chunk.length << ")" << std::endl;
                    break;
                case Chunk::Type::PLTE:
                    std::cout << "PLTE (" << chunk.length << ")" << std::endl;
                    break;
                case Chunk::Type::IEND:
                    std::cout << "IEND (" << chunk.length << ")" << std::endl;
                    break;
                }
            }
        }
    }

    is.close();

    return isPNG;
}

bool PNGImage::loadChunk(std::ifstream& is, Chunk* chunk) {
    uint8_t chunkLengthInBigEndian[4];
    is.read(reinterpret_cast<char*>(chunkLengthInBigEndian), 4);
    if (!is.good()) {
        return false;
    }

    chunk->length = toEndian(chunkLengthInBigEndian[0],
                             chunkLengthInBigEndian[1],
                             chunkLengthInBigEndian[2],
                             chunkLengthInBigEndian[3]);

    is.read(reinterpret_cast<char*>(chunk->type), 4);
    if (!is.good()) {
        return false;
    }

    if (chunk->getType() != PNGImage::Chunk::Type::IEND) {
        if (chunk->length > 0) {
            chunk->data.resize(chunk->length);
            is.read(reinterpret_cast<char*>(chunk->data.data()), chunk->length);
            if (!is.good()) {
                return false;
            }
        }

        is.read(reinterpret_cast<char*>(&chunk->crc), 4);
        if (!is.good()) {
            return false;
        }
    }

    return true;
}
} // namespace graphics
} // namespace gs