#include "ps1/io/cdrom/cdrom.hpp"

#include "utils/error.hpp"
#include "ps1/io/interrupt_controller.hpp"

// Commands

int Cdrom::raiseInterrupt(CdromInterrupt type) { // Every commands with an INT response should end with that
    interruptFlag = (uint8_t)type;
	interruptController->request(Interrupt::CDROM);
	
	return ERR_OK;
}

int Cdrom::decodeCommand() { // Also execute
    uint8_t count = getParameterCount(command);

    if (parameters.size() < count)
        return ERR_CDROM_NOT_ENOUGH_PARAMETERS;

    switch (command) {
        case 0x00: return ERR_CDROM_COMMAND_NOT_FOUND; // Invalid Command ?
        case 0x01: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x02: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x03: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x04: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x05: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x06: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x07: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x08: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x09: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0A: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0B: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0C: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0D: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0E: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0F: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x10: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x11: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x12: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x13: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x14: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x15: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x16: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x17: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x18: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x19: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1A: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1B: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1C: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1D: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1E: return ERR_CDROM_COMMAND_NOT_FOUND;

        case 0x50: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x51: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x52: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x53: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x54: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x55: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x56: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x57: return ERR_CDROM_COMMAND_NOT_FOUND;
    }

    if (0x1F <= command && command <= 0x4F)
        return ERR_CDROM_COMMAND_NOT_FOUND;

    if (0x58 <= command && command <= 0x5F)
        return ERR_CDROM_COMMAND_NOT_FOUND;

    if (0x6F <= command)
        return ERR_CDROM_COMMAND_NOT_FOUND;

    return ERR_CDROM_COMMAND_NOT_FOUND;
}

int Cdrom::writeCommand(uint8_t value) {
	switch (index) {
		case 0:
			command = value;
			if (getParameterCount(command) == 0) { // If no parameter we directly execute the command
				return decodeCommand();
			}

			return ERR_OK;

		case 1:
			return ERR_OK; // Unknown/unused

		case 2:
			return ERR_OK; // Unknown/unused

		case 3:
			audioVolumeRightToRight = value;
			return ERR_OK;
	}

	return ERR_UNEXPECTED_RESULT;
}
