#pragma once

#include <cstdint>
#include "ps1/cpu/operand.hpp"

typedef struct {
	uint32_t VPN;	// Virtual Page Number
	uint32_t PFN;	// Page Frame Number
	uint8_t C;		// Cache mode, 3 bits and 0 -> non-cacheable
	bool D;			// Dirty, if a page can be written
	bool V;			// Valid, if an entry is usable
	bool G;			// Global, 0 -> rely on ASID
	uint8_t ASID;	// Address Space Identifier, which physical block
} TLBEntry;

class Cop0 {
	public:
		Cop0();
		~Cop0();

		int decodeInstruction(uint32_t instruction);

		void setCauseRegister(uint32_t value);
		void setCauseRegisterExCode(uint8_t value);
		void setCauseRegisterBD(uint8_t value);

		void setSRRegisterIEc(uint8_t value);
		void setSRRegisterKUc(uint8_t value);

		void setEPCRegister(uint32_t value);

	private:
        uint32_t GPR[32]; // General purpose registers
        uint32_t EntryHi; // R/W in TLB
        uint32_t EntryLo;

        TLBEntry *TLB[64];

        Operand *operand; // Current operands
};
