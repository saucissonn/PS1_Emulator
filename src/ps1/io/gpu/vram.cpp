#include "ps1/io/gpu/vram.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <cstdio>

#include "utils/error.hpp"

Vram::Vram() {
    vramSize = 0x100000;
    vram = (uint8_t *)calloc(vramSize, sizeof(uint8_t));

    return;
}

Vram::~Vram() {
    free(vram);

    return;
}

uint32_t Vram::read(uint32_t address) {
    return vram[address];
}

void Vram::write(uint32_t address, uint32_t value) {
    vram[address] = value;
}
