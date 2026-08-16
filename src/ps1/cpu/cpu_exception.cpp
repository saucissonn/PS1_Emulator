#include "ps1/cpu/cpu.hpp"

#include "utils/error.hpp"

int Cpu::raiseException(Exception exception) { // Some instructions can call exceptions
    cop0.setCauseRegisterExCode((uint8_t)exception);
    cop0.setStatusRegisterIEo(cop0.getStatusRegisterIEp());
    cop0.setStatusRegisterKUo(cop0.getStatusRegisterKUp());
    cop0.setStatusRegisterIEp(cop0.getStatusRegisterIEc());
    cop0.setStatusRegisterKUp(cop0.getStatusRegisterKUc());
    cop0.setStatusRegisterIEc(0); // Disable current interrupt
    cop0.setStatusRegisterKUc(0); // Kernel mode

	if (inDelaySlot) {
		cop0.setEPCRegister(prevPC); // Put PC of the branch / jump
		cop0.setCauseRegisterBD(1);
	}
	else {
		cop0.setEPCRegister(instructionPC); // Put old PC
		cop0.setCauseRegisterBD(0);
	}

    // else if (exception == Exception::CoprocessorUnusable){
    //     // TODO but very unlikely to be useful
    //     // make a function setCauseRegisterCE(coprocessor id)
    // }

    if (cop0.getStatusRegisterBEV() == 0)
        PC = 0x80000080; // normal exception vector
    else
        PC = 0xBFC00180; // bios exceptoin vector

    return ERR_OK;
}
