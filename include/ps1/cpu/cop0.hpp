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
		void setStatusRegisterIEp(uint8_t value);
		void setStatusRegisterKUp(uint8_t value);
		void setStatusRegisterIEo(uint8_t value);
		void setStatusRegisterKUo(uint8_t value);		
		void setStatusRegisterIm(uint8_t value);
		void setStatusRegisterIsc(uint8_t value);
		void setStatusRegisterSwc(uint8_t value);
		void setStatusRegisterPZ(uint8_t value);
		void setStatusRegisterCM(uint8_t value);
		void setStatusRegisterPE(uint8_t value);
		void setStatusRegisterTS(uint8_t value);
		void setStatusRegisterBEV(uint8_t value);
		void setStatusRegisterRE(uint8_t value);
		void setStatusRegisterCU0(uint8_t value);
		void setStatusRegisterCU1(uint8_t value);
		void setStatusRegisterCU2(uint8_t value);
		void setStatusRegisterCU3(uint8_t value);
		
		bool getStatusRegisterIEc();
		bool getStatusRegisterKUc();
		bool getStatusRegisterIEp();
		bool getStatusRegisterKUp();
		bool getStatusRegisterIEo();
		bool getStatusRegisterKUo();
		uint8_t getStatusRegisterIm();
		bool getStatusRegisterIP2();
		bool getStatusRegisterIsc();
		bool getStatusRegisterSwc();
		bool getStatusRegisterPZ();
		bool getStatusRegisterCM();
		bool getStatusRegisterPE();
		bool getStatusRegisterTS();
		bool getStatusRegisterBEV();
		bool getStatusRegisterRE();
		bool getStatusRegisterCU0();
		bool getStatusRegisterCU1();
		bool getStatusRegisterCU2();
		bool getStatusRegisterCU3();

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
