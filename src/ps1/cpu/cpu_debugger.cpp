#include "ps1/cpu/cpu.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "utils/error.hpp"

int Cpu::cpuStateCreate() {
	registerState = (RegisterState **)malloc(sizeof(RegisterState *) * 32);

    for (int i = 0; i < 32; i++) {
		registerState[i] = (RegisterState *)malloc(sizeof(RegisterState));
		
		RegisterState *r = registerState[i];
		r->instructionName = NULL;
		r->step = 0;
		r->oldValue = 0;
		r->value = 0;
    }

	return ERR_OK;
}

void Cpu::cpuStateDestroy() {
	if (!registerState) return;

	for (int i = 0; i < 32; i++) {
		free(registerState[i]);
	}

	free(registerState);
}

void Cpu::cpuStateUpdate(uint32_t instruction) {
    if (!registerState) {
        printf("Error: cpuStateUpdate, registerState does not exist\n");
        return;
    }

	for (int i = 0; i < 32; i++) {
		RegisterState *r = registerState[i];

		if (GPR[i] != r->value) {
			r->instructionName = (char *)instructionToChar(instruction);
            r->step = instructionCounter;
            r->oldValue = r->value;
            r->value = GPR[i];
		}
	}
}

void Cpu::printRegisterState(int index) {
	if (!registerState) {
		printf("Error: printRegisterState, registerState does not exist\n");
		return;
	}

	RegisterState *r = registerState[index];

	// Format Register: old value -> new value, operation name, when
	printf("Register %02d: %08X -> %08X, %s, %ld\n", index, r->oldValue, GPR[index], r->instructionName, r->step);
}

void Cpu::cpuStatePrint() {
	printf("CPU state:\n");
	printf("Format Register: old value -> new value, operation name, when\n");

	for (int i = 0; i < 32; i++) {
		printRegisterState(i);
	}

	printf("\n");
}

const char* Cpu::instructionToChar(uint32_t instruction) {
    uint8_t opcode = instruction >> 26;

    if (opcode == 0x00) {
        uint8_t funct = instruction & 0x3F;

        switch (funct) {
            case 0x00: return instruction == 0 ? "NOP" : "SLL";
            case 0x02: return "SRL";
            case 0x03: return "SRA";
            case 0x04: return "SLLV";
            case 0x06: return "SRLV";
            case 0x07: return "SRAV";
            case 0x08: return "JR";
            case 0x09: return "JALR";
            case 0x0C: return "SYSCALL";
            case 0x0D: return "BREAK";
            case 0x10: return "MFHI";
            case 0x11: return "MTHI";
            case 0x12: return "MFLO";
            case 0x13: return "MTLO";
            case 0x18: return "MULT";
            case 0x19: return "MULTU";
            case 0x1A: return "DIV";
            case 0x1B: return "DIVU";
            case 0x20: return "ADD";
            case 0x21: return "ADDU";
            case 0x22: return "SUB";
            case 0x23: return "SUBU";
            case 0x24: return "AND";
            case 0x25: return "OR";
            case 0x26: return "XOR";
            case 0x27: return "NOR";
            case 0x2A: return "SLT";
            case 0x2B: return "SLTU";
            default:   return "UNKNOWN";
        }
    }

    switch (opcode) {
        case 0x01: return "REGIMM";
        case 0x02: return "J";
        case 0x03: return "JAL";
        case 0x04: return "BEQ";
        case 0x05: return "BNE";
        case 0x06: return "BLEZ";
        case 0x07: return "BGTZ";
        case 0x08: return "ADDI";
        case 0x09: return "ADDIU";
        case 0x0A: return "SLTI";
        case 0x0B: return "SLTIU";
        case 0x0C: return "ANDI";
        case 0x0D: return "ORI";
        case 0x0E: return "XORI";
        case 0x0F: return "LUI";
        case 0x20: return "LB";
        case 0x21: return "LH";
        case 0x22: return "LWL";
        case 0x23: return "LW";
        case 0x24: return "LBU";
        case 0x25: return "LHU";
        case 0x26: return "LWR";
        case 0x28: return "SB";
        case 0x29: return "SH";
        case 0x2A: return "SWL";
        case 0x2B: return "SW";
        case 0x2E: return "SWR";
        case 0x30: return "LWC0";
        case 0x31: return "LWC1";
        case 0x32: return "LWC2";
        case 0x33: return "LWC3";
        case 0x38: return "SWC0";
        case 0x39: return "SWC1";
        case 0x3A: return "SWC2";
        case 0x3B: return "SWC3";
        default:   return "UNKNOWN";
    }
}
