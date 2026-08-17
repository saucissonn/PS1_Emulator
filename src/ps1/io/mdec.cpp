#include "ps1/io/mdec.hpp"

#include "utils/error.hpp"

Mdec::Mdec() {
    data = 0;
    status = 0;
    control = 0;
}

Mdec::~Mdec() {
    return;
}

uint32_t Mdec::read(uint32_t address) {
    switch (address) {
        case 0x1F801820:
            return data;

        case 0x1F801824:
            return status;
    }

    return 0;
}

int Mdec::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1F801820:
            data = value;
            return ERR_OK;

        case 0x1F801824:
            control = value;
            return ERR_OK;
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}
