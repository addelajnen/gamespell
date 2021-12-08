add_executable(test_math
    ${CMAKE_CURRENT_SOURCE_DIR}/math/test_vector2.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/math/test_vector3.cc)

target_compile_features(test_math PRIVATE cxx_std_20)

target_include_directories(test_math
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(test_math 
    PRIVATE
        gamespell_core)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(test_math PRIVATE Catch2::Catch2)

