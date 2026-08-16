#pragma once

#include <cstdint>

#include "ps1/io/gpu/gp0.hpp"
#include "ps1/io/gpu/gp1.hpp"

class Gpu {
    public:
        Gpu();
        ~Gpu();

        uint32_t read(uint32_t address);
        void write(uint32_t address, uint32_t value);

    private:
        Gp0 gp0;
        Gp1 gp1;
        uint32_t gpuRead;
        uint32_t gpuStat;
};
