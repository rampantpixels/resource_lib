/* errorcodes.h  -  Resource library  -  Public Domain  -  2015 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform resource I/O library in C11 providing
 * basic resource loading, saving and streaming functionality for projects based
 * on our foundation library.
 *
 * The latest source code maintained by Rampant Pixels is always available at
 *
 * https://github.com/rampantpixels/resource_lib
 *
 * The foundation library source code maintained by Rampant Pixels is always available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.
 *
 */

#pragma once

//Error codes returned by resource tool
#define RESOURCE_RESULT_OK                           0
#define RESOURCE_RESULT_INVALID_ARGUMENT            -1
#define RESOURCE_RESULT_UNKNOWN_COMMAND             -2
#define RESOURCE_RESULT_UNABLE_TO_OPEN_OUTPUT_FILE  -3
