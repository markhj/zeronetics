cmake_minimum_required(VERSION 3.28)
project(zeronetics_tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(tests
        src/main.cpp

        # Cases
        src/cases/io-test.cpp)

target_link_libraries(tests PRIVATE zeronetics)

target_include_directories(zeronetics PUBLIC ${ZEN_VENDOR_DIR}/cpp-bbunit/include)

# Copy the payloads directory
file(COPY payloads DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
