#pragma once

#include <cstdint>

class Gpu;
class Bus;
class Dma;

class Gp0 {
    public:
        Gp0(Gpu *gpu_);
        ~Gp0();

		int setBus(Bus *bus_);
		int setDma(Dma *dma_);

        uint32_t read();
		int write(uint32_t value);

		int dmaWriteBlock();
		int dmaWriteLinkedList();

		int decodeCommand();

		// Utils

		void setCommandBufferIndex(uint32_t value);
		void resetCommandBuffer();

    private:
		Gpu *gpu;
		Bus *bus;
		Dma *dma;

		uint32_t commandBufferMaxSize;
		uint32_t commandBufferIndex;
		uint32_t *commandBuffer;

		// Commands

		int NOP();
};
