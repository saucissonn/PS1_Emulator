#pragma once

#include <cstdint>

#include "ps1/cpu/operand.hpp"

class Cpu;

class Cop2 {
    public:
		Cop2(Cpu *cpu_);
		~Cop2();		

        int decodeInstruction(uint32_t instruction);

	private:
		Cpu *cpu;

        uint32_t GPR[32]; // General purpose registers
        Operand *operand; // Current operands
};
