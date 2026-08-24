#include "ps1/io/timers/timers.hpp"

#include <stdio.h>

#include "ps1/io/interrupt_controller.hpp"
#include "utils/error.hpp"

int Timers::setInterruptController(InterruptController *interruptController_) {
    if (!interruptController_) {
        return ERR_INVALID_ARGUMENT;
    }

    interruptController = interruptController_;

    return ERR_OK;
}

Timers::Timers() {
    for (int i = 0; i < 3; i++) {
		timers[i].accumulatorCounter = 0;
        timers[i].counter = 0;
        timers[i].mode = 0;
        timers[i].target = 0;
    }
}

Timers::~Timers() {
    return;
}

uint16_t Timers::read(uint32_t address) {
    if (address >= 0x1F801100 && address <= 0x1F801128) {
        uint32_t timer = (address - 0x1F801100) / 0x10;
        uint32_t offset = (address - 0x1F801100) % 0x10;

        switch (offset) {
            case 0x0:
                return timers[timer].counter;

            case 0x4:
                return timers[timer].mode;

            case 0x8:
                return timers[timer].target;
        }
    }

    return 0;
}

int Timers::write(uint32_t address, uint16_t value) {
    if (address >= 0x1F801100 && address <= 0x1F801128) {
        uint32_t timer = (address - 0x1F801100) / 0x10;
        uint32_t offset = (address - 0x1F801100) % 0x10;

        switch (offset) {
            case 0x0:
                timers[timer].counter = value;
                return ERR_OK;

            case 0x4:
                timers[timer].mode = value;
                return ERR_OK;

            case 0x8:
                timers[timer].target = value;
                return ERR_OK;
        }
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}

int Timers::requestInterrupt(uint8_t timer) {
	switch (timer) {
		case 0x00:
			interruptController->request(Interrupt::TIMER0);
			break;
		case 0x01:
			interruptController->request(Interrupt::TIMER1);
			break;
		case 0x02:
			interruptController->request(Interrupt::TIMER2);
			break;
	}

	return ERR_OK;
}

int Timers::tickCounter(uint8_t timer) {
    timers[timer].counter += 1;

    if (timers[timer].counter == timers[timer].target) {
        setReachedTarget(timer, true);

        if (getIrqTargetEnable(timer)) {
			requestInterrupt(timer);
        }

        if (getResetMode(timer)) {
            timers[timer].counter = 0;
        }
    }

    if (timers[timer].counter == 0xFFFF) {
        setReachedOverflow(timer, true);

        if (getIrqOverflowEnable(timer)) {
			requestInterrupt(timer);
        }

        if (!getResetMode(timer)) {
            timers[timer].counter = 0;
        }
    }

	return ERR_OK;
}

int Timers::tickSystemClock(uint32_t cycles) { // For timer 2 (Linked to the CPU)
    timers[2].accumulatorCounter += cycles;

    if (getClockSource(2) > 1) {
        uint32_t ticks = timers[2].accumulatorCounter / 8;
        timers[2].accumulatorCounter %= 8;

        for (uint32_t i = 0; i < ticks; i++) {
            tickCounter(2);
        }
    }
    else {
        uint32_t ticks = timers[2].accumulatorCounter;
        timers[2].accumulatorCounter = 0;

        for (uint32_t i = 0; i < ticks; i++) {
            tickCounter(2);
        }
    }

	printf("Timer 2: %04d\n", timers[2].counter);

    return ERR_OK;
}

//timers->onHBlank();
//timers->onVBlank();
//timers->tickDotClock(clocks);
