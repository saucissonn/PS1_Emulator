#pragma once

#include <cstdint>
#include <queue>

class Dma;
class Bus;

class Mdec {
    public:
        Mdec();
        ~Mdec();

		int setDma(Dma *dma_);
		int setBus(Bus *bus);

        uint32_t readOut();
        uint32_t read(uint32_t address);
		int writeIn(uint32_t value);
		int write(uint32_t address, uint32_t value);
        int dmaWriteIn();
        int dmaWriteOut();

    private:
		Dma *dma;
		Bus *bus;

		std::queue<uint32_t> dataIn;
		std::queue<uint32_t> dataOut;

        uint32_t status;
        uint32_t control;

        // Commands

        uint32_t readParameter();
		uint32_t getParameterCount();
        int decodeCommand();

		// Utils

		uint8_t getCommand();
		uint16_t getNbParameterCommand1();
		uint8_t getNbParameterCommand2();
};
