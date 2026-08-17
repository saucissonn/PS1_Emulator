#pragma once

#include <cstdint>

struct Timer {
    uint16_t counter;
    uint16_t mode;
    uint16_t target;
};

class Timers {
    public:
        Timers();
        ~Timers();

        uint16_t read(uint32_t address);
		int write(uint32_t address, uint16_t value);

    private:
        Timer timers[3];
};
