/**
 * This file provides information about the build,
 * such as whether whether the environment is DEBUG or RELEASE.
 *
 * @ref build-info
 */

#pragma once

#ifdef NDEBUG
    #define IS_DEBUG false
    #define IS_RELEASE true
#else
    #define IS_DEBUG true
    #define IS_RELEASE false
#endif
