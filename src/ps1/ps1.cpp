#include "ps1/ps1.hpp"

Ps1::Ps1()
    : bus(),
      cpu(&bus)
{
	// Link everything to the bus
	bus.setCpu(&cpu);

	return;
}

Ps1::~Ps1() {
	return;
}

int Ps1::run() {
	cpu.run();
	return 0;
}
