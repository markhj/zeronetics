
set(ZEN_EXTENSIONS
        "Entity|Camera3D|3d/camera-3d"
        "Entity|Mesh3D|3d/mesh-3d"
        "Entity|PointLight3D|3d/point-light-3d"
        "Entity|DirectionalLight3D|3d/directional-light-3d")

set(ZEN_EXTENSION_FILES)
set(ZEN_EXTENSION_CLASSNAMES)

foreach (ZEN_EXT ${ZEN_EXTENSIONS})
    string(REPLACE "|" ";" ZEN_EXT_PARTS "${ZEN_EXT}")
    list(GET ZEN_EXT_PARTS 0 ZEN_EXT_TYPE)
    list(GET ZEN_EXT_PARTS 1 ZEN_EXT_CLASSNAME)
    list(GET ZEN_EXT_PARTS 2 ZEN_EXT_FILENAME)

    list(APPEND ZEN_EXTENSION_FILES ${ZEN_EXT_FILENAME})
    list(APPEND ZEN_EXTENSION_CLASSNAMES ${ZEN_EXT_CLASSNAME})
endforeach ()
