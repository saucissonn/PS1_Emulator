#include "ps1/io/cdrom/cdrom.hpp"

#include "utils/error.hpp"

// Parameters

uint8_t Cdrom::readParameter() { // Pop the value
    if (parameters.empty())
        return 0;

    uint8_t value = parameters.front();
    parameters.pop();

    return value;
}

int Cdrom::writeParameter(uint8_t value) {
    switch (index) {
        case 0:
            parameters.push(value); // Parameter FIFO
			if (parameters.size() == getParameterCount(command)) { // If we write the last parameter we execute the command
				return decodeCommand();
			}
			
            return ERR_OK;

        case 1:
            interruptEnable = value;
            return ERR_OK;

        case 2:
            audioVolumeLeftToLeft = value;
            return ERR_OK;

        case 3:
            audioVolumeRightToLeft = value;
            return ERR_OK;
    }

    return ERR_UNEXPECTED_RESULT;
}

uint8_t Cdrom::getParameterCount(uint8_t command) {
    switch (command) {
        case 0x02: return 3; // Setloc
        case 0x03: return 1; // Play
        case 0x0D: return 2; // Setfilter
        case 0x0E: return 1; // Setmode
        case 0x12: return 1; // SetSession
        case 0x14: return 1; // GetTD
        case 0x19: return 1; // Test
        case 0x1F: return 6; // VideoCD
        default:   return 0;
    }
}
