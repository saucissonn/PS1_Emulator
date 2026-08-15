#include "ps1/ps1.hpp"

#include "utils/error.hpp"

Ps1::Ps1() :
	bus(),
	cpu(&bus),
	bios()
	
{
	int ret = bios.load("src/ps1/roms/test.bin");

	if (ret != ERR_OK) {
		return;
	}

	// Link everything to the bus
	bus.setCpu(&cpu);
	bus.setBios(&bios);

	return;
}

Ps1::~Ps1() {
	return;
}

int Ps1::run() {
	while (1) {
		if (cpu.getInstructionCounter() > 100) {
			return ERR_OK;
		}
		
		int ret = cpu.run();

		if (ret != ERR_OK) {
			return ret;
		}
	}
	return ERR_OK;
}
