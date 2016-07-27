/* remote.c  -  Resource library  -  Public Domain  -  2014 Mattias Jansson / Rampant Pixels
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

#include <resource/remote.h>

#include <foundation/foundation.h>

#if RESOURCE_ENABLE_REMOTE_SOURCED

static string_t _remote_sourced;

string_const_t
resource_remote_sourced(void) {
	return string_const(STRING_ARGS(_remote_sourced));
}

void
resource_remote_set_sourced(const char* url, size_t length) {
	string_deallocate(_remote_sourced.str);
	_remote_sourced = string_clone(url, length);
}

#endif

#if RESOURCE_ENABLE_REMOTE_COMPILED

static string_t _remote_compiled;

string_const_t
resource_remote_compiled(void) {
	return string_const(STRING_ARGS(_remote_compiled));
}

void
resource_remote_set_compiled(const char* url, size_t length) {
	string_deallocate(_remote_compiled.str);
	_remote_compiled = string_clone(url, length);
}

stream_t*
resource_remote_open_static(const uuid_t uuid, uint64_t platform) {
	FOUNDATION_UNUSED(uuid);
	FOUNDATION_UNUSED(platform);
	return 0;
}

stream_t*
resource_remote_open_dynamic(const uuid_t uuid, uint64_t platform) {
	FOUNDATION_UNUSED(uuid);
	FOUNDATION_UNUSED(platform);
	return 0;
}


#endif
