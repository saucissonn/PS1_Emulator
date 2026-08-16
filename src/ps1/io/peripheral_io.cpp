#include "ps1/io/peripheral_io.hpp"

PeripheralIO::PeripheralIO() {
    joyData = 0;
    joyStat = 0;
    joyMode = 0;
    joyCtrl = 0;
    joyBaud = 0;

    sioData = 0;
    sioStat = 0;
    sioMode = 0;
    sioCtrl = 0;
    sioMisc = 0;
    sioBaud = 0;
}

PeripheralIO::~PeripheralIO() {
	return;
}

uint32_t PeripheralIO::read(uint32_t address) {
    switch (address) {
        case 0x1F801040: {
            return joyData;
        }

        case 0x1F801044: {
            return joyStat;
        }

        case 0x1F801048: {
            return joyMode;
        }

        case 0x1F80104A: {
            return joyCtrl;
        }

        case 0x1F80104E: {
            return joyBaud;
        }

        case 0x1F801050: {
            return sioData;
        }

        case 0x1F801054: {
            return sioStat;
        }

        case 0x1F801058: {
            return sioMode;
        }

        case 0x1F80105A: {
            return sioCtrl;
        }

        case 0x1F80105C: {
            return sioMisc;
        }

        case 0x1F80105E: {
            return sioBaud;
        }

        default: {
            return 0;
        }
    }
}

void PeripheralIO::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1F801040: {
            joyData = value;
            return;
        }

        case 0x1F801048: {
            joyMode = value;
            return;
        }

        case 0x1F80104A: {
            joyCtrl = value;
            return;
        }

        case 0x1F80104E: {
            joyBaud = value;
            return;
        }

        case 0x1F801050: {
            sioData = value;
            return;
        }

        case 0x1F801058: {
            sioMode = value;
            return;
        }

        case 0x1F80105A: {
            sioCtrl = value;
            return;
        }

        case 0x1F80105C: {
            sioMisc = value;
            return;
        }

        case 0x1F80105E: {
            sioBaud = value;
            return;
        }

        default: {
            return;
        }
    }
}
