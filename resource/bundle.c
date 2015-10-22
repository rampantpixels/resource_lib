/* bundle.c  -  Resource library  -  Public Domain  -  2014 Mattias Jansson / Rampant Pixels
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

#include <resource/bundle.h>

#include <foundation/foundation.h>

int 
resource_bundle_load( uuid_t bundle )
{
#if RESOURCE_ENABLE_REMOTE_SOURCE
	if (_resource_config.enable_remote_source) {
	}
#endif
	
#if RESOURCE_ENABLE_LOCAL_SOURCE
	if (_resource_config.enable_local_source) {
	}
#endif
	
	return 0;
}
