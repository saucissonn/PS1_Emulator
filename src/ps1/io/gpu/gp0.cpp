#include "ps1/io/gpu/gp0.hpp"

#include <stdlib.h>

#include "ps1/io/gpu/gpu.hpp"

Gp0::Gp0(Gpu *gpu_) {
	gpu = gpu_;

	commandBufferMaxSize = 100;
	indexCommandBuffer = 0;
	commandBuffer = (uint32_t *)calloc(commandBufferMaxSize, sizeof(uint32_t));

	return;
}

Gp0::~Gp0() {
	free(commandBuffer);

	return;
}

uint32_t Gp0::read(uint32_t address) {
	return address; // TODO
}

void Gp0::write(uint32_t address, uint32_t value) {
    if (0x1F801814 != address || indexCommandBuffer >= commandBufferMaxSize) {
        return;
    }

	commandBuffer[indexCommandBuffer] = value;

	indexCommandBuffer += 1;
}
