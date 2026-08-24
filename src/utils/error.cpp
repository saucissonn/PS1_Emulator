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
            return "CPU instruction not found";

        case ERR_COP0_INSTRUCTION_NOT_FOUND:
            return "COP0 instruction not found";

        case ERR_COP2_COMMAND_NOT_FOUND:
            return "COP2 command not found";

        case ERR_GP0_COMMAND_NOT_FOUND:
            return "GP0 command not found";

        case ERR_GP1_COMMAND_NOT_FOUND:
            return "GP1 command not found";

		case ERR_CDROM_COMMAND_NOT_FOUND:
			return "CDROM command not found";

		case ERR_CDROM_NOT_ENOUGH_PARAMETERS:
			return "CDROM not enough parameters";

        case ERR_MDEC_COMMAND_NOT_FOUND:
            return "MDEC command not found";

        case ERR_MDEC_NOT_ENOUGH_PARAMETERS:
            return "MDEC not enough parameters";

        case ERR_WRITE_NOT_ALLOWED:
            return "write not allowed";

        case ERR_WRITE_SECTION_NOT_FOUND:
            return "write section not found";

        case ERR_WRITE_ADDRESS_NOT_ALIGNED:
            return "write address not aligned";

        case ERR_WRITE_SECTION_NOT_CONNECTED:
            return "write section not connected";

        case ERR_READ_NOT_ALLOWED:
            return "read not allowed";

        case ERR_READ_SECTION_NOT_FOUND:
            return "read section not found";

        case ERR_READ_ADDRESS_NOT_ALIGNED:
            return "read address not aligned";

        case ERR_READ_SECTION_NOT_CONNECTED:
            return "read section not connected";

		case ERR_BUS_SECTION_NOT_FOUND:
			return "bus section not found";

		case ERR_BUS_SECTION_NOT_CONNECTED:
			return "bus section not connected";

		case ERR_DMA_CHANNEL_NUMBER:
			return "wrong DMA channel";

        case ERR_DMA_WRITE:
            return "DMA write is not possible";

        case ERR_DMA_READ:
            return "DMA read is not possible";

		case ERR_TIMER0:
			return "something wrong with timer 0";

        case ERR_TIMER1:
            return "something wrong with timer 1";

        case ERR_TIMER2:
            return "something wrong with timer 2";

        case ERR_INTENTIONAL_STOP:
            return "intentional stop";

        default:
            return "unknown error";
    }
}
