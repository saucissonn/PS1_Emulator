#include "ps1/io/gpu/gp0.hpp"

#include <stdlib.h>

#include "utils/error.hpp"
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

int Gp0::write(uint32_t value) { // When we write in GP0 it adds a command (value) to a buffer
	if (commandBufferIndex >= commandBufferMaxSize) { // Overflow (shouldn't happened)
		return ERR_OUT_OF_MEMORY;
	}

	commandBuffer[commandBufferIndex] = value; // Add the command to the buffer
	commandBufferIndex += 1;

	return decodeCommand(); // If something goes wrong the error is handled
}
