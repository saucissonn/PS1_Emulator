#pragma once

#include <cstdint>

class MemoryControl2 {
    public:
        MemoryControl2();
        ~MemoryControl2();

        uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);

    private:
        uint32_t ramSize;
};
