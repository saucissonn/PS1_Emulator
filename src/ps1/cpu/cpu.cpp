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
		cop0(this),
		cop2(this)
{
	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}
/*
	GPR[8] = 0x12345678;
    GPR[9] = 0x87654321;
    GPR[10] = 3;
    GPR[11] = 4;
    GPR[12] = 0x80000000;
    GPR[13] = 0xFFFFFFFF;
*/
	uint32_t startPC = 0x1FC00000;

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

uint32_t Cpu::convertAddress(uint32_t virtualAddr) {
    if (virtualAddr >> 29 > 0b110){
        // TODO: kseg2 decode
    }
    return virtualAddr & 0x1FFFFFFF;
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

	int ret = dispatchInstruction(instruction); // Also execute

	if (modifyDelaySlot == 1) {
		inDelaySlot = 0;
	}

	instructionCounter += 1;

	if (ret != ERR_OK) {
		return ret;
	}

	return ERR_OK;
}
