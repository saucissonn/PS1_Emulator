#pragma once

#include <cstdint>

class Bios {
	public:
		Bios();
		~Bios();

		int load(const char *filename);
		uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);

	private:
		uint32_t biosRomSize;
		uint8_t *biosRom;
};
