#include "ps1/io/gpu/gpu.hpp"

Gpu::Gpu() :
	gp0(this),
	gp1(this)
{
    gpuRead = 0;
    gpuStat = 0;
}

Gpu::~Gpu() {
    return;
}

uint32_t Gpu::read(uint32_t address) {
    switch (address) {
        case 0x1F801810:
            return gpuRead;

        case 0x1F801814:
            return gpuStat;
    }

    return 0;
}

void Gpu::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1F801810:
			gp0.write(address, value);
            return;

        case 0x1F801814:
            gp1.write(address, value);
            return;
    }
}
