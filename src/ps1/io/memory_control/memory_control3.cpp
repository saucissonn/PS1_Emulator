#include "ps1/io/memory_control/memory_control3.hpp"

#include "utils/error.hpp"

MemoryControl3::MemoryControl3() {
    cacheControl = 0;
}

MemoryControl3::~MemoryControl3() {
    return;
}

uint32_t MemoryControl3::read(uint32_t address) {
    if (address == 0xFFFE0130) {
        return cacheControl;
    }

    return 0;
}

int MemoryControl3::write(uint32_t address, uint32_t value) {
    if (address == 0xFFFE0130) {
        cacheControl = value;
        return ERR_OK;
    }

    return ERR_WRITE_SECTION_NOT_FOUND;
}

