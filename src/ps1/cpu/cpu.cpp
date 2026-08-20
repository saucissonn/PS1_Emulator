#include "ps1/cpu/cpu.hpp"

#include <stdio.h>
#include <cstdlib>

#include "ps1/interrupt_controller.hpp"
#include "utils/error.hpp"

int Cpu::setInterruptController(InterruptController *interruptController_) {
	if (!interruptController_) {
		return ERR_INVALID_ARGUMENT;
	}

	interruptController = interruptController_;

	return ERR_OK;
}

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

uint32_t Cpu::convertAddress(uint32_t virtualAddr) {
    // KUSEG / KSEG0 / KSEG1
    if (virtualAddr < 0xC0000000) {
        return virtualAddr & 0x1FFFFFFF;
    }

	// KSEG2
    if (virtualAddr >= 0xFFFE0000 &&
        virtualAddr <= 0xFFFE01FF) {
        return virtualAddr;
    }

	// Unmapped address
	cop0.setBadVaddr(virtualAddr);
    raiseException(Exception::BusErrorData);

    return 0;
}

int Cpu::executeInstruction() {
	prevPC = instructionPC;
    instructionPC = PC;

    uint32_t instruction = fetchPC();

    bool wasDelaySlot = inDelaySlot;

    int ret = dispatchInstruction(instruction);

    if (wasDelaySlot) {
        PC = nextPC;
        nextPC = PC + 4;
        inDelaySlot = false;
    }
    else if (inDelaySlot) {
        PC = PC + 4;
    }
    else {
        PC = nextPC;
        nextPC = PC + 4;
    }

    instructionCounter++;

    return ret;
}

int Cpu::run() {
	updateInterrupt();

	if (launchInterrupt()) {
		return handleInterrupt();
	}
	else {
		return executeInstruction();
	}
}
