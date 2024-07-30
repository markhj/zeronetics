cmake_minimum_required(VERSION 3.28)
project(assets)

set(CMAKE_CXX_STANDARD 20)

add_library(assets STATIC
        src/asset-manager.cpp
        src/texture-2d.cpp)

target_link_libraries(assets PRIVATE zeronetics)

target_include_directories(assets PUBLIC include)
