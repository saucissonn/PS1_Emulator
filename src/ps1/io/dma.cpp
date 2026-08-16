#include "ps1/io/dma.hpp"

Dma::Dma() {
    for (int i = 0; i < 7; i++) {
        channels[i].baseAddress = 0;
        channels[i].blockControl = 0;
        channels[i].channelControl = 0;
    }

    dpcr = 0;
    dicr = 0;
}

Dma::~Dma() {
    return;
}

uint32_t Dma::read(uint32_t address) {
    if (address >= 0x1F801080 && address <= 0x1F8010E8) {
        uint32_t channel = (address - 0x1F801080) / 0x10;
        uint32_t offset = (address - 0x1F801080) % 0x10;

        switch (offset) {
            case 0x0: {
                return channels[channel].baseAddress;
			}

            case 0x4: {
                return channels[channel].blockControl;
			}

            case 0x8: {
                return channels[channel].channelControl;
			}
        }
    }

    switch (address) {
        case 0x1F8010F0: {
            return dpcr;
		}

        case 0x1F8010F4: {
            return dicr;
		}
	}

    return 0;
}

void Dma::write(uint32_t address, uint32_t value) {
    if (address >= 0x1F801080 && address <= 0x1F8010E8) {
        uint32_t channel = (address - 0x1F801080) / 0x10;
        uint32_t offset = (address - 0x1F801080) % 0x10;

        switch (offset) {
            case 0x0: {
                channels[channel].baseAddress = value;
                return;
			}

            case 0x4: {
                channels[channel].blockControl = value;
                return;
			}

            case 0x8: {
                channels[channel].channelControl = value;
                return;
			}
        }
    }

    switch (address) {
        case 0x1F8010F0: {
            dpcr = value;
            return;
		}

        case 0x1F8010F4: {
            dicr = value;
            return;
		}
    }
}
