@page engine-core-structure Core structure

To prevent circular dependencies, we've designed a clear hierarchy of
header inclusion and dependencies.

## Hierarchy

The hierarchy consists of these layers, reading from top-to-bottom, where
the top comprises the most basic and fundamental structures.

| Level                          | Description                                                                  |
|--------------------------------|------------------------------------------------------------------------------|
| **Core**: Fundamentals         | Typedefs, macros, enumerators                                                |
| **Core**: 2<sup>nd</sup> Level | Structs and classes with no dependencies outside own file                    |
| **Core**: 3<sup>rd</sup> Level | Structs and classes (with dependencies _only_ from ``vendor``)               |
| Contracts                      | Interfaces with _only_ pure virtual functions                                |
| Adv. structures                | Classes with more complexity, such as ZEN::Game, as well as abstract classes |
| Modules                        | Modules exist in isolation from each other, but can use the entire engine    |

Each level can depend on items from prior levels. Meaning, ``contracts``
can depend on any core level, but _not_ on advanced structures or modules.

Whether, and how, items in the same layer can depend on each other is
specified on a per-level basis.

## 🔨 Core: Fundamentals

**Dependency from same layer**: Not allowed  
**Location:** ``include/zeronetics/core/``

The first layer consists of primitive declarations such as ``typedef``s
and macros (e.g. @ref build-info) that have no dependencies and
exist in complete contextual isolation.

Examples: 

> Example:  
> ``gw_float`` typedef  
> ``ZEN::Key`` enumerator  
> @ref build-info, because it has no dependencies  
> logging.h macros are not allowed, because they depend on ZEN::Log 

## 📚 Core: 2<sup>nd</sup> level

**Dependency from same layer**: Not allowed  
**Location:** ``include/zeronetics/core/``

Structs and classes which:

- Have universal application and/or are general in nature
- Have no dependencies, aside from other definitions in the _same file_

Struct and classes containing methods must provide an implementation.
This is not to be treated as a layer with interfaces.

> Examples:  
> ZEN::Settings  
> ZEN::Version

## 📥 Core: 3<sup>rd</sup> level

**Dependency from same layer**: Not allowed (only from ``vendor``)  
**Location:** ``include/zeronetics/core/``

Similar to 2<sup>nd</sup> level, with the addition that these
structs and classes can incorporate third-party libraries from ``vendor``.

Examples:

- Vectors and matrices (which depend on ``glm``)

## 📜 Contracts

**Dependency from same layer**: Allowed, but exercise caution.  
**Location:** ``include/zeronetics/contracts/``

Interfaces in the ``contracts`` directory are allowed to have dependencies
from ``core`` and other contracts.

> Example: The ZEN::IWindow contract can depend on ZEN::IInputManager.

Remember that: Contracts must only have pure virtual functions.
For abstract classes, see the next chapter.

## 📱 Advanced structures

**Dependency from same layer**: Allowed, but exercise caution.  
**Location:** ``include/zeronetics/``

Classes and structs with more complexity, such as ZEN::Game.
These classes can have several dependencies, also from the same layer.

Abstract classes also reside in this layer. 

> Example:  
> ZEN::Game  
> logging.h and ZEN::Log  
> Abstract class ZEN::BaseInputManager which extends ZEN::IInputManager

## 📦 Modules

**Dependency from same layer**: Not allowed.  
**Location:** ``modules/``

Modules can extend and depend on anything from the main
engine.

They are under no circumstances allowed to have dependencies
in other modules, and must be treated in total isolation from them,
making no assumptions about their existence or functionality.
