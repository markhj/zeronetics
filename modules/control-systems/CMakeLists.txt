cmake_minimum_required(VERSION 3.28)
project(control-systems)

set(CMAKE_CXX_STANDARD 20)

add_library(control-systems STATIC
        src/control-assist.cpp
        src/free-camera.cpp)

target_link_libraries(control-systems PRIVATE zeronetics)

target_include_directories(control-systems PUBLIC include)
