#pragma once

#include "ps1/cpu/cpu.hpp"
#include "ps1/bus.hpp"
#include "ps1/bios.hpp"
#include "ps1/ram.hpp"
#include "ps1/io/io.hpp"
#include "ps1/expansion.hpp"
#include "ps1/interrupt_controller.hpp"

class Ps1 {
	public:
		Ps1();
		~Ps1();

		int run();

	private:
		Bus bus;
        Cpu cpu;
		Bios bios;
		Ram ram;
		Io io;
		ExpansionRegion1 expansion1;
		ExpansionRegion2 expansion2;
		ExpansionRegion3 expansion3;
		InterruptController interruptController;
};
