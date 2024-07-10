include(CMakePackageConfigHelpers)

get_filename_component(ZEN_LIB_ROOT "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/zeronetics_Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/zeronetics_ConfigVersion.cmake"
        DESTINATION lib/cmake/zeronetics
)

# Main engine code
add_library(zeronetics STATIC IMPORTED)

target_include_directories(zeronetics INTERFACE ${ZEN_LIB_ROOT}/include)

set_target_properties(zeronetics PROPERTIES
        IMPORTED_LOCATION_DEBUG "${ZEN_LIB_ROOT}/build/debug/lib/libzeronetics.a"
        IMPORTED_LOCATION_RELEASE "${ZEN_LIB_ROOT}/build/release/lib/libzeronetics.a"
)

# Modules
include(${ZEN_LIB_ROOT}/cmake/modules.cmake)
foreach (ZEN_MODULE ${ZEN_MODULES})
    add_library(${ZEN_MODULE} STATIC IMPORTED)

    target_include_directories(zeronetics INTERFACE ${ZEN_LIB_ROOT}/modules/${ZEN_MODULE}/include)

    set_target_properties(glfw-window PROPERTIES
            IMPORTED_LOCATION_DEBUG "${ZEN_LIB_ROOT}/build/debug/lib/lib${ZEN_MODULE}.a"
            IMPORTED_LOCATION_RELEASE "${ZEN_LIB_ROOT}/build/release/lib/lib${ZEN_MODULE}.a"
    )
endforeach ()
