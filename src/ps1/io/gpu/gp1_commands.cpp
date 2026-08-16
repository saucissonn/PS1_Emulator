#include "ps1/io/gpu/gp1.hpp"

#include "utils/error.hpp"

int Gp1::decodeCommand(uint32_t command) {
    if (command) {
        return ERR_GP1_COMMAND_NOT_FOUND;
    }

    return ERR_GP1_COMMAND_NOT_FOUND;
}
