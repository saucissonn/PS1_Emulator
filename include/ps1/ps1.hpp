#pragma once

#include "ps1/cpu/cpu.hpp"
#include "ps1/bus.hpp"
#include "ps1/bios.hpp"
#include "ps1/ram.hpp"
#include "ps1/io/io.hpp"

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
};
