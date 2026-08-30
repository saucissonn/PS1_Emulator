#include "ps1/io/io.hpp"

#include "utils/error.hpp"
#include "ps1/bus.hpp"
#include "ps1/io/interrupt_controller.hpp"

Io::Io() :
	memoryControl1(),
	peripheralIO(),
	memoryControl2(),
	interruptController(),
	dma(),
	timers(),
	cdrom(),
	gpu(),
	mdec(),
	spu(),
	memoryControl3()
{
	timers.setInterruptController(&interruptController);

	cdrom.setDma(&dma);
	cdrom.setBus(bus);
	cdrom.setInterruptController(&interruptController);

	gpu.setInterruptController(&interruptController);
	gpu.setBus(bus);
	gpu.setDma(&dma);

	mdec.setDma(&dma);
	mdec.setBus(bus);

	spu.setInterruptController(&interruptController);

	// Connect to DMA
	dma.setMdec(&mdec);
	dma.setGpu(&gpu);
	dma.setCdrom(&cdrom);
	dma.setSpu(&spu);
	dma.setBus(bus);

	return;
}

Io::~Io() {
	return;
}

int Io::setBus(Bus *bus_) {
    if (!bus_) {
        return ERR_INVALID_ARGUMENT;
    }

    bus = bus_;

    return ERR_OK;
}

uint32_t Io::read(uint32_t address) {
	if (0x1F801000 <= address && address <= 0x1F801020) {
		return memoryControl1.read(address);
	}

	if (0x1F801040 <= address && address <= 0x1F80105E) {
		return peripheralIO.read(address);
	}

	if (address == 0x1F801060) {
		return memoryControl2.read(address);
	}

	if (0x1F801080 <= address && address <= 0x1F8010FC) {
		return dma.read(address);
	}

	if (0x1F801100 <= address && address <= 0x1F801128) {
		return timers.read(address);
	}

	if (0x1F801800 <= address && address <= 0x1F801803) {
		return cdrom.read(address);
	}

	if (0x1F801810 <= address && address <= 0x1F801814) {
		return gpu.read(address);
	}

	if (0x1F801820 <= address && address <= 0x1F801824) {
		return mdec.read(address);
	}

	if (0x1F801C00 <= address && address <= 0x1F801FFF) {
		return spu.read(address);
	}

    if (0xFFFE0000 <= address && address <= 0xFFFE01FF) {
        return memoryControl3.read(address);
    }

	return 0;
}

int Io::write(uint32_t address, uint32_t value) {	
	if (0x1F801000 <= address && address <= 0x1F801020) {
        return ERR_NOT_IMPLEMENTED;
		return memoryControl1.write(address, value);
	}

	if (0x1F801040 <= address && address <= 0x1F80105E) {
        return ERR_NOT_IMPLEMENTED;
		return peripheralIO.write(address, value);
	}

	if (address == 0x1F801060) {
        return ERR_NOT_IMPLEMENTED;
		return memoryControl2.write(address, value);
	}

    if (0x1F801070 <= address && address <= 0x1F801074) {
        return ERR_NOT_IMPLEMENTED;
        return interruptController.write(address, value);
	}

	if (0x1F801080 <= address && address <= 0x1F8010FC) {
        return ERR_NOT_IMPLEMENTED;
		return dma.write(address, value);
	}

	if (0x1F801100 <= address && address <= 0x1F801128) {
        return ERR_NOT_IMPLEMENTED;
		return timers.write(address, value);
	}

	if (0x1F801810 <= address && address <= 0x1F801814) {
        return ERR_NOT_IMPLEMENTED;
		return gpu.write(address, value);
	}

	if (0x1F801820 <= address && address <= 0x1F801824) {
        return ERR_NOT_IMPLEMENTED;
		return mdec.write(address, value);
	}

	if (0x1F801C00 <= address && address <= 0x1F801FFF) {
        return ERR_NOT_IMPLEMENTED;
		return spu.write(address, value);
	}

    if (0xFFFE0000 <= address && address <= 0xFFFE01FF) {
		return ERR_NOT_IMPLEMENTED;
        return memoryControl3.write(address, value);
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}

int Io::write8Only(uint32_t address, uint8_t value) {
    if (0x1F801800 <= address && address <= 0x1F801803) {
		return ERR_NOT_IMPLEMENTED;
        return cdrom.write(address, value);
    }

    return ERR_WRITE_SECTION_NOT_FOUND;
}

int Io::dmaRun() {
	return dma.run();
}

InterruptController* Io::getInterruptController() {
    return &interruptController;
}

Timers *Io::getTimers() {
	return &timers;
}

int Io::run() {
    int ret = dma.run();

	if (ret != ERR_OK) {
		return ret;
	}

	ret = cdrom.run();

    if (ret != ERR_OK) {
        return ret;
    }

	return ERR_OK;
}
