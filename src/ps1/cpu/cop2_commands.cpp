#include "ps1/cpu/cop2.hpp"

#include <stdio.h>

#include "ps1/cpu/cpu.hpp"
#include "utils/error.hpp"

void Cop2::transfromCommand(uint32_t command) {
    operand->command = command & 0x3F;			// bits 0-5
    operand->lm = (command >> 10) & 0x01;		// bit 10
    operand->mvmva_mv = (command >> 15) & 0x03;	// bits 15-16
    operand->mvmva_mm = (command >> 17) & 0x03; // bits 17-18
    operand->sf = (command >> 19) & 0x01;		// bit 19
    operand->mvmva_tv = (command >> 13) & 0x03;	// bits 13-14
}

int Cop2::decodeCommand(uint32_t command) { // From a command find and execute it among command functions
    printf("\nPC: %8X\n", cpu->getInstructionPC());
    printf("Command: %8X\n", command);

	transfromCommand(command);

    printf("Opcode: %2X\n", operand->command);

    switch (operand->command) {
        default: return ERR_COP2_COMMAND_NOT_FOUND;
    }
}

