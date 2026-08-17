#pragma once

#include <cstdint>

class Cdrom {
    public:
        Cdrom();
        ~Cdrom();

        uint8_t read(uint32_t address);
        int write(uint32_t address, uint8_t value);

    private:
        uint8_t index;

        uint8_t interruptEnable;
        uint8_t interruptFlag;

        uint8_t command;
        uint8_t request;

        uint8_t audioVolumeLeftToLeft;
        uint8_t audioVolumeLeftToRight;
        uint8_t audioVolumeRightToRight;
        uint8_t audioVolumeRightToLeft;
};
