cmake_minimum_required(VERSION 3.28)
project(game_engine)

set(CMAKE_CXX_STANDARD 20)

# Directories
set(ZEN_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ZEN_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(ZEN_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(ZEN_AUTOLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/autoload)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Convert build type to lowercase
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER)

# Set output directories for different build configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/bin)

include_directories(include)

# Autoload generator
include(cmake/autoload-generator.cmake)

# Build vendor projects
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/cpp-hxl-lang)

# Engine
add_subdirectory(engine)

# Editor
add_subdirectory(editor)

# Modules
include(cmake/modules.cmake)
foreach (ZEN_MODULE ${ZEN_MODULES})
    add_subdirectory(modules/${ZEN_MODULE})

    # If a "tests" directory exists, we will include its CMake file
    # in the build process
    set(MODULE_TEST_PATH ${ZEN_MODULES_DIR}/${ZEN_MODULE}/tests)
    if (EXISTS ${MODULE_TEST_PATH})
        add_subdirectory(${MODULE_TEST_PATH})

        # Furthermore, if its test suite has payloads, we will copy
        # those to the directory from which the test executable will run
        set(MODULE_TEST_PAYLOAD_PATH ${ZEN_MODULES_DIR}/${ZEN_MODULE}/tests/payloads)
        if (EXISTS ${MODULE_TEST_PAYLOAD_PATH})
            file(COPY ${MODULE_TEST_PAYLOAD_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        endif ()
    endif ()
endforeach ()

# Tests
if ($ENV{ZEN_BUILD_TESTS})
    add_subdirectory(tests)
endif ()
