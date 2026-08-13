#include "ps1/cpu/cop2.hpp"

Cop2::Cop2() {
	for (int i = 0; i < 32; i++) {
		GPR[i] = 0;
	}

	operand = operandCreate();

    return;
}

Cop2::~Cop2() {
    return;
}
