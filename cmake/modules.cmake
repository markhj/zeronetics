# The list of modules available in Zeronetics
set(ZEN_MODULES
        glfw-window
        opengl-renderer
        glsl-shader-builder
        control-systems
        assets
        gizmos
        scene-loader-hxl)

# Define the vendor (third-party) libraries required on a per-module basis.
# This ensures that dependency libraries are linked when consumed by client apps.
set(LIBS_GLFW_WINDOW glfw3)
set(LIBS_OPENGL_RENDERER)
set(LIBS_CONTROL_SYSTEMS)
set(LIBS_SCENE_LOADER_HXL cpp_hxl_lang)
