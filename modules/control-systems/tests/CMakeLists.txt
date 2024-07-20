cmake_minimum_required(VERSION 3.28)
project(tests_control_systems)

set(CMAKE_CXX_STANDARD 20)

add_executable(tests_control_systems
        src/main.cpp

        # Cases
        src/cases/control-systems-test.cpp)

target_link_libraries(tests_control_systems PRIVATE zeronetics)

target_include_directories(tests_control_systems PUBLIC ${ZEN_VENDOR_DIR}/cpp-bbunit/include)
