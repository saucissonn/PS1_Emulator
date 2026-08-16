#include "ps1/io/memory_control.hpp"

MemoryControl1::MemoryControl1() {
    expansion1Base = 0;
    expansion2Base = 0;
    expansion1DelaySize = 0;
    expansion3DelaySize = 0;
    biosRomDelaySize = 0;
    spuDelay = 0;
    cdromDelay = 0;
    expansion2DelaySize = 0;
    commonDelay = 0;

	return;
}

MemoryControl1::~MemoryControl1() {
	return;
}

uint32_t MemoryControl1::read(uint32_t address) {
    switch (address) {
        case 0x1F801000: {
            return expansion1Base;
        }

        case 0x1F801004: {
            return expansion2Base;
        }

        case 0x1F801008: {
            return expansion1DelaySize;
        }

        case 0x1F80100C: {
            return expansion3DelaySize;
        }

        case 0x1F801010: {
            return biosRomDelaySize;
        }

        case 0x1F801014: {
            return spuDelay;
        }

        case 0x1F801018: {
            return cdromDelay;
        }

        case 0x1F80101C: {
            return expansion2DelaySize;
        }

        case 0x1F801020: {
            return commonDelay;
        }

        default: {
            return 0;
        }
    }
}

void MemoryControl1::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1F801000: {
            expansion1Base = value;
            return;
        }

        case 0x1F801004: {
            expansion2Base = value;
            return;
        }

        case 0x1F801008: {
            expansion1DelaySize = value;
            return;
        }

        case 0x1F80100C: {
            expansion3DelaySize = value;
            return;
        }

        case 0x1F801010: {
            biosRomDelaySize = value;
            return;
        }

        case 0x1F801014: {
            spuDelay = value;
            return;
        }

        case 0x1F801018: {
            cdromDelay = value;
            return;
        }

        case 0x1F80101C: {
            expansion2DelaySize = value;
            return;
        }

        case 0x1F801020: {
            commonDelay = value;
            return;
        }

        default: {
            return;
        }
    }
}
