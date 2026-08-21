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

uint8_t Cdrom::readData() {
    if (data.empty())
        return 0;

    uint8_t value = data.front();
    data.pop();

    return value;
}

int Cdrom::dmaWrite() { // data FIFO -> RAM
	uint32_t bcr = dma->getBCR(3);
	uint32_t madr = dma->getMADR(3);

	for (uint32_t i = 0; i < bcr; i++) {
		uint32_t data = readData();
		data |= readData() << 8;
	    data |= readData() << 16;
		data |= readData() << 24;
		
		bus->write(madr, data);
		madr += 4;
	}
	return ERR_OK;
}
