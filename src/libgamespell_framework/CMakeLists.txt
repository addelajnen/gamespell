add_library(gamespell_framework STATIC
    application.cc
    main.cc)

if(WIN32)
    target_compile_definitions(gamespell_framework
        PRIVATE
            UNICODE
            _UNICODE)
    target_sources(gamespell_framework
        PRIVATE
            win32/application.cc)
endif()

target_link_libraries(gamespell_framework
    gamespell_main
)

