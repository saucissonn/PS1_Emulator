#pragma once

#include <cstdint>

class InterruptControl {
	public:
		InterruptControl();
		~InterruptControl();

		uint16_t read(uint32_t address);
		void write(uint32_t address, uint16_t value);

		void requestInterrupt(uint8_t source);

	private:
		uint16_t stat;
		uint16_t mask;
};
