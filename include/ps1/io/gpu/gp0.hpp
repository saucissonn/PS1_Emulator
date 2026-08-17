#pragma once

#include <cstdint>

class Gpu;

class Gp0 {
    public:
        Gp0(Gpu *gpu_);
        ~Gp0();

        uint32_t read();
		int write(uint32_t value);

		int decodeCommand();

		// Utils

		void setCommandBufferIndex(uint32_t value);
		void resetCommandBuffer();

    private:
		Gpu *gpu;

		uint32_t commandBufferMaxSize;
		uint32_t commandBufferIndex;
		uint32_t *commandBuffer;

		// Commands

		int NOP();
};
