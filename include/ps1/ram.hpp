#pragma once

#include <cstdint>

class Ram {
	public:
		Ram();
		~Ram();

		uint32_t read(uint32_t address);

		void write(uint32_t address, uint32_t value);

	private:
		uint32_t ramSize;
		uint8_t *ram;
};
