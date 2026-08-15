#include "ps1/bus.hpp"

#include <stdio.h>
#include <stdlib.h>


int Bus::setCpu(Cpu *cpu_) {
	cpu = cpu_;

	return 0;
}

int Bus::setBios(Bios *bios_) {
	bios = bios_;

	return 0;
}

Bus::Bus() {
	expansionRegion1Size = 0x80100; // Temporarly here, maybe not here later on (for all regions)
	memoryControl1Size = 36;
	periphericalIOPortsSize = 32;
	memoryControl2Size = 4;
    expansionRegion2Size = 80;
	expansionRegion3Size = 0x200000;
	memoryControl3Size = 4;

	return;
}

Bus::~Bus() {
    return;
}

uint32_t Bus::read(uint32_t address) {
	if (0x1FC00000 <= address && address <= 0x1FC7FFFF) { // BIOS Region
		address -= 0x1FC00000;
		return bios->read(address);
	}

	return 0;
}

int Bus::write(uint32_t address, uint32_t value) {
    if (0x1FC00000 <= address && address <= 0x1FC7FFFF) { // BIOS Region
        address -= 0x1FC00000;
		bios->write(address, value);
		return 0;
    }

    return 0;
}

Mem Bus::getMemoryHardware(uint32_t physicalAddr){
    if      (0x00000000 < physicalAddr && physicalAddr < 0x001FFFFF) return Mem::MAIN_RAM;
    else if (0x1F000000 < physicalAddr && physicalAddr < 0x1F7FFFFF) return Mem::EXPANSION_REGION_1;
    else if (0x1F800000 < physicalAddr && physicalAddr < 0x1F8003FF) return Mem::SCRATCHPAD;
    else if (0x1F801000 < physicalAddr && physicalAddr < 0x1F802FFF) return Mem::IO_PORTS;
    else if (0x1F802000 < physicalAddr && physicalAddr < 0x1F803FFF) return Mem::EXPANSION_REGION_2;
    else if (0x1FA00000 < physicalAddr && physicalAddr < 0x1FBFFFFF) return Mem::EXPANSION_REGION_3;
    else if (0x1FC00000 < physicalAddr && physicalAddr < 0x1FC7FFFF) return Mem::BIOS_ROM;
    else if (0xFFFE0000 < physicalAddr && physicalAddr < 0xFFFE01FF) return Mem::CACHE_CONTROL;
    else{
        printf("Error: getHardware, the physical address given (%d) doesn't match any existing component\n", physicalAddr);
        return Mem::INVALID_COMPONENT;
    }
}
