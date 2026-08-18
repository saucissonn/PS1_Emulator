#pragma once

#include <cstdint>
#include <vector>

class ExpansionRegion1 {
    public:
        ExpansionRegion1();
        ~ExpansionRegion1();

        uint32_t read(uint32_t address);
        int write(uint32_t address, uint32_t value);

		int getConnected();
		void setConnected(int value);

    private:
		uint32_t dataSize;
        uint8_t *data;

        // Utils

        int connected;
};

class ExpansionRegion2 {
    public:
        ExpansionRegion2();
        ~ExpansionRegion2();

        uint8_t read(uint32_t address);
        int write(uint32_t address, uint32_t value);

        int getConnected();
        void setConnected(int value);

    private:
		uint32_t dataSize;
        uint8_t *data;

        // DUART
        uint8_t modeA;
        uint8_t statusA;
        uint8_t clockA;
        uint8_t commandA;
        uint8_t rxA;
        uint8_t txA;

        uint8_t modeB;
        uint8_t statusB;
        uint8_t clockB;
        uint8_t commandB;
        uint8_t rxB;
        uint8_t txB;

        uint8_t interruptStatus;
        uint8_t interruptMask;
        uint16_t counter;
        uint16_t counterReload;

        uint8_t inputPort;
        uint8_t outputConfig;

        // Int/Dip/Post
        uint8_t atconsStatus;
        uint8_t atconsData;
        uint16_t unknown004;
        uint8_t irqFlags;
        uint8_t irqControl;
        uint8_t dip;
        uint8_t post;
        uint8_t postLed;
        uint8_t post2;

        // Nocash Emulation Expansion
        uint8_t emuEnable1;
        uint8_t emuEnable2;
        uint8_t emuHalt;
        uint8_t emuTurbo;

		// Utils

		int connected;
};

class ExpansionRegion3 {
    public:
        ExpansionRegion3();
        ~ExpansionRegion3();

        uint8_t read(uint32_t address);
        int write(uint32_t address, uint32_t value);

        int getConnected();
        void setConnected(int value);

    private:
        uint8_t post;

        // Utils

        int connected;
};
