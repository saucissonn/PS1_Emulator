#pragma once

#include <cstdint>

class Gpu;

class Gp1 {
    public:
        Gp1(Gpu *gpu_);
        ~Gp1();

        uint32_t read(uint32_t address);
        void write(uint32_t address, uint32_t value);

		int decodeCommand(uint32_t command);

	private:
		Gpu *gpu;

		uint32_t instruction;
};
