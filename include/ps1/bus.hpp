#pragma once

#include <cstdint>

#include "ps1/cpu/cpu.hpp"
#include "ps1/bios.hpp"

class Cpu;

class Bus {
	public:
		Bus();
		~Bus();

		int setCpu(Cpu *cpu_);
		int setBios(Bios *bios_);

		uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);		

	private:
		Cpu *cpu;
		Bios *bios;

		uint32_t expansionRegion1Size;
		uint32_t memoryControl1Size;
		uint32_t periphericalIOPortsSize;
		uint32_t memoryControl2Size;
        uint32_t expansionRegion2Size;
		uint32_t expansionRegion3Size;
		uint32_t memoryControl3Size;

        uint32_t *expansionRegion1;
        uint32_t *memoryControl1;
        uint32_t *periphericalIOPorts;
        uint32_t *memoryControl2;
        uint32_t *expansionRegion2;
        uint32_t *expansionRegion3;
        uint32_t *memoryControl3;
};
