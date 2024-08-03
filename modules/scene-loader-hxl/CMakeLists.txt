cmake_minimum_required(VERSION 3.28)
project(scene-loader-hxl)

set(CMAKE_CXX_STANDARD 20)

add_library(scene-loader-hxl STATIC src/scene-loader-hxl.cpp)

target_link_libraries(scene-loader-hxl PRIVATE zeronetics cpp_hxl_lang)

target_include_directories(scene-loader-hxl PUBLIC include)
target_include_directories(scene-loader-hxl PUBLIC ${ZEN_VENDOR_DIR}/cpp-hxl-lang/include)
