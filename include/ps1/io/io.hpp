#pragma once

#include "ps1/io/gpu/gpu.hpp"
#include "ps1/io/memory_control.hpp"
#include "ps1/io/peripheral_io.hpp"

class Io {
	public:
		Io();
		~Io();

		uint32_t read(uint32_t address);
		void write(uint32_t address, uint32_t value);

	private:
		MemoryControl1 memoryControl1;
		PeripheralIO peripheralIO;
		Gpu gpu;
};
