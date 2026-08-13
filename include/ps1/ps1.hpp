#pragma once

#include "ps1/cpu/cpu.hpp"
#include "ps1/bus.hpp"

class Ps1 {
	public:
		Ps1();
		~Ps1();

		int run();

	private:
		Bus bus;
        Cpu cpu;
};
