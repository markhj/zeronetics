cmake_minimum_required(VERSION 3.28)
project(glsl-shader-builder)

set(CMAKE_CXX_STANDARD 20)

add_library(glsl-shader-builder STATIC src/glsl-shader-builder.cpp)

target_link_libraries(glsl-shader-builder PRIVATE zeronetics)

target_include_directories(glsl-shader-builder PUBLIC include)
