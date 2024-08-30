
# Create the autoload directory
file(MAKE_DIRECTORY ${ZEN_AUTOLOAD_DIR})

# Set filename
set(ZEN_AUTOLOAD_CPP_FILE ${ZEN_AUTOLOAD_DIR}/autoload.cpp)

include("cmake/extensions.cmake")

set(ZEN_AUTOLOAD_SRC
        "/**\n"
        " * Zeronetics Autoload File\n"
        " *\n"
        " * This file was generated by the CMake process.\n"
        " *\n"
        " * PLEASE NOTE:\n"
        " * This file is automatically generated, and might be overwritten again.\n"
        " * Changes made to this file should be expected to be lost.\n"
        " */\n"
        "\n"
)

foreach (ZEN_EXTENSION_FILE ${ZEN_EXTENSION_FILES})
    list(APPEND ZEN_AUTOLOAD_SRC "#include \"zeronetics/entities/${ZEN_EXTENSION_FILE}.h\"\n")
endforeach ()

list(APPEND ZEN_AUTOLOAD_SRC
        "\n"
        "namespace ZEN {\n"
        "\tclass Autoload {\n"
        "\tpublic:\n"
        "\t\tstatic void registerEntities() {\n"
        )

foreach (ZEN_EXTENSION_CLASSNAME ${ZEN_EXTENSION_CLASSNAMES})
    list(APPEND ZEN_AUTOLOAD_SRC "\t\t\t${ZEN_EXTENSION_CLASSNAME}().registerEntity()\;\n")
endforeach ()

list(APPEND ZEN_AUTOLOAD_SRC
        "\t\t}\n"
        "\t}\;\n"
        "}\n")

# Create the content of autoload.cpp
file(WRITE ${ZEN_AUTOLOAD_CPP_FILE} ${ZEN_AUTOLOAD_SRC})
