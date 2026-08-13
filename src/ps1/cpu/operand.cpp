#include "ps1/cpu/operand.hpp"

#include <stdlib.h>

Operand *operandCreate() {
	Operand *operand = (Operand *)malloc(sizeof(Operand));

	operand->rs = 0;
    operand->rt = 0;
    operand->rd = 0;
    operand->shamt = 0;
    operand->immediate = 0;
    operand->target = 0;

	return operand;
}
