#include "ps1/io/dma.hpp"

#include "utils/error.hpp"
#include "ps1/io/mdec.hpp"
#include "ps1/io/gpu/gpu.hpp"
#include "ps1/io/cdrom.hpp"
#include "ps1/io/spu.hpp"
#include "ps1/bus.hpp"

int Dma::setMdec(Mdec *mdec_) {
	if (!mdec_) {
		return ERR_INVALID_ARGUMENT;
	}

	mdec = mdec_;

	return ERR_OK;
}

int Dma::setGpu(Gpu *gpu_) {
    if (!gpu_) {
        return ERR_INVALID_ARGUMENT;
    }

    gpu = gpu_;

    return ERR_OK;
}

int Dma::setCdrom(Cdrom *cdrom_) {
    if (!cdrom_) {
        return ERR_INVALID_ARGUMENT;
    }

    cdrom = cdrom_;

    return ERR_OK;
}

int Dma::setSpu(Spu *spu_) {
    if (!spu_) {
        return ERR_INVALID_ARGUMENT;
    }

    spu = spu_;

    return ERR_OK;
}

int Dma::setBus(Bus *bus_) {
    if (!bus_) {
        return ERR_INVALID_ARGUMENT;
    }

    bus = bus_;

    return ERR_OK;
}

Dma::Dma()
{
    for (int i = 0; i < 7; i++) {
        channels[i].baseAddress = 0;
        channels[i].blockControl = 0;
        channels[i].channelControl = 0;
    }

    dpcr = 0;
    dicr = 0;

	channelMasterIndex = 0;
}

Dma::~Dma() {
    return;
}

uint32_t Dma::read(uint32_t address) {
    if (0x1F801080 <= address && address <= 0x1F8010E8) {
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

int Dma::write(uint32_t address, uint32_t value) {
    if (address >= 0x1F801080 && address <= 0x1F8010E8) {
        uint32_t channel = (address - 0x1F801080) / 0x10;
        uint32_t offset = (address - 0x1F801080) % 0x10;

        switch (offset) {
            case 0x0: {
                channels[channel].baseAddress = value;
                return ERR_OK;
			}

            case 0x4: {
                channels[channel].blockControl = value;
                return ERR_OK;
			}

            case 0x8: {
                channels[channel].channelControl = value;
                return ERR_OK;
			}
        }
    }

    switch (address) {
        case 0x1F8010F0: {
            dpcr = value;
            return ERR_OK;
		}

        case 0x1F8010F4: {
            dicr = value;
            return ERR_OK;
		}
    }

	return ERR_WRITE_NOT_ALLOWED;
}

int Dma::getChannelMasterIndex() {
	return channelMasterIndex;
}

void Dma::setChannelMasterIndex() {
	channelMasterIndex = -1; // Reset

	for (int i = 0; i < 7; i++) { // Get the first master enable
		if (getDmaMasterEnable(i)) {
			channelMasterIndex = i;
			break;
		}
	}

	uint8_t priority = getDmaPriority(channelMasterIndex);

	for (int i = channelMasterIndex + 1; i < 7; i++) { // Search the max priority
		if (getDmaMasterEnable(i) && priority < getDmaPriority(i)) {
			channelMasterIndex = i;
			priority = getDmaPriority(channelMasterIndex);
		}
	}
}

int Dma::runManual() {
	DMAChannel channel = channels[channelMasterIndex];

	for (uint32_t i = 0; i < channel.blockControl; i++) {
		uint32_t value = 0;

		switch (channelMasterIndex) {
			case 3: 
				value = mdec->dmaRead(); // TODO handle busError like
				break;

			default:
				return 0; // TODO return a new error
		}

		bus->write(channel.baseAddress, value);

		channel.baseAddress += 4;
	}

	return ERR_OK;
}

int Dma::decodeSyncMode() {
	uint8_t syncmode = getChannelSyncMode(channelMasterIndex);

	switch (syncmode) {
		case 0: {
			return runManual();
		}

		case 1: {

		}

		case 2: {

		}
	}

	return 0;
}

int Dma::run() {
	setChannelMasterIndex();

	if (channelMasterIndex == -1) { // No channel wants to control the bus
		return ERR_OK;
	}

//	return ERR_INTENTIONAL_STOP;
	return decodeSyncMode();
}
