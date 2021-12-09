add_executable(shader_viewer
    main.cc)

target_compile_definitions(shader_viewer
    PRIVATE
        UNICODE
        _UNICODE)

target_link_libraries(shader_viewer
    PRIVATE
        gamespell_main
        gamespell_opengl)