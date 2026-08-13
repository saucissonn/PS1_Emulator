#include "ps1/cpu/cpu.hpp"

#include <stdio.h>

#include "utils/error.hpp"

// Instructions

int Cpu::ADD() {
	GPR[operand->rd] = GPR[operand->rs] + GPR[operand->rt];

	int64_t result = (int64_t)GPR[operand->rs] + (int64_t)GPR[operand->rt];

	if (result > INT32_MAX || result < INT32_MIN) {
        raiseException(Exception::IntegerOverflow);
        return ERR_OK;
	}

	GPR[operand->rd] = (uint32_t)result;

	printf("CPU instruction ADD done\n");

	return ERR_OK;
}

int Cpu::BEQ() {
	int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	if (GPR[operand->rs] == GPR[operand->rt])
		nextPC = PC + target;

    printf("CPU instruction BEQ done\n");

    return ERR_OK;
}


// Decoder

uint32_t Cpu::fetchPC() {
	return PC;
}

void Cpu::transfromRType(uint32_t instruction) {
    operand->rs = (instruction >> 21) & 0x1F; // 5 bits
    operand->rt = (instruction >> 16) & 0x1F; // 5 bits
    operand->rd = (instruction >> 11) & 0x1F; // 5 bits
    operand->shamt = (instruction >> 6) & 0x1F; // 5 bits
}

void Cpu::transfromIType(uint32_t instruction) {
    operand->rs = (instruction >> 21) & 0x1F; // 5 bits
    operand->rt = (instruction >> 16) & 0x1F; // 5 bits
    operand->rd = (instruction << 16) >> 16; // 15 bits
}

void Cpu::transfromJType(uint32_t instruction) {
    operand->target = (instruction << 6) >> 6; // 26 bits
}

int Cpu::decodeInstruction(uint32_t instruction) {
	uint8_t opcode = instruction >> 26; // 6 bits

	printf("Opcode: %2X\n", opcode);

	switch (opcode) {
		case 0x00: { // R-Type
			uint8_t funct = instruction & 0x3F; // 6 bits

			operand->rs = (instruction >> 21) & 0x1F; // 5 bits
            operand->rt = (instruction >> 16) & 0x1F; // 5 bits
            operand->rd = (instruction >> 11) & 0x1F; // 5 bits
            operand->shamt = (instruction >> 6) & 0x1F; // 5 bits

			switch (funct) {
				case 0x09: { // JALR
					// Call JALR function
				}

				case 0x20: { // ADD
					return ADD();
				}
			}
			return ERR_OK;
		}

		case 0x04: {
			return BEQ();
		}

	}

	return ERR_OK;
}
