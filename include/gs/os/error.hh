#ifndef GAMESPELL_OS_ERROR_HH
#define GAMESPELL_OS_ERROR_HH

#include <string>

namespace gs {
namespace os {
extern int         getLastNativeError();
extern std::string describeLastNativeError();
} // namespace os
} // namespace gs

#endif // GAMESPELL_OS_ERROR_HH
