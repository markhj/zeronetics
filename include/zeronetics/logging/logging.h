/**
 * Logging
 * This file is an extension of log, which provides macros
 * that can be used in place of the actual ZEN::Log class.
 * This provides you with an convenient way to optimize
 * the shipped code.
 *
 * The advantage of using macros such as ``ZEN_INFO`` is that
 * they can be completely stripped from the distribution build.
 *
 * @ref logging
 */

#pragma once

#include "log.h"
#include "zeronetics/core/build.h"

#define LOG_LEVEL_INFO IS_DEBUG

#if LOG_LEVEL_INFO
#define ZEN_INFO(message, category) ZEN::Log::info(message, category);
#else
#define ZEN_INFO(message, category)
#endif

#define ZEN_WARN(message, category) ZEN::Log::warn(message, category)
#define ZEN_CRITICAL(message) ZEN::Log::critical(message);
