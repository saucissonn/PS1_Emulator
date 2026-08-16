#include "ps1/cpu/cop0.hpp"

#include <cstdlib>

#include "ps1/cpu/cpu.hpp"


Cop0::Cop0(Cpu *cpu_)
{
	cpu = cpu_;

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
