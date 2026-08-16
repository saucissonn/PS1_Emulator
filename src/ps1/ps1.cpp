#include "ps1/ps1.hpp"

#include <stdio.h>

#include "utils/error.hpp"

Ps1::Ps1() :
	bus(),
	cpu(&bus),
	bios(),
	ram(),
	io()
{
	int ret = bios.load("src/ps1/roms/BIOS.bin");

	if (ret != ERR_OK) {
		return;
	}

	// Link everything to the bus
	bus.setCpu(&cpu);
	bus.setBios(&bios);
	bus.setRam(&ram);
	bus.setIo(&io);

	return;
}

Ps1::~Ps1() {
	return;
}

int Ps1::run() {
	while (1) {
		if (cpu.getInstructionCounter() > 100000) {
			return ERR_OK;
		}
		
		int ret = cpu.run();
		
		if (ret != ERR_OK) {
			return ret;
		}
	}
	return ERR_OK;
}
