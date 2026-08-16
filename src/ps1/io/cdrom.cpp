#include "ps1/io/cdrom.hpp"

Cdrom::Cdrom() {
    index = 0;

    interruptEnable = 0;
    interruptFlag = 0;

    command = 0;
    request = 0;

    audioVolumeLeftToLeft = 0;
    audioVolumeLeftToRight = 0;
    audioVolumeRightToRight = 0;
    audioVolumeRightToLeft = 0;
}

Cdrom::~Cdrom() {
    return;
}

uint8_t Cdrom::read(uint32_t address) {
    switch (address) {
        case 0x1F801800:
            return index;

        case 0x1F801801:
            switch (index) {
                case 1:
                    return 0; // Response FIFO
            }
            break;

        case 0x1F801802:
            return 0; // Data FIFO

        case 0x1F801803:
            switch (index) {
                case 0:
                    return interruptEnable;

                case 1:
                    return interruptFlag;

                case 2:
                    return interruptEnable;

                case 3:
                    return interruptFlag;
            }
            break;
    }

    return 0;
}

void Cdrom::write(uint32_t address, uint8_t value) {
    switch (address) {
        case 0x1F801800:
            index = value & 0x03;
            return;

        case 0x1F801801:
            switch (index) {
                case 0:
                    command = value;
                    return;

                case 1:
                    return; // Unknown/unused

                case 2:
                    return; // Unknown/unused

                case 3:
                    audioVolumeRightToRight = value;
                    return;
            }
            break;

        case 0x1F801802:
            switch (index) {
                case 0:
                    return; // Parameter FIFO

                case 1:
                    interruptEnable = value;
                    return;

                case 2:
                    audioVolumeLeftToLeft = value;
                    return;

                case 3:
                    audioVolumeRightToLeft = value;
                    return;
            }
            break;

        case 0x1F801803:
            switch (index) {
                case 0:
                    request = value;
                    return;

                case 1:
                    interruptFlag = value;
                    return;

                case 2:
                    return; // Audio volume apply changes

                case 3:
                    interruptFlag = value;
                    return;
            }
            break;
    }
}
