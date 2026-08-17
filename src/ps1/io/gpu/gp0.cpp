#include "ps1/io/gpu/gp0.hpp"

#include <stdlib.h>

#include "ps1/io/gpu/gpu.hpp"

Gp0::Gp0(Gpu *gpu_) {
	gpu = gpu_;

	commandBufferMaxSize = 100;
	commandBufferIndex = 0;
	commandBuffer = (uint32_t *)calloc(commandBufferMaxSize, sizeof(uint32_t));

	return;
}

Gp0::~Gp0() {
	free(commandBuffer);

	return;
}

uint32_t Gp0::read() {
	return gpu->getGpuread(); // TODO
}

void Gp0::write(uint32_t value) {
    if (commandBufferIndex >= commandBufferMaxSize) {
        return;
    }

	commandBuffer[commandBufferIndex] = value;

	commandBufferIndex += 1;
}
