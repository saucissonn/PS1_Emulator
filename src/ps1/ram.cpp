#include "ps1/ram.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <cstdio>

#include "utils/error.hpp"

Ram::Ram() {
	ramSize = 0x200000 + 4;
	ram = (uint8_t *)calloc(ramSize, sizeof(uint8_t));

	return;
}

Ram::~Ram() {
	free(ram);

	return;
}

uint32_t Ram::read(uint32_t address) {
    address &= 0x001FFFFF;

    uint32_t result = 0;

    result |= (uint32_t)ram[address]; // Little endian + 8 bits to 32 bits
    result |= ((uint32_t)ram[address + 1]) << 8;
    result |= ((uint32_t)ram[address + 2]) << 16;
    result |= ((uint32_t)ram[address + 3]) << 24;

    return result;
}

int Ram::write(uint32_t address, uint32_t value) {
    address &= 0x001FFFFF;

	printf("Local RAM address: %08X, value: %08X\n", address, value);

    ram[address] = (uint8_t)(value); // Little endian + 32 bits to 8 bits
    ram[address + 1] = (uint8_t)(value >> 8);
    ram[address + 2] = (uint8_t)(value >> 16);
    ram[address + 3] = (uint8_t)(value >> 24);

    return ERR_OK;
};
