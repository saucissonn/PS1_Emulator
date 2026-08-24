#include "ps1/io/cdrom/cdrom.hpp"

#include "ps1/io/dma.hpp"
#include "ps1/bus.hpp"
#include "utils/error.hpp"
#include "ps1/io/interrupt_controller.hpp"

int Cdrom::setInterruptController(InterruptController *interruptController_) {
    if (!interruptController_) {
        return ERR_INVALID_ARGUMENT;
    }

    interruptController = interruptController_;

    return ERR_OK;
}

int Cdrom::setDma(Dma *dma_) {
	if (!dma_) {
		return ERR_INVALID_ARGUMENT;
	}

	dma = dma_;

	return ERR_OK;
}

int Cdrom::setBus(Bus *bus_) {
    if (!bus_) {
        return ERR_INVALID_ARGUMENT;
    }

    bus = bus_;

    return ERR_OK;
}

Cdrom::Cdrom() :
	disc()
{
    index = 0;
    interruptEnable = 0;
    interruptFlag = 0;
    command = 0;
	longCommand = 0;
    countLongCommandParameters = 0;
	request = 0;
	status = 0;
	targetMinute = 0;
	targetSecond = 0;
	targetFrame = 0;

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
            return 0; // Response FIFO

        case 0x1F801802:
            return 0; // Data FIFO

        case 0x1F801803:
			return readRequest();
    }

    return 0;
}

int Cdrom::write(uint32_t address, uint8_t value) {
    switch (address) {
        case 0x1F801800:
            index = value & 0x03;
            return ERR_OK;

        case 0x1F801801:
			return writeCommand(value);

        case 0x1F801802:
			return writeParameter(value);

        case 0x1F801803:
			return writeRequest(value);
    }

	return ERR_WRITE_NOT_ALLOWED;
}

int Cdrom::dmaWrite() { // data FIFO -> RAM
	// DMA Channel 3, SyncMode = 0
	uint32_t bcr = dma->getBCR(3);
	uint32_t madr = dma->getMADR(3);
	uint8_t step = dma->getChannelMemoryAddressStep(3); // 1 or -1
	step *= 4; // 4 or -4
	uint32_t wordCount = bcr & 0xFFFF;

	for (uint32_t i = 0; i < wordCount; i++) {
		uint32_t data = (uint32_t)readData();
		data |= (uint32_t)(readData() << 8);
	    data |= (uint32_t)(readData() << 16);
		data |= (uint32_t)(readData() << 24);
		
		bus->write(madr, data);
		madr += step;
	}

	dma->setMADR(madr, 3);

	return ERR_OK;
}

int Cdrom::run() {
	return decodeLongCommand();
}
