#include "ps1/io/gpu/gp1.hpp"

Gp1::Gp1(Gpu *gpu_) {
	gpu = gpu_;

    return;
}

Gp1::~Gp1() {
    return;
}

uint32_t Gp1::read(uint32_t address) {
    return address; // TODO
}

void Gp1::write(uint32_t address, uint32_t value) {
	if (0x1F801814 != address) {
		return;
	}

    instruction = value;
}
