#include "ps1/ram.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <cstdio>

#include "utils/error.hpp"

Ram::Ram() {
	ramSize = 0x200000;
	ram = (uint8_t *)calloc(0x200000, sizeof(uint8_t));

	return;
}

Ram::~Ram() {
	free(ram);

	return;
}

uint32_t Ram::read(uint32_t address) {
	uint32_t result = 0;

	result |= (uint32_t)ram[address];
	result |= (uint32_t)(ram[address + 1] << 8);
	result |= (uint32_t)(ram[address + 2] << 16);
	result |= (uint32_t)(ram[address + 3] << 24);

	return result;
}

int Ram::write(uint32_t address, uint32_t value) {
	ram[address] = value;

	return ERR_OK;
}
