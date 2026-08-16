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

int Bus::setRam(Ram *ram_) {
	ram = ram_;

	return 0;
}

int Bus::setIo(Io *io_) {
	io = io_;

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

Mem Bus::getMemoryHardware(uint32_t physicalAddr) {
    if      (physicalAddr <= 0x001FFFFF) return Mem::MAIN_RAM;
    else if (0x1F000000 <= physicalAddr && physicalAddr <= 0x1F7FFFFF) return Mem::EXPANSION_REGION_1;
    else if (0x1F800000 <= physicalAddr && physicalAddr <= 0x1F8003FF) return Mem::SCRATCHPAD;
    else if (0x1F801000 <= physicalAddr && physicalAddr <= 0x1F802FFF) return Mem::IO_PORTS;
    else if (0x1F802000 <= physicalAddr && physicalAddr <= 0x1F803FFF) return Mem::EXPANSION_REGION_2;
    else if (0x1FA00000 <= physicalAddr && physicalAddr <= 0x1FBFFFFF) return Mem::EXPANSION_REGION_3;
    else if (0x1FC00000 <= physicalAddr && physicalAddr <= 0x1FC7FFFF) return Mem::BIOS_ROM;
    else if (0xFFFE0000 <= physicalAddr && physicalAddr <= 0xFFFE01FF) return Mem::CACHE_CONTROL;
    else {
        printf("Error: getMemoryHardware, the physical address given (%8X) doesn't match any existing component\n", physicalAddr);
        return Mem::INVALID_COMPONENT;
    }
}

uint32_t Bus::read(uint32_t address) {
    Mem section = getMemoryHardware(address);

    switch (section) {
        case Mem::MAIN_RAM: {
            return ram->read(address);
		}

        case Mem::EXPANSION_REGION_1: {
            printf("Read memory in expansion region 1\n");
            return 0;
		}

        case Mem::SCRATCHPAD: {
            return 0;
		}

        case Mem::IO_PORTS: {
            return io->read(address);
		}

        case Mem::EXPANSION_REGION_2: {
            printf("Read memory in expansion region 2\n");
            return 0;
		}

        case Mem::EXPANSION_REGION_3: {
            printf("Read memory in expansion region 3\n");
            return 0;
		}

        case Mem::BIOS_ROM: {
            return bios->read(address);
		}

        case Mem::CACHE_CONTROL: {
            return 0;
		}

		default: {
            printf("Error: invalid memory component\n");
            return 0;
		}
    }
}

int Bus::write(uint32_t address, uint32_t value) {
    Mem section = getMemoryHardware(address);

    switch (section) {
        case Mem::MAIN_RAM: {
            ram->write(address, value);
            return 0;
        }

        case Mem::EXPANSION_REGION_1: {
            printf("Write memory in expansion region 1\n");
            return 0;
        }

        case Mem::SCRATCHPAD: {
            return 0;
        }

        case Mem::IO_PORTS: {
            io->write(address, value);
			return 0;
		}

        case Mem::EXPANSION_REGION_2: {
            printf("Write memory in expansion region 2\n");
            return 0;
        }

        case Mem::EXPANSION_REGION_3: {
            printf("Write memory in expansion region 3\n");
            return 0;
        }

        case Mem::BIOS_ROM: {
            printf("Error: cannot write to BIOS ROM\n");
            return 0;
        }

        case Mem::CACHE_CONTROL: {
            return 0;
        }

        default: {
            printf("Error: invalid memory component\n");
            return 0;
        }
    }
}
