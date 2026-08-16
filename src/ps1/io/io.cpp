#include "ps1/io/io.hpp"

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
	expansion1(),
	expansion2(),
	expansion3()
{
	return;
}

Io::~Io() {
	return;
}

uint32_t Io::read(uint32_t address) {
	if (0x1F000000 <= address && address <= 0x1F07FFFF) {
		return expansion1.read(address);
	}

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

	if (0x1F802000 <= address && address <= 0x1F80207F) {
		return expansion2.read(address);
	}

	if (address == 0x1FA00000) {
		return expansion3.read(address);
	}

	return 0;
}

void Io::write(uint32_t address, uint32_t value) {
	if (0x1F000000 <= address && address <= 0x1F07FFFF) {
		expansion1.write(address, value);
		return;
	}

	if (0x1F801000 <= address && address <= 0x1F801020) {
		memoryControl1.write(address, value);
		return;
	}

	if (0x1F801040 <= address && address <= 0x1F80105E) {
		peripheralIO.write(address, value);
		return;
	}

	if (address == 0x1F801060) {
		memoryControl2.write(address, value);
		return;
	}

	if (0x1F801070 <= address && address <= 0x1F801074) {
		interruptControl.write(address, value);
		return;
	}

	if (0x1F801080 <= address && address <= 0x1F8010FC) {
		dma.write(address, value);
		return;
	}

	if (0x1F801100 <= address && address <= 0x1F801128) {
		timers.write(address, value);
		return;
	}

	if (0x1F801800 <= address && address <= 0x1F801803) {
		cdrom.write(address, value);
		return;
	}

	if (0x1F801810 <= address && address <= 0x1F801814) {
		gpu.write(address, value);
		return;
	}

	if (0x1F801820 <= address && address <= 0x1F801824) {
		mdec.write(address, value);
		return;
	}

	if (0x1F801C00 <= address && address <= 0x1F801FFF) {
		spu.write(address, value);
		return;
	}

	if (0x1F802000 <= address && address <= 0x1F80207F) {
		expansion2.write(address, value);
		return;
	}

	if (address == 0x1FA00000) {
		expansion3.write(address, value);
		return;
	}
}
