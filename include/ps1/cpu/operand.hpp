#pragma once

#include <cstdint>

typedef struct {
    uint8_t rs;         // Source register (5 bits)
    uint8_t rt;         // Target / source register (5 bits)
    uint8_t rd;         // Destination register (5 bits)
    uint8_t shamt;      // Shift amount (5 bits)
    uint16_t immediate; // Immediate (16 bits)
    uint32_t target;    // Target (26 bits)
    uint8_t funct;      // Function (6 bits)

    // COP2 / GTE command
    uint8_t command;    // Real GTE Command Number (6 bits)
    uint8_t lm;         // Saturate IR1-IR3 (1 bit)
    uint8_t mvmva_tv;   // Translation Vector (2 bits)
    uint8_t mvmva_mv;   // Multiply Vector (2 bits)
    uint8_t mvmva_mm;   // Multiply Matrix (2 bits)
    uint8_t sf;         // Shift Fraction (1 bit)
} Operand;

Operand *operandCreate();
