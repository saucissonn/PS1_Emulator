#include "ps1/ps1.hpp"

#include <stdio.h>

#include "utils/error.hpp"

Ps1::Ps1() :
	bus(),
	cpu(&bus),
	bios(),
	ram(),
	io(),
    expansion1(),
    expansion2(),
    expansion3()
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
	bus.setExpansion1(&expansion1);
    bus.setExpansion2(&expansion2);
    bus.setExpansion3(&expansion3);

	return;
}

Ps1::~Ps1() {
	return;
}

int Ps1::run() {
	while (1) {
		uint64_t count = cpu.getInstructionCounter();

		if (count > 18000) {
			return ERR_OK;
		}
		
		printf("%ld\n", count);

		int ret = cpu.run();
		
		if (ret != ERR_OK) {
			return ret;
		}
	}
	return ERR_OK;
}
