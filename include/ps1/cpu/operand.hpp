#pragma once

#include <cstdint>

typedef struct {
    uint8_t rs;         // Source register (5 bits)
    uint8_t rt;         // Target / source register (5 bits)
    uint8_t rd;         // Destination register (5 bits)
    uint8_t shamt;      // Shift amount (5 bits)
    uint16_t immediate; // (16 bits)
    uint32_t target;    // (26 bits)
} Operand;

Operand *operandCreate();
