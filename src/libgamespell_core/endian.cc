#include <gs/endian.hh>

namespace gs {
bool isBigEndian() {
    return (std::endian::native == std::endian::big);
}

bool isLittleEndian() {
    return (std::endian::native == std::endian::little);
}

uint32_t
toBigEndian(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    return (byte1 << 0) | (byte2 << 8) | (byte3 << 16) | (byte4 << 24);
}

uint32_t
toLittleEndian(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    return (byte4 << 0) | (byte3 << 8) | (byte2 << 16) | (byte1 << 24);
}

uint32_t toEndian(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    if (isBigEndian()) {
        return toBigEndian(byte1, byte2, byte3, byte4);
    }

    return toLittleEndian(byte1, byte2, byte3, byte4);
}
} // namespace gs