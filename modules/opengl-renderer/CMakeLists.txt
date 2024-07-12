cmake_minimum_required(VERSION 3.28)
project(opengl-renderer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${ZEN_VENDOR_DIR}/glad/include)

set(OPENGL_RENDERER_UTILS
        src/bindable.cpp)

add_library(opengl-renderer STATIC
        src/opengl-renderer.cpp
        ${OPENGL_RENDERER_UTILS}
        ${ZEN_VENDOR_DIR}/glad/src/glad.c)

target_link_libraries(opengl-renderer PRIVATE zeronetics glfw)

target_include_directories(opengl-renderer PUBLIC include)
