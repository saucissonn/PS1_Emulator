#pragma once

#include <cstdint>

class Mdec {
    public:
        Mdec();
        ~Mdec();

        uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);

    private:
        uint32_t data;
        uint32_t status;
        uint32_t control;
};
