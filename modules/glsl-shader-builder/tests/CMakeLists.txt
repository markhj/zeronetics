cmake_minimum_required(VERSION 3.28)
project(tests_glsl_shader_builder)

set(CMAKE_CXX_STANDARD 20)

add_executable(tests_glsl_shader_builder
        src/main.cpp

        # Cases
        src/cases/glsl-shader-builder-test.cpp)

target_link_libraries(tests_glsl_shader_builder PRIVATE zeronetics)

target_include_directories(tests_glsl_shader_builder PUBLIC ../include)

target_include_directories(tests_glsl_shader_builder PUBLIC ${ZEN_VENDOR_DIR}/cpp-bbunit/include)
