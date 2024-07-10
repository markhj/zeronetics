@page arch Architecture

## 💫 Overview

The **Zeronetics** engine comprises the main engine code, and a number of modules.

The engine compiles to a static library which can be used by client applications
(i.e. games). The modules are built alongside the engine, also as static libraries.

The core contains functionality which is used across modules, and possibly also
in the games, such as I/O, math, interfaces, contracts, typedefs, and so forth.

Modules exist in complete isolation from other modules, but can freely depend
on anything contained in the core. This ensures modularity, making it easy
to swap components. For instance, switching from OpenGL to Vulkan should be
an easy "plug-and-play" from the game developer's perspective.
