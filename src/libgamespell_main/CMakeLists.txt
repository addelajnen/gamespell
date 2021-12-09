add_library(gamespell_main STATIC
    main.cc)

if(WIN32)
    target_compile_definitions(gamespell_main
        PRIVATE
            UNICODE
            _UNICODE)
endif()

target_link_libraries(gamespell_main
    gamespell_core
)

