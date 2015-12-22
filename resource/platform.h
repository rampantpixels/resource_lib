/* platform.h  -  Resource library  -  Public Domain  -  2014 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform resource I/O library in C11 providing
 * basic resource loading, saving and streaming functionality for projects based
 * on our foundation library.
 *
 * The latest source code maintained by Rampant Pixels is always available at
 *
 * https://github.com/rampantpixels/render_lib
 *
 * The foundation library source code maintained by Rampant Pixels is always available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.
 *
 */

#pragma once

#include <foundation/platform.h>

#include <resource/types.h>

/*! Compute a resource platform compact identifier from a platform
declaration structure
\param declaration Declaration
\return Compact identifier */
RESOURCE_API uint64_t
resource_platform(const resource_platform_t declaration);

/*! Check if platform is equal or more specific than reference
\param platform Platform
\param reference Reference
\return true if platform is equal or more specific than reference, false if not */
RESOURCE_API bool
resource_platform_is_equal_or_more_specific(uint64_t platform, uint64_t reference);

/*! Gradual reduction of platform specification, by removing highest group
specifier.
\param platform Platform specifier
\return Reduced platform specifier */
RESOURCE_API uint64_t
resource_platform_reduce(uint64_t platform);
