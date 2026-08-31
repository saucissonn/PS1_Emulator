#include "ps1/io/memory_control/memory_control2.hpp"

#include "utils/error.hpp"

MemoryControl2::MemoryControl2() {
	ramSize = 0;
}

MemoryControl2::~MemoryControl2() {
	return;
}

uint32_t MemoryControl2::read(uint32_t address) {
	if (address == 0x1F801060) {
		return ramSize;
	}

	return 0;
}

int MemoryControl2::write(uint32_t address, uint32_t value) {
    if (address == 0x1F801060) {
        ramSize = value;
		return ERR_OK;
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}
