#include <iostream>
#include <stdexcept>

extern int main(int argc, char** argv);

#if defined(_WIN32)
#include <windows.h>
#if defined(UNICODE)
int wmain(int argc, wchar_t** argv) {
    char** multiByteArgv = new char*[argc];
    int    code          = EXIT_SUCCESS;

    try {
        for (auto i = 0; i < argc; i++) {
            auto size = WideCharToMultiByte(
                CP_UTF8, 0, argv[i], -1, nullptr, 0, nullptr, nullptr);

            multiByteArgv[i] = new char[size];
            WideCharToMultiByte(CP_UTF8,
                                0,
                                argv[i],
                                -1,
                                multiByteArgv[i],
                                size,
                                nullptr,
                                nullptr);
        }

        code = main(argc, multiByteArgv);
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        code = EXIT_FAILURE;
    }

    if (multiByteArgv) {
        for (auto i = 0; i < argc; i++) {
            delete[] multiByteArgv[i];
        }
        delete[] multiByteArgv;
    }

    return code;
}

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPWSTR    lpCmdLine,
                    int       nShowCmd) {
    return wmain(__argc, __wargv);
}
#else
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nShowCmd) {
    return main(__argc, __argv);
}
#endif

#endif
