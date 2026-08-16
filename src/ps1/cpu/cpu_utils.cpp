#include "ps1/cpu/cpu.hpp"

int32_t Cpu::signExtend(uint32_t value, int bits) {
    uint32_t mask = 1u << (bits - 1);

    if (value & mask) {
        if (bits == 32)
            return (int32_t)value;

        return (int32_t)(value | (~0u << bits));
    }

    return (int32_t)value;
}

uint64_t Cpu::getInstructionCounter() {
	return instructionCounter;
}

uint32_t Cpu::getInstructionPC() {
	return instructionPC;
}
