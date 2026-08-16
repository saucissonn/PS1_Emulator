#pragma once

#include "ps1/io/gpu/gpu.hpp"
#include "ps1/io/memory_control.hpp"
#include "ps1/io/peripheral_io.hpp"
#include "ps1/io/interrupt_control.hpp"
#include "ps1/io/dma.hpp"
#include "ps1/io/timers.hpp"
#include "ps1/io/cdrom.hpp"
#include "ps1/io/mdec.hpp"
#include "ps1/io/spu.hpp"
#include "ps1/io/expansion.hpp"

class Io {
	public:
		Io();
		~Io();

		uint32_t read(uint32_t address);
		void write(uint32_t address, uint32_t value);

	private:
		MemoryControl1 memoryControl1;
		PeripheralIO peripheralIO;
		MemoryControl2 memoryControl2;
		InterruptControl interruptControl;
		Dma dma;
		Timers timers;
		Cdrom cdrom;
		Gpu gpu;
		Mdec mdec;
		Spu spu;

		ExpansionRegion1 expansion1;
		ExpansionRegion2 expansion2;
		ExpansionRegion3 expansion3;
};
