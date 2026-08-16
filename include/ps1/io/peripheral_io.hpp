#pragma once

#include <cstdint>

class PeripheralIO {
	public:
		PeripheralIO();
		~PeripheralIO();

		uint32_t read(uint32_t address);
		void write(uint32_t address, uint32_t value);

	private:
		uint32_t joyData;
		uint32_t joyStat;
		uint32_t joyMode;
		uint32_t joyCtrl;
		uint32_t joyBaud;

		uint32_t sioData;
		uint32_t sioStat;
		uint32_t sioMode;
		uint32_t sioCtrl;
		uint32_t sioMisc;
		uint32_t sioBaud;
};
