#pragma once

#include <cstdint>

class Vram {
    public:
        Vram();
        ~Vram();

        uint32_t read(uint32_t address);

        void write(uint32_t address, uint32_t value);

    private:
        uint32_t vramSize;
        uint8_t *vram;
};
