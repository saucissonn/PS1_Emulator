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
	CacheLine **cache = (CacheLine **)malloc(sizeof(CacheLine *));

	for (int i = 0; i < size; i++) {
		cache[i] = createCacheLine();
	}

	return cache;
}

Cpu::Cpu(Bus *bus_) 
	: bus(bus_)
{
	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}

	PC = 0;
	HI = 0;
	LO = 0;

	operand = operandCreate();

	DCacheSize = 100;
	ICacheSize = 100;

	DCache = createCache(DCacheSize);
	ICache = createCache(ICacheSize);

    cop0 = Cop0();
    cop2 = Cop2();

	return;
}

Cpu::~Cpu() {
    return;
}

uint32_t Cpu::convertAddress(uint32_t address) {
	printf("Convert address\n");
	return address;
}

int Cpu::run() {
	convertAddress(0);
	return 0;
}
