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

uint32_t Cpu::convertAddress(uint32_t address) {
	printf("Convert address\n");
	return address;
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
