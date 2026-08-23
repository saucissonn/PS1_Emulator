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
    operand->funct = 0;

    operand->command = 0;
    operand->lm = 0;
    operand->mvmva_tv = 0;
    operand->mvmva_mv = 0;
    operand->mvmva_mm = 0;
    operand->sf = 0;

    return operand;
}
