#include "ps1/io/io.hpp"

Io::Io() :
	memoryControl1(),
	peripheralIO(),
	gpu()
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

	else if (0x1F801040 <= address && address <= 0x1F80105E) {
        return peripheralIO.read(address);
    }

    return 0;
}

void Io::write(uint32_t address, uint32_t value) {
    if (0x1F801000 <= address && address <= 0x1F801020) {
        memoryControl1.write(address, value);
        return;
    }

    else if (0x1F801040 <= address && address <= 0x1F80105E) {
		peripheralIO.write(address, value);
        return;
    }
}
