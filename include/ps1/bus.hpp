#pragma once

#include <cstdint>

#include "ps1/cpu/cpu.hpp"

class Cpu;

class Bus {
	public:
		Bus();
		~Bus();

		int setCpu(Cpu *cpu_);

		uint32_t read(uint32_t address);
		uint32_t write(uint32_t address, uint32_t value);		

	private:
		Cpu *cpu;
};
