cmake_minimum_required(VERSION 3.28)
project(zeronetics_engine)

set(CMAKE_CXX_STANDARD 20)

include(${ZEN_ROOT_DIR}/cmake/modules.cmake)

set(CORE_SRC
        # Core: 2nd layer
        src/core/version.cpp
        src/core/engine-info.cpp
        src/core/controls.cpp
        src/core/io.cpp
        src/core/sysinfo.cpp
        src/core/result.cpp
        src/core/timer.cpp
        src/core/observer.cpp
        src/process/process.cpp
        src/core/globals.cpp
        src/core/shader-blueprint.cpp

        # Core: 3rd layer
        src/core/aabb.cpp
        src/core/vertices.cpp

        # Helpers
        src/helpers/strings.cpp
        src/helpers/vertices.cpp

        # Traits
        src/traits/has-unique-id.cpp
        src/traits/processor.cpp

        # Adv. structures
        src/render/render-manager.cpp
        src/logging/log.cpp
        src/game/game.cpp

        # Shapes
        src/shapes/3d/shape-3d.cpp
        src/shapes/3d/cube.cpp

        # Entities
        src/entities/entity.cpp
        src/entities/3d/point-light-3d.cpp
        src/entities/3d/directional-light-3d.cpp
        src/entities/3d/camera-3d.cpp
        src/entities/3d/mesh-3d.cpp)

add_library(zeronetics STATIC ${CORE_SRC})

target_link_libraries(zeronetics PRIVATE ${ZEN_MODULES})

target_include_directories(zeronetics PUBLIC ${ZEN_VENDOR_DIR}/glm)
