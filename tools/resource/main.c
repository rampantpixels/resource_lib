/* main.c  -  Resource library  -  Public Domain  -  2014 Mattias Jansson / Rampant Pixels
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

#include <foundation/foundation.h>
#include <resource/resource.h>

#include "errorcodes.h"

typedef struct {
	bool              display_help;
	int               binary;
	string_const_t    path;
	string_const_t    key;
	string_const_t    value;
} resource_input_t;

static resource_input_t
resource_parse_command_line(const string_const_t* cmdline);

static void
resource_print_usage(void);

int
main_initialize(void) {
	int ret = 0;
	application_t application;
	foundation_config_t foundation_config;
	resource_config_t resource_config;

	memset(&foundation_config, 0, sizeof(foundation_config));
	memset(&resource_config, 0, sizeof(resource_config));

	memset(&application, 0, sizeof(application));
	application.name = string_const(STRING_CONST("resource"));
	application.short_name = string_const(STRING_CONST("resource"));
	application.config_dir = string_const(STRING_CONST("resource"));
	application.flags = APPLICATION_UTILITY;

	log_enable_prefix(false);
	log_set_suppress(0, ERRORLEVEL_ERROR);

	if ((ret = foundation_initialize(memory_system_malloc(), application, foundation_config)) < 0)
		return ret;
	if ((ret = resource_module_initialize(resource_config)) < 0)
		return ret;

	return 0;
}

int
main_run(void* main_arg) {
	int result = RESOURCE_RESULT_OK;
	resource_source_t source;
	stream_t* stream;
	bool binary = false;
	resource_input_t input = resource_parse_command_line(environment_command_line());

	FOUNDATION_UNUSED(main_arg);

	resource_source_initialize(&source);

	if (input.display_help) {
		resource_print_usage();
		goto exit;
	}

	log_infof(HASH_RESOURCE, STRING_CONST("Set '%.*s' to '%.*s' in '%.*s'"),
	          STRING_FORMAT(input.key), STRING_FORMAT(input.value), STRING_FORMAT(input.path));

	stream = stream_open(STRING_ARGS(input.path), STREAM_IN);
	if (stream) {
		stream_determine_binary_mode(stream, 16);
		binary = stream_is_binary(stream);
		log_infof(HASH_RESOURCE, STRING_CONST("Input file is %s"), binary ? "binary" : "ascii");
		stream_seek(stream, 0, STREAM_SEEK_BEGIN);
		resource_source_read(&source, stream);
		stream_deallocate(stream);
	}

	resource_source_set(&source, time_system(), hash(STRING_ARGS(input.key)), STRING_ARGS(input.value));

	stream = stream_open(STRING_ARGS(input.path), STREAM_OUT | STREAM_CREATE | STREAM_TRUNCATE);
	if (stream) {
		if (input.binary)
			binary = (input.binary > 0);
		log_infof(HASH_RESOURCE, STRING_CONST("Output file is %s"), binary ? "binary" : "ascii");
		stream_set_binary(stream, binary);
		resource_source_write(&source, stream);
		stream_deallocate(stream);
	}

exit:

	resource_source_finalize(&source);

	return result;
}

void
main_finalize(void) {
	resource_module_finalize();
	foundation_finalize();
}

resource_input_t
resource_parse_command_line(const string_const_t* cmdline) {
	resource_input_t input;
	size_t arg, asize;

	memset(&input, 0, sizeof(input));

	error_context_push(STRING_CONST("parsing command line"), STRING_CONST(""));
	for (arg = 1, asize = array_size(cmdline); arg < asize; ++arg) {
		if (string_equal(STRING_ARGS(cmdline[arg]), STRING_CONST("--help")))
			input.display_help = true;
		else if (string_equal(STRING_ARGS(cmdline[arg]), STRING_CONST("--file"))) {
			if (arg < asize - 1)
				input.path = cmdline[++arg];
		}
		else if (string_equal(STRING_ARGS(cmdline[arg]), STRING_CONST("--set"))) {
			if (arg < asize - 2) {
				input.key = cmdline[++arg];
				input.value = cmdline[++arg];
			}
		}
		else if (string_equal(STRING_ARGS(cmdline[arg]), STRING_CONST("--binary"))) {
			input.binary = 1;
		}
		else if (string_equal(STRING_ARGS(cmdline[arg]), STRING_CONST("--ascii"))) {
			input.binary = -1;
		}
		else if (string_equal(STRING_ARGS(cmdline[arg]), STRING_CONST("--debug"))) {
			log_set_suppress(0, ERRORLEVEL_NONE);
		}
		else if (string_equal(STRING_ARGS(cmdline[arg]), STRING_CONST("--")))
			break; //Stop parsing cmdline options
		else {
			//Unknown argument, display help
			input.display_help = true;
		}
	}
	error_context_pop();

	if (!input.path.length || !input.key.length)
		input.display_help = true;

	return input;
}

static void
resource_print_usage(void) {
	const error_level_t saved_level = log_suppress(0);
	log_set_suppress(0, ERRORLEVEL_DEBUG);
	log_info(0, STRING_CONST(
	             "resource usage:\n"
	             "  resource --file <path> --set <key> <value> [--debug] [--help] [--]\n"
	             "    Arguments:\n"
	             "      --file <path>                Operate on resource file given by <path>\n"
	             "      --set <key> <value>          Set <key> to <value> in resource\n"
	             "    Optional arguments:\n"
	             "      --binary                     Write binary file\n"
	             "      --ascii                      Write ASCII file (default)\n"
	             "      --debug                      Enable debug output\n"
	             "      --help                       Display this help message\n"
	             "      --                           Stop processing command line arguments"
	         ));
	log_set_suppress(0, saved_level);
}