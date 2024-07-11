/**
 * Zeronetics Engine - Primary Header File
 *
 * This header file provides a convenient access point to all
 * necessary features in Zeronetics, with the exception of modules.
 *
 * Modules must be included separately and on a per-need basis.
 */

#pragma once

// Fundamentals
#include "core/engine-info.h"
#include "core/macros.h"
#include "core/typedefs.h"
#include "core/version.h"

// Contracts
#include "contracts/contracts.h"

// Controls and user inputs
#include "controls/base-input-manager.h"
#include "controls/controls.h"

// Game
#include "game/game.h"
#include "zeronetics/core/settings.h"
