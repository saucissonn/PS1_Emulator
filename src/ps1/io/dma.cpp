#include "ps1/io/dma.hpp"

#include "utils/error.hpp"
#include "ps1/io/mdec/mdec.hpp"
#include "ps1/io/gpu/gpu.hpp"
#include "ps1/io/cdrom/cdrom.hpp"
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
        channels[i].MADR = 0;
        channels[i].BCR = 0;
        channels[i].CHCR = 0;
    }

    dpcr = 0;
    dicr = 0;

	channelMasterIndex = 0;
	dmaError = ERR_OK;
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
                return channels[channel].MADR;
			}

            case 0x4: {
                return channels[channel].BCR;
			}

            case 0x8: {
                return channels[channel].CHCR;
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
                channels[channel].MADR = value;
                return ERR_OK;
			}

            case 0x4: {
                channels[channel].BCR = value;
                return ERR_OK;
			}

            case 0x8: {
                channels[channel].CHCR = value;
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

uint8_t Dma::getChannelMasterIndex() {
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
	switch (channelMasterIndex) {
		case 3:
			return cdrom->dmaWrite();

        default:
            return ERR_DMA_CHANNEL_NUMBER;
	}

	return ERR_OK;
}

int Dma::runBlock() {
	switch (channelMasterIndex) {
        case 0: 
            return mdec->dmaWriteIn();

		case 1: 
			return mdec->dmaWriteOut();

		default:
			return ERR_DMA_CHANNEL_NUMBER;
	}

	return ERR_OK;
}

int Dma::decodeSyncMode() {
	uint8_t syncmode = getChannelSyncMode(channelMasterIndex);

	switch (syncmode) {
		case 0: {
			return runManual(); // Send n elements at once
		}

		case 1: {
			return runBlock(); // Send n block of m elements at once
		}

		case 2: {
			return ERR_OK; // TODO: Weird
		}
	}

	return ERR_DMA_CHANNEL_NUMBER;
}

int Dma::run() {
	setChannelMasterIndex();

	if (channelMasterIndex == -1) { // No channel wants to control the bus
		return ERR_OK;
	}

//	return ERR_INTENTIONAL_STOP;
	return decodeSyncMode();
}
