#include "ps1/io/gpu/gpu.hpp"

Gpu::Gpu() {
	vramSize = 0x100000;
	vram = (uint8_t *)calloc(vramSize, sizeof(uint8_t));

	return;
}

Gpu::~Gpu() {
	free(vram);

	return;
}
