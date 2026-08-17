#include "ps1/io/gpu/gp1.hpp"

#include "utils/error.hpp"
#include "ps1/io/gpu/gpu.hpp"

Gp1::Gp1(Gpu *gpu_) {
	gpu = gpu_;

    return;
}

Gp1::~Gp1() {
    return;
}

uint32_t Gp1::read() {
	return gpu->getGpustat(); // TODO
}

int Gp1::write(uint32_t value) {
    command = value >> 24;
    parameter = value & 0x00FFFFFF;
	
	return decodeCommand();
}
