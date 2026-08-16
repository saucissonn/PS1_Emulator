#pragma once

#include <cstdint>

#include "ps1/cpu/cpu.hpp"
#include "ps1/bios.hpp"
#include "ps1/ram.hpp"

enum class Mem // the physical memory zone in the cpu
{
    MAIN_RAM,
    EXPANSION_REGION_1,
    SCRATCHPAD,
    IO_PORTS,
    EXPANSION_REGION_2,
    EXPANSION_REGION_3,
    BIOS_ROM,
    CACHE_CONTROL,
    INVALID_COMPONENT
};

class Cpu;

class Bus {
	public:
		Bus();
		~Bus();

		int setCpu(Cpu *cpu_);
		int setBios(Bios *bios_);
		int setRam(Ram *ram_);

		uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);
        Mem getMemoryHardware(uint32_t physicalAddr); // translate the physical address given into the physical component it is refering to

	private:
		Cpu *cpu;
		Bios *bios;
		Ram *ram;

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
