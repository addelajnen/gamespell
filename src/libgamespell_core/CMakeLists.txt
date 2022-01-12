add_library(gamespell_core
    os/window.cc)

target_compile_features(gamespell_core PRIVATE cxx_std_20)

if(WIN32)
target_compile_definitions(gamespell_core
    PRIVATE
        UNICODE
        _UNICODE)

target_sources(gamespell_core
    PRIVATE
        os/win32/error.cc
        os/win32/file_watcher.cc
        os/win32/window.cc
        os/win32/unicode.cc)
endif()