#include "ps1/bus.hpp"

int Bus::setCpu(Cpu *cpu_) {
	cpu = cpu_;

	return 0;
}

Bus::Bus() {
	return;
}

Bus::~Bus() {
    return;
}
