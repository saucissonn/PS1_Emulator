#include "ps1/io/interrupt_controller.hpp"

#include "utils/error.hpp"

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

int InterruptController::writeStat(uint32_t value) {
	I_STAT &= value;

	return ERR_OK;
}

int InterruptController::writeMask(uint32_t value) {
	I_MASK = value;

	return ERR_OK;
}

int InterruptController::write(uint32_t address, uint32_t value) {
	if (address == 0x1F801070) {
		return writeStat(value);
	}

	if (address == 0x1F801074) {
		return writeMask(value);
	}

	return ERR_WRITE_SECTION_NOT_FOUND;
}

bool InterruptController::irqPending() {
	return (I_STAT & I_MASK) != 0;
}
