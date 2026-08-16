#include "ps1/io/gpu/gp0.hpp"

#include "utils/error.hpp"

int Gp0::decodeCommand(uint32_t command) {
	if (command) {
		return ERR_GP0_COMMAND_NOT_FOUND;
	}

	return ERR_GP0_COMMAND_NOT_FOUND;
}
