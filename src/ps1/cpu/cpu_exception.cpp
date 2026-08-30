#include "ps1/cpu/cpu.hpp"

#include <stdio.h>

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

    if (cop0.getStatusRegisterBEV() == 0) {
        nextPC = 0x80000080; // normal exception vector
	}
    else {
        nextPC = 0xBFC00180; // bios exception vector
	}

	printf("exception handled\n");

    return ERR_OK;
}

bool Cpu::errorRaiseException(int error) {
	switch (error) {
		case ERR_WRITE_SECTION_NOT_CONNECTED: return false;
		case ERR_READ_SECTION_NOT_CONNECTED: return false;
		case ERR_BUS_SECTION_NOT_CONNECTED: return false;
	}
	return true;
}

int Cpu::handleErrorOnRW(int error, uint32_t address) {
    if (error != ERR_OK) { 
        bus->setBusError(ERR_OK);

        if (errorRaiseException(error)) {
            cop0.setBadVaddr(address);
            return raiseException(Exception::BusErrorData);
        }
    }

	return ERR_OK;
}
