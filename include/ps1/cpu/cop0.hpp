#pragma once

#include <cstdint>
#include <sys/types.h>

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
		void setCauseRegisterIP2(bool value);
		void setCauseRegisterBD(uint8_t value);

		void setEPCRegister(uint32_t value);

        // NOTE: DO NOT forget to call this function with the invalid address in case of badVaddr exception before calling Cpu::raiseException
		void setBadVaddr(uint32_t badVaddr); // set BadVaddr (GPR[8]) to badVaddr

		void setStatusRegisterIEc(uint8_t value);
		void setStatusRegisterKUc(uint8_t value);
		void setStatusRegisterIEo(uint8_t value);
		void setStatusRegisterKUo(uint8_t value);
		void setStatusRegisterIEp(uint8_t value);
		void setStatusRegisterKUp(uint8_t value);
		void setStatusRegisterBEV(uint8_t value);

		bool getStatusRegisterIEp();
		bool getStatusRegisterKUp();
		bool getStatusRegisterIEc();
		bool getStatusRegisterKUc();
		bool getStatusRegisterIP2();
        bool getStatusRegisterBEV();

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
