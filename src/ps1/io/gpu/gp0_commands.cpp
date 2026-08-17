#include "ps1/io/gpu/gp0.hpp"

#include "utils/error.hpp"

int Gp0::NOP() {
	return ERR_OK;
}

int Gp0::decodeCommand() {
	uint8_t command = commandBuffer[0] >> 24; // Tells how much commands are needed to execute the command
	// uint32_t parameter = commandBuffer[0] & 0x00FFFFFF; // Can add additional info about the number of command

	if (command == 0x00) {
		if (commandBufferIndex == 1) { // If we have the right amount of commands we execute the command
			resetCommandBuffer();
			return NOP();
		}
		return ERR_OK;
	}

	else if (command == 0x01) {
		if (commandBufferIndex == 1) {
			resetCommandBuffer();
		}
	}

	else if (command == 0x02) {
		if (commandBufferIndex == 3) {
			resetCommandBuffer();
		}
	}

	else if (command == 0x03) {
		if (commandBufferIndex == 1) {
			resetCommandBuffer();
		}
	}

	else if (0x04 <= command && command <= 0x1E) {
        if (commandBufferIndex == 1) {
            resetCommandBuffer();
            return NOP();
        }
        return ERR_OK;
	}

    else if (command == 0x1F) {
        if (commandBufferIndex == 1) {
            resetCommandBuffer();
        }
    }

    else if (0x20 <= command && command <= 0x7F) {
        if (commandBufferIndex == 1) {
            resetCommandBuffer();
        }
    }

    else if (command == 0x80) {
        if (commandBufferIndex == 4) {
            resetCommandBuffer();
        }
    }

    else if (0x81 <= command && command <= 0xDF) {
        if (commandBufferIndex == 1) {
            resetCommandBuffer();
        }
    }

    else if (0xE1 <= command && command <= 0xE6) {
        if (commandBufferIndex == 1) {
            resetCommandBuffer();
        }
    }

	return ERR_GP0_COMMAND_NOT_FOUND;
}
