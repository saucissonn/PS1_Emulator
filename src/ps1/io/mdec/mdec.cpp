#include "ps1/io/mdec/mdec.hpp"

#include "ps1/io/dma.hpp"
#include "ps1/bus.hpp"
#include "utils/error.hpp"

int Mdec::setDma(Dma *dma_) {
    if (!dma_) {
        return ERR_INVALID_ARGUMENT;
    }

    dma = dma_;

    return ERR_OK;
}

int Mdec::setBus(Bus *bus_) {
    if (!bus_) {
        return ERR_INVALID_ARGUMENT;
    }

    bus = bus_;

    return ERR_OK;
}

Mdec::Mdec() {
    status = 0;
    control = 0;
}

Mdec::~Mdec() {
    return;
}

uint32_t Mdec::readOut() {
    if (dataOut.empty())
        return 0;

    uint32_t value = dataOut.front();
    dataOut.pop();

    return value;	
}

uint32_t Mdec::read(uint32_t address) {
    switch (address) {
        case 0x1F801820:
            return readOut();

        case 0x1F801824:
            return status;
    }

    return 0;
}

int Mdec::writeIn(uint32_t value) {
	dataIn.push(value);

	return ERR_OK;
}

int Mdec::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1F801820:
            writeIn(value);

		    // Check if there is enough parameters
		    if (dataIn.size() - 1 >= getParameterCount()) {
		        return decodeCommand();
		    }
			
            return ERR_OK;

        case 0x1F801824:
            control = value;
            return ERR_OK;
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}

int Mdec::dmaWriteIn() { // RAM -> MDEC
	return ERR_OK;
}

int Mdec::dmaWriteOut() { // MDEC -> RAM
    // DMA Channel 1, SyncMode = 1
    uint32_t bcr = dma->getBCR(1);
    uint32_t madr = dma->getMADR(1);
    uint8_t step = dma->getChannelMemoryAddressStep(1); // 1 or -1
    step *= 4; // 4 or -4

    uint32_t wordCount = bcr & 0x0000FFFF;
	uint32_t blockCount = (bcr >> 16) & 0xFFFF;;
	uint32_t stepCount = wordCount * blockCount;  
 
    for (uint32_t i = 0; i < stepCount; i++) {
		uint32_t data = readOut();
        bus->write(madr, data);
        madr += step;
    }

    dma->setMADR(madr, 1);

    return ERR_OK;
}
