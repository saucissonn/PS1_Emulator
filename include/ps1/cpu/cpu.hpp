#pragma once

#include "ps1/cpu/operand.hpp"
#include "ps1/cpu/cop0.hpp"
#include "ps1/cpu/cop2.hpp"
#include "ps1/bus.hpp"

typedef struct {
	bool valid;
	uint32_t tag;
	uint8_t data[16];
} CacheLine;

CacheLine **createCache(int size);

enum class Exception
{
    Interrupt = 0,
    LoadAddressError = 4,		// Address not alligned on read
    StoreAddressError = 5,		// Address not alligned on store
    BusErrorInstruction = 6,	// Can't read instruction
    BusErrorData = 7,			// Can't read / write at the current address
    Syscall = 8,
    Breakpoint = 9,
    ReservedInstruction = 10,
    CoprocessorUnusable = 11,
    ArithmeticOverflow = 12,
};

class Bus;
class Cop0;
class Cop2;

class Cpu {
    public:
        Cpu(Bus *bus_);
        ~Cpu();

        uint32_t convertAddress(uint32_t address); // From virtual to physical address
        uint32_t useCache(uint32_t address, CacheLine **cache); // Output is an instruction

		uint32_t fetchPC(); // Decode PC and give the instruction to execute

		int dispatchInstruction(uint32_t instruction); // Which componant has to execute the instruction
        int decodeInstruction(uint32_t instruction); // Decode and execute an instruction

        int accessDataMemory(uint32_t address); // If an instruction uses a load / store, use it to get the address

        int run();

		// Utils

		uint32_t getGPR(uint8_t index);
		void setGPR(uint32_t value, uint8_t index);

		uint64_t getInstructionCounter();
		uint32_t getInstructionPC();

	private:
		Bus *bus;
        Cop0 cop0;
        Cop2 cop2;

        uint32_t GPR[32];   // General purpose registers
        uint32_t PC;        // Program Counter (instructionPC + 4)
        uint32_t HI;        // High
        uint32_t LO;        // Low

        Operand *operand; // Current operands
		uint32_t prevPC;
		uint32_t instructionPC; // current pc
		uint32_t nextPC; // instructionPC + 8 | branch or jump address
		bool inDelaySlot;

		uint64_t instructionCounter;

		uint8_t DCacheSize;
		uint8_t ICacheSize;
        CacheLine **DCache;
        CacheLine **ICache;

		// Instructions

		void transfromRType(uint32_t instruction);
		void transfromIType(uint32_t instruction);
		void transfromJType(uint32_t instruction);

		int raiseException(Exception exception);

		int ADD();
		int ADDI();
		int ADDIU();
		int ADDU();
		int AND();
		int ANDI();
		int BEQ();
		int BNE();
		int BREAK();
		int DIV();
		int DIVU();
		int J();
		int JAL();
		int JALR();
		int JR();
		int LUI();
		int MFHI();
		int MTHI();
		int MFLO();
		int MTLO();
		int MULT();
		int MULTU();
		int NOP();
		int NOR();
		int OR();
		int ORI();
		int SLL();
        int SLLV();
		int SLT();
		int SLTI();
        int SLTIU();
		int SLTU();
		int SRA();
		int SRAV();
		int SRL();
		int SRLV();
		int SUBU();
		int SW();
		int SUB();
		int SYSCALL();
		int XOR();
		int XORI();
		int BLEZ();
		int BGTZ();
		int BLTZAL();
		int BGEZAL();
		int BGEZ();
		int BLTZ();
		int LB();
		int LH();
		int LWL();
		int LW();
		int LBU();
		int LHU();
		int LWR();
		int SB();
		int SH();
		int SWL();
		int SWR();
		int LWC0();
		int LWC1();
		int LWC2();
		int LWC3();
		int SWC0();
		int SWC1();
		int SWC2();
		int SWC3();

		// Utils
		int32_t signExtend(uint32_t value, int bits);
};
