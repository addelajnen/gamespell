add_executable(shader_viewer
    shader_viewer.cc
    shader_viewer.hh)

if(WIN32)
target_compile_definitions(shader_viewer
    PRIVATE
        UNICODE
        _UNICODE)
endif()

target_link_libraries(shader_viewer
    PRIVATE
        gamespell_framework
        gamespell_opengl)