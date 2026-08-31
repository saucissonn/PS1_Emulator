#pragma once

#include <cstdint>

class MemoryControl3;
class Bus;

class Ram {
	public:
		Ram();
		~Ram();

		int setBus(Bus *bus_);
		int setMemoryControl3(MemoryControl3 *memoryControl3_);

		uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);

	private:
		MemoryControl3 *memoryControl3;
		Bus *bus;

		uint32_t ramSize;
		uint8_t *ram;
        uint32_t scratchPadSize;
        uint8_t *scratchPad;
};
