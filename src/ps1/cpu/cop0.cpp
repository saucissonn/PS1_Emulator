#include "ps1/cpu/cop0.hpp"

#include <cstdlib>


Cop0::Cop0() {
	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}

	EntryHi = 0;
	EntryLo = 0;


	operand = operandCreate();

    return;
}

Cop0::~Cop0() {

	free(operand);

    return;
}

void Cop0::setCauseRegister(uint32_t value) {
	GPR[13] = value;
}

void Cop0::setCauseRegisterExCode(uint8_t value) {
    GPR[13] &= ~(0b1111100); // Clear area
	GPR[13] |= (uint32_t)(value << 2);
}

void Cop0::setEPCRegister(uint32_t value) {
    GPR[14] = value;
}

void Cop0::setSRRegisterIEc(uint8_t value) {
    GPR[12] &= ~(0b1); // Clear area
    GPR[12] |= (uint32_t)(value);
}

void Cop0::setSRRegisterKUc(uint8_t value) {
    GPR[12] &= ~(0b10); // Clear area
    GPR[12] |= (uint32_t)(value);
}
