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
	expansionRegion1Size = 0x80100;
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
