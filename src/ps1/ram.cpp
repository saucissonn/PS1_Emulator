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
	return ram[address];
}

void Ram::write(uint32_t address, uint32_t value) {
	ram[address] = value;
}
