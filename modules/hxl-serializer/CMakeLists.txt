cmake_minimum_required(VERSION 3.28)
project(hxl-serializer)

set(CMAKE_CXX_STANDARD 20)

add_library(hxl-serializer STATIC src/hxl-serializer.cpp)

target_link_libraries(hxl-serializer PRIVATE zeronetics cpp_hxl_lang)

target_include_directories(hxl-serializer PUBLIC include)
target_include_directories(hxl-serializer PUBLIC ${ZEN_VENDOR_DIR}/cpp-hxl-lang/include)
