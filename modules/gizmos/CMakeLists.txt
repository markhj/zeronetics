cmake_minimum_required(VERSION 3.28)
project(gizmos)

set(CMAKE_CXX_STANDARD 20)

add_library(gizmos STATIC src/3d-grid.cpp)

target_link_libraries(gizmos PRIVATE zeronetics)

target_include_directories(gizmos PUBLIC include)
