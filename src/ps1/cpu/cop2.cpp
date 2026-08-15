#include "ps1/cpu/cop2.hpp"

#include <cstdlib>

#include "ps1/cpu/cpu.hpp"

Cop2::Cop2(Cpu *cpu_) {
	cpu = cpu_;

	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}

	operand = operandCreate();

    return;
}

Cop2::~Cop2() {
	free(operand);

    return;
}
