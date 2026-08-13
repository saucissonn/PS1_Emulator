#include "ps1/cpu/cpu.hpp"

int32_t Cpu::signExtend(uint32_t value, int bits) {
    uint32_t mask = 1u << (bits - 1);

    if (value & mask)
        return (int32_t)(value | (~0u << bits));

    return (int32_t)(value);
}
