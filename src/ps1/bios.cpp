#include "ps1/bios.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <cstdio>

#include "utils/error.hpp"

Bios::Bios() {
	biosRomSize = 0x200000;
	biosRom = (uint8_t *)calloc(biosRomSize, sizeof(uint8_t));

	return;
}

Bios::~Bios() {
	free(biosRom);

	return;
}

int Bios::load(const char *filename) {
	std::FILE *file;

	file = fopen(filename, "r");

	if (!file) {
		printf("Error: Bios::Load, Can't read this file\n");
		return ERR_FILE_NOT_FOUND;
	}

	fseek(file, 0, SEEK_END); // Get the file size
	long int size = ftell(file);
	rewind(file);

	fread(biosRom, sizeof(uint8_t), size, file);
/*	// To debug
	for (int i = 0; i < size && i < 1000; i++) {
		printf("%3d: %8X\n", i, biosRom[i]);
	}
*/
	fclose(file);

	return ERR_OK;
}

uint32_t Bios::read(uint32_t address) { // Return a 32 bit value at address
	uint32_t result = 0;

	address -= 0x1FC00000;

	result |= (uint32_t)biosRom[address];
    result |= (uint32_t)(biosRom[address + 1] << 8);
    result |= (uint32_t)(biosRom[address + 2] << 16);
    result |= (uint32_t)(biosRom[address + 3] << 24);

	return result;
}
