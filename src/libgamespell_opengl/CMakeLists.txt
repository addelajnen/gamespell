add_library(gamespell_opengl
    graphics/opengl_extensions.cc
    graphics/opengl_extensions.hh
    graphics/opengl_shader_program.cc
    graphics/opengl_shader.cc
    graphics/opengl_vertex_buffer.cc)

target_compile_features(gamespell_opengl PRIVATE cxx_std_20)

include_directories(graphics)

if(WIN32)
target_sources(gamespell_opengl
    PRIVATE
        graphics/win32/opengl_render_context.cc)
endif()

find_package(OpenGL REQUIRED)
target_link_libraries(gamespell_opengl 
    PRIVATE
        ${OPENGL_gl_LIBRARY})
