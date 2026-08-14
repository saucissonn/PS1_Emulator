#pragma once

#include <cstdint>

class Bios {
	public:
		Bios();
		~Bios();

		int load(const char *filename);
		uint32_t read(uint32_t address);

	private:
		uint32_t biosRomSize;
		uint8_t *biosRom;
};
