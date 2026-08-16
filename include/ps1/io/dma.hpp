#pragma once

#include <cstdint>

struct DMAChannel {
	uint32_t baseAddress;
	uint32_t blockControl;
	uint32_t channelControl;
};

class Dma {
	public:
		Dma();
		~Dma();

		uint32_t read(uint32_t address);
		void write(uint32_t address, uint32_t value);

	private:
		DMAChannel channels[7];

		uint32_t dpcr; // 1F8010F0 - DMA Control Register
		uint32_t dicr; // 1F8010F4 - DMA Interrupt Register
};
