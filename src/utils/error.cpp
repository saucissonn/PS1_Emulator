#include "utils/error.hpp"

const char *error_string(Error err)
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

		default:
			return "unknown error";
	}
}
