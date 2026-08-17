#include "ps1/io/timers.hpp"

#include "utils/error.hpp"

Timers::Timers() {
    for (int i = 0; i < 3; i++) {
        timers[i].counter = 0;
        timers[i].mode = 0;
        timers[i].target = 0;
    }
}

Timers::~Timers() {
    return;
}

uint16_t Timers::read(uint32_t address) {
    if (address >= 0x1F801100 && address <= 0x1F801128) {
        uint32_t timer = (address - 0x1F801100) / 0x10;
        uint32_t offset = (address - 0x1F801100) % 0x10;

        switch (offset) {
            case 0x0:
                return timers[timer].counter;

            case 0x4:
                return timers[timer].mode;

            case 0x8:
                return timers[timer].target;
        }
    }

    return 0;
}

int Timers::write(uint32_t address, uint16_t value) {
    if (address >= 0x1F801100 && address <= 0x1F801128) {
        uint32_t timer = (address - 0x1F801100) / 0x10;
        uint32_t offset = (address - 0x1F801100) % 0x10;

        switch (offset) {
            case 0x0:
                timers[timer].counter = value;
                return ERR_OK;

            case 0x4:
                timers[timer].mode = value;
                return ERR_OK;

            case 0x8:
                timers[timer].target = value;
                return ERR_OK;
        }
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}
