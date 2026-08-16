#pragma once

typedef enum {
	ERR_OK = 0,						// No error
	ERR_OUT_OF_MEMORY,				// Segfault
	ERR_FILE_NOT_FOUND,				// File not found
	ERR_INVALID_FORMAT,				// Invalid file format
	ERR_INVALID_ARGUMENT,			// Invalid argument (often when NULL)
	ERR_INVALID_TYPE,				// Invalid type
	ERR_UNEXPECTED_RESULT,			// When a value returned by a function isn't expected
	ERR_CPU_INSTRUCTION_NOT_FOUND,	// Cpu instruction not found
	ERR_COP0_INSTRUCTION_NOT_FOUND,	// Cop0 instruction not found
	ERR_GP0_COMMAND_NOT_FOUND,		// Gp0 command not found
	ERR_GP1_COMMAND_NOT_FOUND		// Gp1 command not found
} Error;

const char *error_string(int err);
