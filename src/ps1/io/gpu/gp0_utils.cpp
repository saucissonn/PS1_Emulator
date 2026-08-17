#include "ps1/io/gpu/gp0.hpp"

void Gp0::setCommandBufferIndex(uint32_t value) {
	commandBufferIndex = value;
}

void Gp0::resetCommandBuffer() {
    commandBufferIndex = 0;

	for (uint32_t i = 0; i < commandBufferMaxSize; i++) {
		commandBuffer[i] = 0;
	}
}

