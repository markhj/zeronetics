cmake_minimum_required(VERSION 3.28)
project(zeronetics_editor)

set(CMAKE_CXX_STANDARD 20)

add_executable(editor src/main.cpp)

target_link_libraries(editor PRIVATE zeronetics glfw-window)

