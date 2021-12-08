add_library(gamespell_core
    os/window.cc)

target_compile_features(gamespell_core PRIVATE cxx_std_20)

if(WIN32)
target_sources(gamespell_core
    PRIVATE
        os/win32/window.cc)
endif()