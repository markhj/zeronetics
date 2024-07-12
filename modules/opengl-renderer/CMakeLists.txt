cmake_minimum_required(VERSION 3.28)
project(opengl-renderer)

set(CMAKE_CXX_STANDARD 20)

add_library(opengl-renderer STATIC src/opengl-renderer.cpp)

target_link_libraries(opengl-renderer PRIVATE zeronetics)

target_include_directories(opengl-renderer PUBLIC include)
