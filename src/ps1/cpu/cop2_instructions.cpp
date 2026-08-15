#include "ps1/cpu/cop0.hpp"

#include <stdio.h>

#include "ps1/cpu/cpu.hpp"
#include "utils/error.hpp"

int Cop2::decodeInstruction(uint32_t instruction) { // From an instruction find and execute it among instruction functions
    printf("\nPC: %8X\n", cpu->getInstructionPC());
    printf("Instruction: %8X\n", instruction);
    uint8_t opcode = instruction >> 26; // 6 bits

    printf("Opcode: %2X\n", opcode);

    switch (opcode) {
        default: {
            return ERR_OK;
        }
    }
}

