#include <stdexcept>

#include <string>
#include <string_view>

#include <windows.h>

namespace gs {
namespace os {
std::wstring mbToWc(std::string_view s) {
    auto length = MultiByteToWideChar(
        CP_UTF8, MB_COMPOSITE, s.begin(), -1, nullptr, 0);

    std::wstring ws(length, L'\0');
    if (!MultiByteToWideChar(CP_UTF8, 0, s.begin(), -1, ws.data(), length)) {
        throw std::runtime_error(
            "failed to convert from wide-char to multi-byte");
    }

    return ws;
}

std::string wcToMb(std::wstring_view ws) {
    auto length = WideCharToMultiByte(
        CP_UTF8, 0, ws.begin(), -1, nullptr, 0, nullptr, nullptr);

    std::string s(length, L'\0');
    if (!WideCharToMultiByte(
            CP_UTF8, 0, ws.begin(), -1, s.data(), length, nullptr, nullptr)) {
        throw std::runtime_error(
            "failed to convert from wide-char to multi-byte");
    }

    return s;
}
} // namespace os
} // namespace gs