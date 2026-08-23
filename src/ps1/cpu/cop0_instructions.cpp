#include "ps1/cpu/cop0.hpp"

#include <stdio.h>

#include "ps1/cpu/cpu.hpp"
#include "utils/error.hpp"

// Instructions

int Cop0::MFC0() {
	cpu->setGPR(GPR[operand->rd], operand->rt);

	printf("COP0 instruction MFC0 done\n");

	return ERR_OK;
}

int Cop0::MTC0() {
    GPR[operand->rd] = cpu->getGPR(operand->rt);

    printf("COP0 instruction MTC0 done\n");

    return ERR_OK;
}

int Cop0::RFE() {
	GPR[12] = (GPR[12] & ~0x3F) | ((GPR[12] & 0x3F) >> 2);

    printf("COP0 instruction RFE done\n");

    return ERR_OK;
}

void Cop0::transfromInstruction(uint32_t instruction) {
    operand->rs = (instruction >> 21) & 0x1F; // 5 bits
    operand->rt = (instruction >> 16) & 0x1F; // 5 bits
    operand->rd = (instruction >> 11) & 0x1F; // 5 bits
    operand->funct = instruction & 0x3F; // 6 bits
}

int Cop0::decodeInstruction(uint32_t instruction) { // From an instruction find and execute it among instruction functions
    printf("PC: %8X\n", cpu->getInstructionPC());
    printf("Instruction: %8X\n", instruction);

	transfromInstruction(instruction);

	printf("Opcode: %8X\n", operand->rs);

    switch (operand->rs) {
		case 0x00: {
			return MFC0();
		}

		case 0x04: {
			return MTC0();
		}

        case 0x10: {
			if (operand->funct == 0x10) {
				return RFE();
			}

			return ERR_COP0_INSTRUCTION_NOT_FOUND;
        }

	}

	return ERR_COP0_INSTRUCTION_NOT_FOUND;
}
