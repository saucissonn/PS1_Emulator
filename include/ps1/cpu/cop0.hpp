#pragma once

#include <cstdint>
#include "ps1/cpu/operand.hpp"

class Cop0 {
	public:
		Cop0();
		~Cop0();

		int decodeInstruction(uint32_t instruction);

		void setCauseRegister(uint32_t value);
		void setCauseRegisterExCode(uint8_t value);

		void setSRRegisterIEc(uint8_t value);
		void setSRRegisterKUc(uint8_t value);

		void setEPCRegister(uint32_t value);

	private:
        uint32_t GPR[32]; // General purpose registers
        uint32_t EntryHi; // R/W in TLB
        uint32_t EntryLo;

        Operand *operand; // Current operands
};
