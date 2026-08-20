#include "ps1/cpu/cpu.hpp"

#include <stdio.h>
#include <cstdlib>

#include "ps1/interrupt_controller.hpp"
#include "utils/error.hpp"

bool Cpu::launchInterrupt() {
	return (interruptController->irqPending() && cop0.getStatusRegisterIP2() && cop0.getStatusRegisterIEp());
}

void Cpu::updateInterrupt() {
    cop0.setCauseRegisterIP2(interruptController->irqPending());
}

int Cpu::handleInterrupt() {
	return raiseException(Exception::Interrupt);
}
