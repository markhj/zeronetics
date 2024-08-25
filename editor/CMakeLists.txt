cmake_minimum_required(VERSION 3.28)
project(zeronetics_editor)

set(CMAKE_CXX_STANDARD 20)

include_directories(${ZEN_VENDOR_DIR}/glad/include)

include_directories(src/ui-elements)

add_executable(editor
        src/main.cpp

        # Editor
        src/editor.cpp
        src/utilities/editor-ui.cpp

        # UI Elements
        src/ui-elements/ui-element.cpp
        src/ui-elements/button.cpp
        src/ui-elements/label.cpp
        src/ui-elements/separator.cpp
        src/ui-elements/box.cpp
        src/ui-elements/text-field.cpp

        # Utilities
        src/utilities/editor-utility.cpp
        src/utilities/main-menu.cpp
        src/utilities/about.cpp
        src/utilities/new-project.cpp
        src/utilities/side-panel.cpp
        src/utilities/project.cpp
        src/utilities/scene.cpp
        src/utilities/scene-entity.cpp
        src/utilities/font-manager.cpp
        src/utilities/project-settings.cpp
        src/utilities/load-project.cpp

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

target_link_libraries(editor PRIVATE
        zeronetics
        glfw
        opengl-renderer
        glsl-shader-builder
        gizmos
        cpp_hxl_lang
        control-systems)

target_include_directories(editor PUBLIC ${ZEN_VENDOR_DIR}/cpp-hxl-lang/include)
target_include_directories(editor PRIVATE ${ZEN_VENDOR_DIR}/glfw/include)
target_include_directories(editor PUBLIC ${ZEN_VENDOR_DIR}/imgui)

file(COPY stub DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

