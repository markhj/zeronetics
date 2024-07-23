/**
 * Zeronetics Engine - Primary Header File
 *
 * This header file provides a convenient access point to all
 * necessary features in Zeronetics, with the exception of modules.
 *
 * Modules must be included separately and on a per-need basis.
 *
 * @ref engine-core-structure
 */

#pragma once

// Core: Fundamentals
#include "core/build.h"
#include "core/enums.h"
#include "core/typedefs.h"

// Core: 2nd Level
#include "core/engine-info.h"
#include "core/gpu-alloc.h"
#include "core/inputs.h"
#include "core/io.h"
#include "core/settings.h"
#include "core/sysinfo.hpp"
#include "core/version.h"
#include "core/result.h"
#include "core/observer.h"

// Core: 3rd Level
#include "core/aabb.h"
#include "core/attributes.h"
#include "core/shape.h"
#include "core/tensors.h"
#include "core/vertices.h"
#include "core/timer.h"

// Contracts
#include "contracts/cameras.h"
#include "contracts/input-manager.h"
#include "contracts/render-manager.h"
#include "contracts/renderable.h"
#include "contracts/renderer.h"
#include "contracts/shader.h"
#include "contracts/shapes.h"
#include "contracts/transforms.h"
#include "contracts/window.h"

// Traits
#include "traits/has-unique-id.h"

// Adv. structures
#include "controls/base-input-manager.h"
#include "game/game.h"
#include "logging/logging.h"
#include "render/render-manager.h"
#include "zeronetics/process/process.h"

// Shapes
#include "shapes/3d/cube.h"

// Entities
#include "entities/3d/camera-3d.h"
#include "entities/3d/mesh-3d.h"
#include "entities/entity.h"
