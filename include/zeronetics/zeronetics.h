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

// Fundamentals
#include "core/controls.h"
#include "core/engine-info.h"
#include "core/macros.h"
#include "core/settings.h"
#include "core/typedefs.h"
#include "core/version.h"

// Contracts
#include "contracts/input-manager.h"
#include "contracts/renderer.h"
#include "contracts/window.h"

// Controls and user inputs
#include "controls/base-input-manager.h"

// Game
#include "game/game.h"
