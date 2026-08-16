#pragma once

#include <cstdint>

class MemoryControl1 {
	public:
		MemoryControl1();
		~MemoryControl1();

		uint32_t read(uint32_t address);
		void write(uint32_t address, uint32_t value);

	private:
		uint32_t expansion1Base;
		uint32_t expansion2Base;
		uint32_t expansion1DelaySize;
		uint32_t expansion3DelaySize;
		uint32_t biosRomDelaySize;
		uint32_t spuDelay;
		uint32_t cdromDelay;
		uint32_t expansion2DelaySize;
		uint32_t commonDelay;
};
