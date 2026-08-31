#include "ps1/ram.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <cstdio>

#include "ps1/io/memory_control/memory_control3.hpp"
#include "ps1/bus.hpp"
#include "ps1/cpu/cop0.hpp"
#include "utils/error.hpp"

int Ram::setBus(Bus *bus_) {
	if (!bus_) {
		return ERR_INVALID_ARGUMENT;
	}

	bus = bus_;

	 return ERR_OK;
}

int Ram::setMemoryControl3(MemoryControl3 *memoryControl3_) {
	if (!memoryControl3_) {
		return ERR_INVALID_ARGUMENT;
	}

	memoryControl3 = memoryControl3_;

	return ERR_OK;
}

Ram::Ram() {
	ramSize = 0x00800000;
	ram = (uint8_t *)calloc(ramSize, sizeof(uint8_t));

	scratchPadSize = 0x400;
	scratchPad = (uint8_t *)calloc(ramSize, sizeof(uint8_t));

	return;
}

Ram::~Ram() {
	free(ram);
	free(scratchPad);

	return;
}

uint32_t Ram::read(uint32_t address) {
    uint8_t segment = bus->getSegment(address);

    address &= 0x1FFFFFFF;

    if (0x1F800000 <= address && address <= 0x1F8003FF) { // Scratch Pad
        if (segment == KUSEG || segment == KSEG0) { // Has a scratchpad

            bool scratchpadEnabled =
                memoryControl3->getScratchpadEnable1() &&
                memoryControl3->getScratchpadEnable2();

            if (scratchpadEnabled) {
                address &= 0x3FF;

                uint32_t result = 0;

                result |= (uint32_t)scratchPad[address];
                result |= ((uint32_t)scratchPad[address + 1]) << 8;
                result |= ((uint32_t)scratchPad[address + 2]) << 16;
                result |= ((uint32_t)scratchPad[address + 3]) << 24;

                return result;
            }
            else {
                address &= 0x001FFFFF;

                uint32_t result = 0;

                result |= (uint32_t)ram[address];
                result |= ((uint32_t)ram[address + 1]) << 8;
                result |= ((uint32_t)ram[address + 2]) << 16;
                result |= ((uint32_t)ram[address + 3]) << 24;

                uint32_t offset = address & 0x3FF; // Miss fill

                scratchPad[offset]     = (uint8_t)(result);
                scratchPad[offset + 1] = (uint8_t)(result >> 8);
                scratchPad[offset + 2] = (uint8_t)(result >> 16);
                scratchPad[offset + 3] = (uint8_t)(result >> 24);

                return result;
            }
        }
        else {
            bus->setBusError(ERR_READ_SECTION_NOT_FOUND);
            return 0;
        }
    }

    address &= 0x001FFFFF;

    uint32_t result = 0;

    result |= (uint32_t)ram[address];
    result |= ((uint32_t)ram[address + 1]) << 8;
    result |= ((uint32_t)ram[address + 2]) << 16;
    result |= ((uint32_t)ram[address + 3]) << 24;

    return result;
}


int Ram::write(uint32_t address, uint32_t value) {
    uint8_t segment = bus->getSegment(address);

    address &= 0x1FFFFFFF;

    if (0x1F800000 <= address && address <= 0x1F8003FF) { // Scratch Pad
        if (segment == KUSEG || segment == KSEG0) { // Has a scratchpad

            bool scratchpadEnabled =
                memoryControl3->getScratchpadEnable1() &&
                memoryControl3->getScratchpadEnable2();

            if (scratchpadEnabled) {
                address &= 0x3FF;

                scratchPad[address]     = (uint8_t)(value);
                scratchPad[address + 1] = (uint8_t)(value >> 8);
                scratchPad[address + 2] = (uint8_t)(value >> 16);
                scratchPad[address + 3] = (uint8_t)(value >> 24);

                return ERR_OK;
            }
        }
        else {
            bus->setBusError(ERR_WRITE_SECTION_NOT_FOUND);
            return ERR_WRITE_SECTION_NOT_FOUND;
        }
    }

    address &= 0x001FFFFF;

    printf("Local RAM address: %08X, value: %08X\n", address, value);

    ram[address]     = (uint8_t)(value);
    ram[address + 1] = (uint8_t)(value >> 8);
    ram[address + 2] = (uint8_t)(value >> 16);
    ram[address + 3] = (uint8_t)(value >> 24);

    return ERR_OK;
}
