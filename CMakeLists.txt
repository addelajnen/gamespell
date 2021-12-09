cmake_minimum_required(VERSION 3.13)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(Gamespell
    VERSION 1.0.0)

option(BUILD_EXAMPLES "Build example projects" ON)
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_TOOLS "Build tools" ON)

include_directories(include)

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
if(BUILD_TOOLS)
  add_subdirectory(tools)
endif()