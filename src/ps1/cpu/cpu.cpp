#include "ps1/cpu/cpu.hpp"

#include <stdio.h>
#include <cstdlib>

CacheLine *createCacheLine() {
	CacheLine *cacheLine = (CacheLine *)malloc(sizeof(CacheLine));

	cacheLine->valid = 0;
	cacheLine->tag = 0;
	for (int i = 0; i < 16; i++) {
		cacheLine->data[i] = 0;
	}

	return cacheLine;
}

CacheLine **createCache(int size) {
	CacheLine **cache = (CacheLine **)malloc(sizeof(CacheLine *) * size);

	for (int i = 0; i < size; i++) {
		cache[i] = createCacheLine();
	}

	return cache;
}

void destroyCache(CacheLine **cache, int size) {
	if (!cache) {
		return;
	}

	for (int i = 0; i < size; i++) {
        free(cache[i]);
    }

	free(cache);
}

Cpu::Cpu(Bus *bus_)
	: bus(bus_),
		cop0(),
		cop2()
{
	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}

	PC = 0;
	HI = 0;
	LO = 0;

	operand = operandCreate();

	instructionPC = 0;
	nextPC = 0;

	DCacheSize = 100;
	ICacheSize = 100;

	DCache = createCache(DCacheSize);
	ICache = createCache(ICacheSize);

	return;
}

Cpu::~Cpu() {
	destroyCache(DCache, DCacheSize);
	destroyCache(ICache, ICacheSize);

	free(operand);

    return;
}

uint32_t Cpu::convertAddress(uint32_t virtualAddr) {
    if (virtualAddr >> 29 > 0b110){
        // TODO: kseg2 decode
    }
    else
        return virtualAddr & 0x1FFFFFFF;
}

Mem Cpu::getMemoryHardware(uint32_t physicalAddr){
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

int Cpu::run() {
	convertAddress(0);

	instructionPC = PC; // now (to modify if exception)
	PC = nextPC; // next
	nextPC = PC + 4; // after next (to modify if branch / jump)

	// uint32_t instruction = fetchPC(instructionPC);
	// decodeInstruction(instruction);

	decodeInstruction(0x20);
	decodeInstruction(0x10000020);

	return 0;
}
