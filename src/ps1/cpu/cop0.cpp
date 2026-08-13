#include "ps1/cpu/cop0.hpp"

#include <cstdlib>

TLBEntry *createTLBEntry() {
	TLBEntry *tlbe = (TLBEntry *)malloc(sizeof(TLBEntry));

	tlbe->VPN = 0;
    tlbe->PFN = 0;
    tlbe->C = 0;
    tlbe->D = 0;
    tlbe->V = 0;
    tlbe->G = 0;
    tlbe->ASID = 0;

	return tlbe;
}

Cop0::Cop0() {
	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}

	EntryHi = 0;
	EntryLo = 0;

	for (int i = 0; i < 64; i++) {
		TLB[i] = createTLBEntry();
	}

	operand = operandCreate();

    return;
}

Cop0::~Cop0() {
    for (int i = 0; i < 64; i++) {
        free(TLB[i]);
    }

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
