#include "ps1/io/mdec/mdec.hpp"

#include "ps1/bus.hpp"
#include "utils/error.hpp"

uint32_t Mdec::readParameter() { // Pop the value
    if (dataIn.empty())
        return 0;

    uint32_t value = dataIn.front();
    dataIn.pop();

    return value;
}

uint32_t Mdec::getParameterCount() {
	uint8_t command = getCommand();

    switch (command) {
		case 0x00: return 0;
		case 0x01: return getNbParameterCommand1();
		case 0x02: return getNbParameterCommand2();
		case 0x03: return 32; // 64 halfwords
        default: return 0;
    }
}

int Mdec::decodeCommand() { // TODO: Only 3 commands
	uint32_t command = dataIn.front();

	switch (command) {
		case 0x00: return ERR_OK; // Does nothing (probably something with status register)
        case 0x01: return ERR_OK; // Do the command
        case 0x02: return ERR_OK; // Do the command
        case 0x03: return ERR_OK; // Do the command
        case 0x04: return ERR_OK; // Does nothing (same as 0)
        case 0x05: return ERR_OK; // Does nothing (same as 0)
        case 0x06: return ERR_OK; // Does nothing (same as 0)
        case 0x07: return ERR_OK; // Does nothing (same as 0)
	}

	return ERR_MDEC_COMMAND_NOT_FOUND;
}
