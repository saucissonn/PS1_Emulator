#include "ps1/cpu/cpu.hpp"

#include <stdio.h>

#include "utils/error.hpp"

int Cpu::raiseException(Exception exception) { // Some instructions can call exceptions
    if (exception == Exception::IntegerOverflow) {
		if (inDelaySlot) {
			cop0.setEPCRegister(prevPC); // Put PC of the branch / jump
			cop0.setCauseRegisterBD(1);
		}
		else {
			cop0.setEPCRegister(instructionPC); // Put old PC
			cop0.setCauseRegisterBD(0);
		}
        cop0.setCauseRegisterExCode(12);
		cop0.setSRRegisterIEc(0); // Disable current interrupt
        cop0.setSRRegisterKUc(0); // Kernel mode
        PC = 0x80000080; // TODO Sometimes different but enough for now

        printf("Exception: Overflow\n");
        return ERR_OK;
    }

    return ERR_OK;
}
