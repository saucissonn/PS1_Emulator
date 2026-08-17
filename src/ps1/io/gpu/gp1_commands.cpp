#include "ps1/io/gpu/gp1.hpp"

#include "utils/error.hpp"
#include "ps1/io/gpu/gpu.hpp"

int Gp1::resetCommandBuffer() {
	gpu->resetCommandBuffer();

	return ERR_OK;
}

int Gp1::acknowledgeGpuInterrupt() {
    gpu->setGpustatInterruptRequest(0);

    return ERR_OK;
}

int Gp1::decodeCommand() {
    switch (command) {
		case 0x01: return resetCommandBuffer();
		case 0x02: return acknowledgeGpuInterrupt();
		default: return ERR_GP1_COMMAND_NOT_FOUND;
    }
}
