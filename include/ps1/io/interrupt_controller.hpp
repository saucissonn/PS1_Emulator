#pragma once

#include <cstdint>

enum class Interrupt : uint8_t {
    VBLANK = 1 << 0,
    GPU = 1 << 1,
    CDROM = 1 << 2,
    DMA = 1 << 3,
    TIMER0 = 1 << 4,
    TIMER1 = 1 << 5,
    TIMER2 = 1 << 6,
    PAD = 1 << 7,
};

class InterruptController {
	public:
		InterruptController();
		~InterruptController();

	    void request(Interrupt source);
		void clear(Interrupt source);
	    int writeStat(uint32_t value);
	    int writeMask(uint32_t value);
		int write(uint32_t address, uint32_t value);

		bool irqPending();

	private:
		uint32_t I_STAT;
		uint32_t I_MASK;
};
