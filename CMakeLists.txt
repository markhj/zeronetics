cmake_minimum_required(VERSION 3.28)
project(game_engine)

set(CMAKE_CXX_STANDARD 20)

# Directories
set(ZEN_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ZEN_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(ZEN_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Convert build type to lowercase
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_LOWER)

# Set output directories for different build configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${BUILD_TYPE_LOWER}/bin)

# Create directories (which due to subdirectories might not be possible to generate otherwise)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/docs)

include_directories(include)

# Build vendor projects
add_subdirectory(vendor/glfw)

# Modules
include(cmake/modules.cmake)
foreach (ZEN_MODULE ${ZEN_MODULES})
    add_subdirectory(modules/${ZEN_MODULE})
endforeach ()

# Engine
add_subdirectory(engine)

# Editor
add_subdirectory(editor)
