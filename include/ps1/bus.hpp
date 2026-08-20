#pragma once

#include <cstdint>

#include "ps1/cpu/cpu.hpp"
#include "ps1/bios.hpp"
#include "ps1/ram.hpp"
#include "ps1/io/io.hpp"
#include "ps1/expansion.hpp"

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
class Expansion;

class Bus {
	public:
		Bus();
		~Bus();

		int setCpu(Cpu *cpu_);
		int setBios(Bios *bios_);
		int setRam(Ram *ram_);
		int setIo(Io *io_);
		int setExpansion1(ExpansionRegion1 *expansion1_); // Currently disconnected
		int setExpansion2(ExpansionRegion2 *expansion2_); // Currently disconnected
		int setExpansion3(ExpansionRegion3 *expansion3_); // Currently disconnected

		uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);
		int write16(uint32_t address, uint16_t value);
		int write8Only(uint32_t address, uint8_t value); // Some rare address can only be written in 8 bits
		int write8(uint32_t adderss, uint8_t value);
        Mem getMemoryHardware(uint32_t physicalAddr); // translate the physical address given into the physical component it is refering to

		int getBusError();
		void setBusError(int value);

	private:
		Cpu *cpu;
		Bios *bios;
		Ram *ram;
		Io *io;
        ExpansionRegion1 *expansion1;
        ExpansionRegion2 *expansion2;
        ExpansionRegion3 *expansion3;

		int busError; // Call exceptions if not equals to ERR_OK
};
