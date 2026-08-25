#include "ps1/cpu/cop2.hpp"

#include <stdlib.h>

#include "ps1/cpu/cpu.hpp"
#include "utils/error.hpp"

int Cop2::initRGBColors() {
	for (int i = 0; i < 3; i++) {
		RGBColors[i] = (RGBColor *)malloc(sizeof(RGBColor));\
		RGBColors[i]->r = 0x00;
        RGBColors[i]->g = 0x00;
        RGBColors[i]->b = 0x00;
	}

	return ERR_OK;
}

int Cop2::destroyRGBColors() {
	for (int i = 0; i < 3; i++) {
		free(RGBColors[i]);
	}

	return ERR_OK;
}

int Cop2::writeRGBColors(uint8_t r, uint8_t g, uint8_t b) {
	for (int i = 0; i < 2; i++) {
		RGBColors[i] = RGBColors[i + 1];
	}

	RGBColors[2]->r = r;
    RGBColors[2]->g = g;
    RGBColors[2]->b = b;

	return ERR_OK;
}

Cop2::Cop2(Cpu *cpu_) {
	cpu = cpu_;

	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}

	operand = operandCreate();
	initRGBColors();

    return;
}

Cop2::~Cop2() {
	free(operand);
	destroyRGBColors();

    return;
}
