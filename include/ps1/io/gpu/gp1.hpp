#pragma once

#include <cstdint>

class Gpu;

class Gp1 {
    public:
        Gp1(Gpu *gpu_);
        ~Gp1();

        uint32_t read();
        void write(uint32_t value);

		int decodeCommand();

	private:
		Gpu *gpu;

		uint8_t command;
		uint32_t parameter;

		// Commands

		int resetCommandBuffer();
		int acknowledgeGpuInterrupt();
};
