#pragma once

#include <cstdint>
#include <stdlib.h>

class Gpu {
	public:
		Gpu();
		~Gpu();

		uint32_t read(uint32_t address);
		void write(uint32_t address, uint32_t value);

	private:
		uint32_t vramSize;
		uint8_t *vram;
};
