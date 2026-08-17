#include "ps1/io/gpu/gpu.hpp"

#include "utils/error.hpp"

Gpu::Gpu() :
	gp0(this),
	gp1(this)
{
    gpuread = 0;
    gpustat = 0;
}

Gpu::~Gpu() {
    return;
}

uint32_t Gpu::read(uint32_t address) {
    switch (address) {
        case 0x1F801810:
            return gp0.read();

        case 0x1F801814:
            return gp1.read();
    }

    return 0;
}

int Gpu::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1F801810:
			gp0.write(value);
            return ERR_OK;

        case 0x1F801814:
            gp1.write(value);
            return ERR_OK;
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}
