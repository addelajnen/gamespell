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

#ifndef GAMESPELL_GRAPHICS_PNG_IMAGE_HH
#define GAMESPELL_GRAPHICS_PNG_IMAGE_HH

#include <gs/graphics/image.hh>

namespace gs {
namespace graphics {
class PNGImage : public Image {
public:
    PNGImage();
    ~PNGImage();

    struct Chunk {
    public:
        enum class Type { Unknown = 0, IHDR, IDAT, PLTE, IEND };

        struct IHDRData {
            uint32_t width;
            uint32_t height;
            uint8_t  bitDepth;
            uint8_t  colorType;
            uint8_t  compressionMethod;
            uint8_t  filterMethod;
            uint8_t  interlaceMethod;
        };

        struct IDATData {
            std::vector<uint8_t> bytes;
        };

        inline Type getType() const {
            if (type[0] == 'I' && type[1] == 'H' ||
                type[2] == 'D' && type[3] == 'R') {
                return Type::IHDR;
            }
            if (type[0] == 'P' && type[1] == 'L' ||
                type[2] == 'T' && type[3] == 'E') {
                return Type::PLTE;
            }
            if (type[0] == 'I' && type[1] == 'D' ||
                type[2] == 'A' && type[3] == 'T') {
                return Type::IDAT;
            }
            if (type[0] == 'I' && type[1] == 'E' ||
                type[2] == 'N' && type[3] == 'D') {
                return Type::IEND;
            }

            return Type::Unknown;
        }

        uint32_t             length;
        uint8_t              type[4];
        std::vector<uint8_t> data;
        uint32_t             crc;
    };

    virtual bool load(const std::filesystem::path& path) final;

private:
    bool loadChunk(std::ifstream& is, Chunk* chunk);
};
} // namespace graphics
} // namespace gs

#endif // GAMESPELL_GRAPHICS_PNG_IMAGE_HH
