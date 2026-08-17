#include "utils/error.hpp"

const char *error_string(int err)
{
	switch(err)
	{
		case ERR_OK:
			return "success";

		case ERR_OUT_OF_MEMORY:
			return "out of memory";

		case ERR_FILE_NOT_FOUND:
			return "file not found";

		case ERR_INVALID_FORMAT:
			return "invalid format";

        case ERR_INVALID_ARGUMENT:
            return "invalid argument";

        case ERR_INVALID_TYPE:
            return "invalid type";

        case ERR_UNEXPECTED_RESULT:
            return "unexpected result";

		case ERR_CPU_INSTRUCTION_NOT_FOUND:
			return "cpu instruction not found";

        case ERR_COP0_INSTRUCTION_NOT_FOUND:
            return "cop0 instruction not found";

		case ERR_GP0_COMMAND_NOT_FOUND:
			return "gp0 command not found";

        case ERR_GP1_COMMAND_NOT_FOUND:
            return "gp1 command not found";

		case ERR_WRITE_NOT_ALLOWED:
			return "write not allowed";

        case ERR_WRITE_SECTION_NOT_FOUND:
            return "write section not found";

		case ERR_INTENTIONAL_STOP:
			return "intentional stop";

		default:
			return "unknown error";
	}
}
