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

	cpu.setInterruptController(io.getInterruptController());

	io.setBus(&bus);

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
	int ret = ERR_OK;

	while (1) {
		uint64_t count = cpu.getInstructionCounter();

		if (count > 100000) { // 17381 (nb instructions to check a non connected hardware) 
			return ERR_OK;
		}
	
		ret = io.dmaRun(); // DMA (not tested yet)

        if (ret != ERR_OK) {
            return ret;
        }

		printf("\n%ld\n", count);
		ret = cpu.run();

		if (ret != ERR_OK) {
			return ret;
		}
	}
	return ERR_OK;
}
