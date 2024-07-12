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
#include "core/inputs.h"
#include "core/settings.h"
#include "core/version.h"

// Core: 3rd Level
#include "core/tensors.h"

// Contracts
#include "contracts/input-manager.h"
#include "contracts/renderer.h"
#include "contracts/shader.h"
#include "contracts/window.h"

// Adv. structures
#include "controls/base-input-manager.h"
#include "game/game.h"
#include "logging/logging.h"
