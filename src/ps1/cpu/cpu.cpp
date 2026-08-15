#include "ps1/cpu/cpu.hpp"

#include <stdio.h>
#include <cstdlib>

#include "utils/error.hpp"

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

	uint32_t startPC = 0xBFC00000;

	PC = startPC;
	HI = 0;
	LO = 0;

	operand = operandCreate();

	prevPC = startPC - 4;
	instructionPC = startPC;
	nextPC = startPC + 4;

	instructionCounter = 0;

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

int Cpu::run() {
	prevPC = instructionPC; // before
	instructionPC = PC; // now (to modify if exception)
	PC = nextPC; // next
	nextPC = PC + 4; // after next (to modify if branch / jump)

	uint32_t instruction = fetchPC();

	bool modifyDelaySlot = 0;

	if (inDelaySlot == 1) {
		modifyDelaySlot = 1;
	}

	int ret = decodeInstruction(instruction); // Also execute

	if (modifyDelaySlot == 1) {
		inDelaySlot = 0;
	}

	instructionCounter += 1;

	if (ret != ERR_OK) {
		return ret;
	}

	return ERR_OK;
}
