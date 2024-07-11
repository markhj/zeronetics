/**
 * Zeronetics Engine - Primary Header File
 *
 * This header file provides a convenient access point to all
 * necessary features in Zeronetics, with the exception of modules.
 *
 * Modules must be included separately and on a per-need basis.
 */

#pragma once

// Library core: Fundamentals
#include "core/macros.h"
#include "core/typedefs.h"
#include "core/basic.h"
#include "core/engine-info.h"

// Library core: Higher level structures
#include "core/settings.h"
#include "core/controls.h"

// Library core: Controls and user inputs
#include "controls/base-input-manager.h"

// Game
#include "game/game.h"
