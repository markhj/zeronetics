cmake_minimum_required(VERSION 3.28)
project(zeronetics_engine)

set(CMAKE_CXX_STANDARD 20)

include(${ZEN_ROOT_DIR}/cmake/modules.cmake)

set(CORE_SRC
        src/core/basic.cpp
        src/core/engine-info.cpp
        src/core/controls.cpp
        src/core/game.cpp)

add_library(zeronetics STATIC ${CORE_SRC})

target_link_libraries(zeronetics PRIVATE ${ZEN_MODULES})
