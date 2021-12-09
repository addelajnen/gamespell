#if defined(_WIN32)

#include <string>
#include <vector>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#include <windows.h>

#include <gs/os/unicode.hh>

extern int main(int, char**);

#if defined(UNICODE)
// Windows unicode console entry
int wmain(int argc, wchar_t** wargv) {
    char* argv[argc] = {nullptr};

    std::vector<std::string> argvs;
    for (std::size_t i = 0; i < argc; i++) {
        wchar_t* warg = wargv[i];

        argvs.push_back(gs::os::wcToMb(warg));
        argv[i] = argvs.back().data();
    }

    return main(argc, argv);
}

// Windows unicode window entry
int WINAPI wWinMain(HINSTANCE instanceHandle,
                    HINSTANCE prevInstanceHandle,
                    LPWSTR    cmdLine,
                    int       showCmd) {
    return wmain(__argc, __wargv);
}
#else
// Windows multi-byte console entry
int wmain(int argc, wchar_t** argv) {
    return main(argc, argv);
}

// Windows multi-byte window entry
int WINAPI WinMain(HINSTANCE instanceHandle,
                   HINSTANCE prevInstanceHandle,
                   LPSTR     cmdLine,
                   int       showCmd) {
    return main(__argc, __argv);
}
#endif

#endif