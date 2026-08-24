#pragma once

#include <cstdint>

struct Timer {
	uint32_t accumulatorCounter; // Store temp values
    uint16_t counter;
    uint16_t mode;
    uint16_t target;
};

class InterruptController;

class Timers {
    public:
        Timers();
        ~Timers();

		int setInterruptController(InterruptController *interruptController_);

        uint16_t read(uint32_t address);
        int write(uint32_t address, uint16_t value);

		int requestInterrupt(uint8_t timer);
		int tickCounter(uint8_t timer);
		int tickIncrement(uint8_t timer, uint32_t ticks);
		int tickDotClock(uint32_t cycles); // timer 0
		int tickHBlank(); // timer 1
		int tickSystemClock8(uint32_t cycles); // timer 2
		int tickSystemClock(uint32_t cycles); // 3 timers

		// Utils

        uint16_t getCounter(uint8_t timer);
        uint16_t getMode(uint8_t timer);
        uint16_t getTarget(uint8_t timer);
        bool getSynchronizationEnable(uint8_t timer);
        uint8_t getSynchronizationMode(uint8_t timer);
        bool getResetMode(uint8_t timer);
        bool getIrqTargetEnable(uint8_t timer);
        bool getIrqOverflowEnable(uint8_t timer);
        bool getIrqRepeat(uint8_t timer);
        bool getIrqToggle(uint8_t timer);
        uint8_t getClockSource(uint8_t timer);
        bool getInterruptRequest(uint8_t timer);
        bool getReachedTarget(uint8_t timer);
        bool getReachedOverflow(uint8_t timer);

        void setCounter(uint8_t timer, uint16_t value);
        void setMode(uint8_t timer, uint16_t value);
        void setTarget(uint8_t timer, uint16_t value);
        void setSynchronizationEnable(uint8_t timer, bool value);
        void setSynchronizationMode(uint8_t timer, uint8_t value);
        void setResetMode(uint8_t timer, bool value);
        void setIrqTargetEnable(uint8_t timer, bool value);
        void setIrqOverflowEnable(uint8_t timer, bool value);
        void setIrqRepeat(uint8_t timer, bool value);
        void setIrqToggle(uint8_t timer, bool value);
        void setClockSource(uint8_t timer, uint8_t value);
        void setInterruptRequest(uint8_t timer, bool value);
        void setReachedTarget(uint8_t timer, bool value);
        void setReachedOverflow(uint8_t timer, bool value);

    private:
		InterruptController *interruptController;

        Timer timers[3];
};
