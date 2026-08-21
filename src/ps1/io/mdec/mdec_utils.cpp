#include "ps1/io/mdec/mdec.hpp"

#include "utils/error.hpp"

uint8_t Mdec::getCommand() {
	uint32_t command = dataIn.front();
	command >>= 29;

	return (uint8_t)command;
}

uint16_t Mdec::getNbParameterCommand1() {
	uint32_t command = dataIn.front();
	command &= 0xFFFF;
	
	return (uint16_t)command;
}

uint8_t Mdec::getNbParameterCommand2() {
    uint32_t command = dataIn.front();
    command &= 0x01;

	if (command) {
		return 128;
	}
	
    return 64;
}

