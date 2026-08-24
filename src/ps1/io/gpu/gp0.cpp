#include "ps1/io/gpu/gp0.hpp"

#include <stdlib.h>

#include "utils/error.hpp"
#include "ps1/io/gpu/gpu.hpp"
#include "ps1/bus.hpp"
#include "ps1/io/dma.hpp"

int Gp0::setBus(Bus *bus_) {
    if (!bus_) {
        return ERR_INVALID_ARGUMENT;
    }

    bus = bus_;

    return ERR_OK;
}

int Gp0::setDma(Dma *dma_) {
    if (!dma_) {
        return ERR_INVALID_ARGUMENT;
    }

    dma = dma_;

    return ERR_OK;
}

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

int Gp0::dmaWriteBlock() { // RAM -> GP0
    // DMA Channel 2, SyncMode = 1
    uint32_t bcr = dma->getBCR(2);
    uint32_t madr = dma->getMADR(2);
    uint8_t step = dma->getChannelMemoryAddressStep(2); // 1 or -1
    step *= 4; // 4 or -4

    uint32_t wordCount = bcr & 0x0000FFFF;
    uint32_t blockCount = (bcr >> 16) & 0xFFFF;;
    uint32_t stepCount = wordCount * blockCount;

    for (uint32_t i = 0; i < stepCount; i++) {
        uint32_t data = bus->read(madr);
        write(data);
        madr += step;
    }

    dma->setMADR(madr, 2);

    return ERR_OK;
}

int Gp0::dmaWriteLinkedList() { // RAM -> GP0
	// DMA Channel 2, SyncMode = 2
	uint32_t madr = dma->getMADR(2);

	while (madr < 0x00FFFFFF) {
		uint32_t header = bus->read(madr);

	    uint32_t count = header >> 24;
	    uint32_t next  = header & 0x00FFFFFF; 
		madr += 4;

		for (uint32_t i = 0; i < count; i++) {
			uint32_t command = bus->read(madr);
			write(command);
			madr += 4;
		}

		madr = next;
	}

    dma->setMADR(madr, 2);

    return ERR_OK;
}
