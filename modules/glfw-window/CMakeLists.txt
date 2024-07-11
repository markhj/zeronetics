# GLFW Window module

cmake_minimum_required(VERSION 3.28)
project(glfw_window)

set(CMAKE_CXX_STANDARD 20)

add_library(glfw-window STATIC src/glfw-window.cpp)

target_link_libraries(glfw-window PRIVATE zeronetics glfw)

target_include_directories(glfw-window PUBLIC include)
target_include_directories(glfw-window PRIVATE ${ZEN_VENDOR_DIR}/glfw/include)
