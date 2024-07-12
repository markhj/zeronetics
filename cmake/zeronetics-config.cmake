include(CMakePackageConfigHelpers)

get_filename_component(ZEN_LIB_ROOT "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/zeronetics_Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/zeronetics_ConfigVersion.cmake"
        DESTINATION lib/cmake/zeronetics
)

# MAIN ENGINE CODE
add_library(zeronetics STATIC IMPORTED)

target_include_directories(zeronetics INTERFACE
        ${ZEN_LIB_ROOT}/include
        ${ZEN_LIB_ROOT}/vendor/glm)

set_target_properties(zeronetics PROPERTIES
        IMPORTED_LOCATION_DEBUG "${ZEN_LIB_ROOT}/build/debug/lib/libzeronetics.a"
        IMPORTED_LOCATION_RELEASE "${ZEN_LIB_ROOT}/build/release/lib/libzeronetics.a"
)

# MODULES
include(${ZEN_LIB_ROOT}/cmake/modules.cmake)
foreach (ZEN_MODULE ${ZEN_MODULES})
    # Create the library
    add_library(${ZEN_MODULE} STATIC IMPORTED)

    # The include path with the public header files that the
    # module wants to expose to the world
    target_include_directories(${ZEN_MODULE} INTERFACE ${ZEN_LIB_ROOT}/modules/${ZEN_MODULE}/include)

    # The directory in which the module artifacts will be built
    set_target_properties(${ZEN_MODULE} PROPERTIES
            IMPORTED_LOCATION_DEBUG "${ZEN_LIB_ROOT}/build/debug/lib/lib${ZEN_MODULE}.a"
            IMPORTED_LOCATION_RELEASE "${ZEN_LIB_ROOT}/build/release/lib/lib${ZEN_MODULE}.a"
    )

    # Link Zeronetics core to the module
    target_link_libraries(${ZEN_MODULE} INTERFACE
            $<$<CONFIG:Debug>:${ZEN_LIB_ROOT}/build/debug/lib/libzeronetics.a>
            $<$<CONFIG:Release>:${ZEN_LIB_ROOT}/build/release/lib/libzeronetics.a>
    )

    # Iterate through specific vendor/third-party dependencies
    # that are requested by each module
    string(TOUPPER "${ZEN_MODULE}" ZEN_MODULE_UC)
    string(REPLACE "-" "_" ZEN_MODULE_DEPENDENCIES "${ZEN_MODULE_UC}")
    foreach (LIB ${LIBS_${ZEN_MODULE_DEPENDENCIES}})
        target_link_libraries(${ZEN_MODULE} INTERFACE
                $<$<CONFIG:Debug>:${ZEN_LIB_ROOT}/build/debug/lib/lib${LIB}.a>
                $<$<CONFIG:Release>:${ZEN_LIB_ROOT}/build/release/lib/lib${LIB}.a>
        )
    endforeach ()
endforeach ()
