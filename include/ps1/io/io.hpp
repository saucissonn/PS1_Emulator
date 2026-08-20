#pragma once

#include "ps1/io/gpu/gpu.hpp"
#include "ps1/io/memory_control.hpp"
#include "ps1/io/peripheral_io.hpp"
#include "ps1/io/interrupt_control.hpp"
#include "ps1/io/dma.hpp"
#include "ps1/io/timers.hpp"
#include "ps1/io/cdrom/cdrom.hpp"
#include "ps1/io/mdec.hpp"
#include "ps1/io/spu.hpp"

class Bus;
class InterruptController;

class Io {
	public:
		Io();
		~Io();

		int setInterruptController(InterruptController *interruptController_);
		int setBus(Bus *bus_);

		uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);
		int write8Only(uint32_t address, uint8_t value);

		int dmaRun();

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
		MemoryControl3 memoryControl3;

		Bus *bus;
		InterruptController *interruptController;
};
