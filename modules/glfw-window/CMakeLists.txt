# GLFW Window module

cmake_minimum_required(VERSION 3.28)
project(glfw_window)

set(CMAKE_CXX_STANDARD 20)

add_library(glfw-window STATIC src/glfw-window.cpp)

target_include_directories(glfw-window PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
