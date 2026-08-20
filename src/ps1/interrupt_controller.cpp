#include "ps1/interrupt_controller.hpp"

InterruptController::InterruptController() {
	return;
}

InterruptController::~InterruptController() {
	return;
}

void InterruptController::request(Interrupt source) {
	I_STAT |= (uint32_t)source;
}

void InterruptController::clear(Interrupt source) {
	I_STAT &= ~(uint32_t)source;
}

void InterruptController::writeStat(uint32_t value) {
	I_STAT &= value;
}

void InterruptController::writeMask(uint32_t value) {
	I_MASK = value;
}

bool InterruptController::irqPending() {
	return (I_STAT & I_MASK) != 0;
}
