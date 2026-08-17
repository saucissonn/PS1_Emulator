#include "ps1/io/io.hpp"

#include "utils/error.hpp"

Io::Io() :
	memoryControl1(),
	peripheralIO(),
	memoryControl2(),
	interruptControl(),
	dma(),
	timers(),
	cdrom(),
	gpu(),
	mdec(),
	spu(),
	memoryControl3()
{
	return;
}

Io::~Io() {
	return;
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

	if (0x1F801070 <= address && address <= 0x1F801074) {
		return interruptControl.read(address);
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
		return memoryControl1.write(address, value);
	}

	if (0x1F801040 <= address && address <= 0x1F80105E) {
		return peripheralIO.write(address, value);
	}

	if (address == 0x1F801060) {
		return memoryControl2.write(address, value);
	}

	if (0x1F801070 <= address && address <= 0x1F801074) {
		return interruptControl.write(address, value);
	}

	if (0x1F801080 <= address && address <= 0x1F8010FC) {
		return dma.write(address, value);
	}

	if (0x1F801100 <= address && address <= 0x1F801128) {
		return timers.write(address, value);
	}

	if (0x1F801800 <= address && address <= 0x1F801803) {
		return cdrom.write(address, value);
	}

	if (0x1F801810 <= address && address <= 0x1F801814) {
		return gpu.write(address, value);
	}

	if (0x1F801820 <= address && address <= 0x1F801824) {
		return mdec.write(address, value);
	}

	if (0x1F801C00 <= address && address <= 0x1F801FFF) {
		return spu.write(address, value);
	}

    if (0xFFFE0000 <= address && address <= 0xFFFE01FF) {
        return memoryControl3.write(address, value);
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}
