#include "ps1/bus.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "ps1/expansion.hpp"
#include "utils/error.hpp"

int Bus::setCpu(Cpu *cpu_) {
	if (!cpu_) {
		return ERR_INVALID_ARGUMENT;
	}
	cpu = cpu_;

	return ERR_OK;
}

int Bus::setBios(Bios *bios_) {
    if (!bios_) {
        return ERR_INVALID_ARGUMENT;
    }
    bios = bios_;

    return ERR_OK;
}

int Bus::setRam(Ram *ram_) {
    if (!ram_) {
        return ERR_INVALID_ARGUMENT;
    }
    ram = ram_;

    return ERR_OK;
}

int Bus::setIo(Io *io_) {
    if (!io_) {
        return ERR_INVALID_ARGUMENT;
    }
    io = io_;

    return ERR_OK;
}

int Bus::setExpansion1(ExpansionRegion1 *expansion1_) {
    if (!expansion1_) {
        return ERR_INVALID_ARGUMENT;
    }
    expansion1 = expansion1_;

    return ERR_OK;
}

int Bus::setExpansion2(ExpansionRegion2 *expansion2_) {
    if (!expansion2_) {
        return ERR_INVALID_ARGUMENT;
    }
    expansion2 = expansion2_;

    return ERR_OK;
}

int Bus::setExpansion3(ExpansionRegion3 *expansion3_) {
    if (!expansion3_) {
        return ERR_INVALID_ARGUMENT;
    }
    expansion3 = expansion3_;

    return ERR_OK;
}

Bus::Bus() {
	busError = ERR_OK;

	return;
}

Bus::~Bus() {
    return;
}

Mem Bus::getMemoryHardware(uint32_t physicalAddr) {
	//printf("physical address: %08X\n", physicalAddr);

    if (physicalAddr <= 0x001FFFFF)
		return Mem::MAIN_RAM;

    else if (0x1F000000 <= physicalAddr && physicalAddr <= 0x1F7FFFFF && (expansion1->getConnected() == 1))
		return Mem::EXPANSION_REGION_1;

    else if (0x1F800000 <= physicalAddr && physicalAddr <= 0x1F8003FF)
		return Mem::SCRATCHPAD;

    else if (0x1F801000 <= physicalAddr && physicalAddr <= 0x1F801FFF)
		return Mem::IO_PORTS;

    else if (0x1F802000 <= physicalAddr && physicalAddr <= 0x1F803FFF && (expansion2->getConnected() == 1))
		return Mem::EXPANSION_REGION_2;

    else if (0x1FA00000 <= physicalAddr && physicalAddr <= 0x1FBFFFFF && (expansion3->getConnected() == 1))
		return Mem::EXPANSION_REGION_3;

    else if (0x1FC00000 <= physicalAddr && physicalAddr <= 0x1FC7FFFF)
		return Mem::BIOS_ROM;

    else if (0xFFFE0000 <= physicalAddr && physicalAddr <= 0xFFFE01FF) 
		return Mem::CACHE_CONTROL;

    else if ((0x1FC80000 <= physicalAddr && physicalAddr <= 0xFFFDFFFF) || 0xFFFE0200 <= physicalAddr) {
        printf("Error: getMemoryHardware, the physical address given (%8X) doesn't match any existing component\n", physicalAddr);
		busError = ERR_BUS_SECTION_NOT_FOUND;
        return Mem::INVALID_COMPONENT;
    }

	else {
        printf("Error: getMemoryHardware, the physical address given (%8X) doesn't match any connected component\n", physicalAddr);
		busError = ERR_BUS_SECTION_NOT_CONNECTED;
        return Mem::INVALID_COMPONENT;
	}
}

uint32_t Bus::read(uint32_t address) {
    if (address % 4 != 0){
        printf("Error: read, the address %8X is not a multiple of 4\n", address);
        busError = ERR_READ_ADDRESS_NOT_ALIGNED;
        return ERR_READ_ADDRESS_NOT_ALIGNED;
    }

    uint32_t physicalAddress = cpu->convertAddress(address);

    Mem section = getMemoryHardware(physicalAddress);

    switch (section) {
        case Mem::MAIN_RAM:				return ram->read(address);
        case Mem::EXPANSION_REGION_1:	return expansion1->read(address);
        case Mem::SCRATCHPAD:			return 0;
        case Mem::IO_PORTS:				return io->read(address);
        case Mem::EXPANSION_REGION_2:	return expansion2->read(address);
        case Mem::EXPANSION_REGION_3:	return expansion3->read(address);
        case Mem::BIOS_ROM:				return bios->read(address);
        case Mem::CACHE_CONTROL:		return io->read(address);

		default:
            printf("Error: invalid memory component\n");
			if (busError == ERR_BUS_SECTION_NOT_FOUND) { // Convert general error to spesific error
				busError = ERR_READ_SECTION_NOT_FOUND;
			}
            if (busError == ERR_BUS_SECTION_NOT_CONNECTED) {
				busError = ERR_READ_SECTION_NOT_CONNECTED;
			}

	        return 0;
    }
}

