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

		default:
			return "unknown error";
	}
}
