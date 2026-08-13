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
    return;
}
