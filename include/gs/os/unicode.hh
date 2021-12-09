#ifndef GAMESPELL_OS_UNICODE_HH
#define GAMESPELL_OS_UNICODE_HH

#include <string>
#include <string_view>

namespace gs {
namespace os {
extern std::wstring mbToWc(std::string_view s);
extern std::string  wcToMb(std::wstring_view ws);
} // namespace os
} // namespace gs

#endif // GAMESPELL_OS_UNICODE_HH
