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
    LoadAddressError = 4,
    StoreAddressError = 5,
    BusErrorInstruction = 6,
    BusErrorData = 7,
    Syscall = 8,
    Breakpoint = 9,
    ReservedInstruction = 10,
    CoprocessorUnusable = 11,
    IntegerOverflow = 12,
};

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

class Bus;

class Cpu {
    public:
        Cpu(Bus *bus_);
        ~Cpu();

        uint32_t convertAddress(uint32_t address); // From virtual to physical address
        Mem getMemoryHardware(uint32_t physicalAddr); // translate the physical address given into the physical component it is refering to
        uint32_t useCache(uint32_t address, CacheLine **cache); // Output is an instruction

		uint32_t fetchPC(); // Decode PC and give the instruction to execute

        int decodeInstruction(uint32_t instruction); // Decode and execute an instruction
        int accessDataMemory(uint32_t address); // If an instruction uses a load / store, use it to get the address

        int run();

	private:
		Bus *bus;

        uint32_t GPR[32];   // General purpose registers
        uint32_t PC;        // Program Counter
        uint32_t HI;        // High
        uint32_t LO;        // Low

        Operand *operand; // Current operands
		uint32_t instructionPC;
		uint32_t nextPC;

		uint8_t DCacheSize;
		uint8_t ICacheSize;
        CacheLine **DCache;
        CacheLine **ICache;

        Cop0 cop0;
        Cop2 cop2;

		// Instructions

		void transfromRType(uint32_t instruction);
		void transfromIType(uint32_t instruction);
		void transfromJType(uint32_t instruction);

		int raiseException(Exception exception);

		int ADD();
		int BEQ();

		// Utils

		int32_t signExtend(uint32_t value, int bits);
};
