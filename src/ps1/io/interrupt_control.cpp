#include "ps1/io/interrupt_control.hpp"

InterruptControl::InterruptControl() {
	stat = 0;
	mask = 0;
}

InterruptControl::~InterruptControl() {
	return;
}

uint16_t InterruptControl::read(uint32_t address) {
    switch (address) {
        case 0x1F801070: {
            return stat;
        }

        case 0x1F801074: {
            return mask;
        }
	}

	return 0;
}

void InterruptControl::write(uint32_t address, uint16_t value) {
    switch (address) {
        case 0x1F801070: {
            stat = value;
			return;
        }

        case 0x1F801074: {
            mask = value;
			return;
        }
    }
}