int Bus::write(uint32_t address, uint32_t value) {
    if (address % 4 != 0){
        printf("Error: write, the address %8X is not a multiple of 4\n", address);
        busError = ERR_WRITE_ADDRESS_NOT_ALIGNED;
        return ERR_WRITE_ADDRESS_NOT_ALIGNED;
    }

	uint32_t physicalAddress = cpu->convertAddress(address);

    Mem section = getMemoryHardware(physicalAddress);

    switch (section) {
        case Mem::MAIN_RAM:				return ram->write(address, value);
        case Mem::EXPANSION_REGION_1:	return expansion1->write(address, value);
        case Mem::SCRATCHPAD:			return ERR_WRITE_SECTION_NOT_FOUND;
        case Mem::IO_PORTS:				return io->write(address, value);
        case Mem::EXPANSION_REGION_2:	return expansion2->write(address, value);
        case Mem::EXPANSION_REGION_3:	return expansion3->write(address, value);
        case Mem::BIOS_ROM:				return ERR_WRITE_NOT_ALLOWED;
        case Mem::CACHE_CONTROL:		return io->write(address, value);

        default:
            if (busError == ERR_BUS_SECTION_NOT_FOUND) { // Convert general error to spesific error
                busError = ERR_WRITE_SECTION_NOT_FOUND;
            }
            if (busError == ERR_BUS_SECTION_NOT_CONNECTED) {
                busError = ERR_WRITE_SECTION_NOT_CONNECTED;
            }

			return ERR_WRITE_SECTION_NOT_FOUND;
    }
}

int Bus::write16(uint32_t address, uint16_t value){ // address is a multiple of 2
    int miniOffset = address % 4;
    uint32_t temp = read(address - miniOffset) ; // multiple of 4

    if (busError != ERR_OK){
        printf("Error: write16, impossible to read address %8X\n", address);
        return busError;
    }

    if (miniOffset == 0){
        temp &= 0x0000FFFF;
        temp |= value << 16;
    }
    else if (miniOffset == 2){
        temp &= 0xFFFF0000;
        temp |= value;
    }
    else {
        printf("Error: write16, the address %8X is not a multiple of 2\n", address);
        busError = ERR_WRITE_ADDRESS_NOT_ALIGNED;
        return ERR_WRITE_ADDRESS_NOT_ALIGNED;
    }

    return write(address-miniOffset, temp);
}

int Bus::write8Only(uint32_t address, uint8_t value) { // Some rare address can only be written in 8 bits
    uint32_t physicalAddress = cpu->convertAddress(address);

    Mem section = getMemoryHardware(physicalAddress);

    switch (section) {
		case Mem::IO_PORTS: return io->write8Only(address, value);
		default:			return ERR_WRITE_SECTION_NOT_FOUND;
    }
}

int Bus::write8(uint32_t address, uint8_t value) { // Address is any number
	int ret8Only = write8Only(address, value);

	if (ret8Only == ERR_OK) {
		return ERR_OK;
	}

    int miniOffset = address % 4;
    uint32_t temp = read(address - miniOffset); // multiple of 4

    if (busError != ERR_OK) {
        printf("Error: write8, impossible to read address %08X\n", address);
        return busError;
    }

    switch(miniOffset) {
        case 0 :
            temp &= 0x00FFFFFF;
            temp |= value << 24;
            break;
        case 1 :
            temp &= 0xFF00FFFF;
            temp |= value << 16;
            break;
        case 2 :
            temp &= 0xFFFF00FF;
            temp |= value << 8;
            break;
        case 3 :
            temp &= 0xFFFFFF00;
            temp |= value;
            break;
    }

    return write(address - miniOffset, temp);
}

int Bus::getBusError() {
	return busError;
}

void Bus::setBusError(int value) {
	busError = value;
}
