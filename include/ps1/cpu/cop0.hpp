#pragma once

#include <cstdint>

#include "ps1/cpu/operand.hpp"

class Cpu;

class Cop0 {
	public:
		Cop0(Cpu *cpu_);
		~Cop0();

		int decodeInstruction(uint32_t instruction);

		// Utils

		void setCauseRegister(uint32_t value);
		void setCauseRegisterExCode(uint8_t value);
		void setCauseRegisterBD(uint8_t value);

		void setSRRegisterIEc(uint8_t value);
		void setSRRegisterKUc(uint8_t value);

		void setEPCRegister(uint32_t value);

	private:
		Cpu *cpu;

        uint32_t GPR[32]; // General purpose registers
        uint32_t EntryHi; // R/W in TLB
        uint32_t EntryLo;

		void transfromInstruction(uint32_t instruction);

        Operand *operand; // Current operands

		// Instructions

		int MFC0();
		int MTC0();
		int RFE();
};
