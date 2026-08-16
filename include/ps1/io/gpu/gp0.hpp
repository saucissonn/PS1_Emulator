#pragma once

#include <cstdint>

class Gpu;

class Gp0 {
    public:
        Gp0(Gpu *gpu_);
        ~Gp0();

        uint32_t read(uint32_t address);
        void write(uint32_t address, uint32_t value);

		int decodeCommand(uint32_t command);

    private:
		Gpu *gpu;

		uint32_t commandBufferMaxSize;
		uint32_t indexCommandBuffer;
		uint32_t *commandBuffer;
};
