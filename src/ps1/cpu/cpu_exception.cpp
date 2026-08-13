#include "ps1/cpu/cpu.hpp"

#include <stdio.h>

#include "utils/error.hpp"

int Cpu::raiseException(Exception exception) {
    if (exception == Exception::IntegerOverflow) {
        cop0.setCauseRegisterExCode(12);
        cop0.setEPCRegister(instructionPC); // Put old PC
        cop0.setSRRegisterIEc(0); // Disable current interrupt
        cop0.setSRRegisterKUc(0); // Kernel mode
        PC = 0x80000080; // TODO Sometimes different but enough for now

        printf("Overflow\n");
        return ERR_OK;
    }

    return ERR_OK;
}
