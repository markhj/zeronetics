cmake_minimum_required(VERSION 3.28)
project(zeronetics_editor)

set(CMAKE_CXX_STANDARD 20)

include_directories(${ZEN_VENDOR_DIR}/glad/include)

add_executable(editor
        src/main.cpp

        # Editor
        src/editor.cpp
        src/editor-ui.cpp

        # UI Elements
        src/ui-elements/ui-element.cpp
        src/ui-elements/button.cpp

        # Utilities
        src/utilities/editor-utility.cpp
        src/utilities/main-menu.cpp
        src/utilities/about.cpp

        # GLAD
        ${ZEN_VENDOR_DIR}/glad/src/glad.c

        # ImGui
        ${ZEN_VENDOR_DIR}/imgui/imgui.cpp
        ${ZEN_VENDOR_DIR}/imgui/imgui_draw.cpp
        ${ZEN_VENDOR_DIR}/imgui/imgui_tables.cpp
        ${ZEN_VENDOR_DIR}/imgui/imgui_widgets.cpp
        ${ZEN_VENDOR_DIR}/imgui/imgui_widgets.cpp

        ${ZEN_VENDOR_DIR}/imgui/backends/imgui_impl_glfw.cpp
        ${ZEN_VENDOR_DIR}/imgui/backends/imgui_impl_opengl3.cpp
        )

target_link_libraries(editor PRIVATE zeronetics glfw opengl-renderer glsl-shader-builder gizmos control-systems)

target_include_directories(editor PRIVATE ${ZEN_VENDOR_DIR}/glfw/include)
target_include_directories(editor PUBLIC ${ZEN_VENDOR_DIR}/imgui)

