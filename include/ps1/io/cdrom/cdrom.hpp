#pragma once

#include <cstdint>
#include <queue>

enum class CdromInterrupt { // commands returned value, we actually return error but if no error occurs we put this value in interruptFlag
    INT1 = 1,
    INT2 = 2,
    INT3 = 3,
    INT4 = 4,
    INT5 = 5
};

class Dma;
class Bus;
class InterruptController;

class Cdrom {
    public:
        Cdrom();
        ~Cdrom();

		int setInterruptController(InterruptController *interruptController_);
		int setDma(Dma *dma_);
		int setBus(Bus *bus_);

        uint8_t read(uint32_t address);
        int write(uint32_t address, uint8_t value);

		uint8_t readData(); // Pop and retuen data FIOF value
		int dmaWrite();

    private:
		Dma *dma;
		Bus *bus;
		InterruptController *interruptController;

        uint8_t index;

        uint8_t interruptEnable;
        uint8_t interruptFlag;

        uint8_t command;
        uint8_t request;

		std::queue<uint8_t> parameters;
		std::queue<uint8_t> data; // Maybe uint16_t
		std::queue<uint8_t> response;

        uint8_t audioVolumeLeftToLeft;
        uint8_t audioVolumeLeftToRight;
        uint8_t audioVolumeRightToRight;
        uint8_t audioVolumeRightToLeft;

		// Commands

		int raiseInterrupt(CdromInterrupt type);

		int decodeCommand();
		int writeCommand(uint8_t value);

        // Parameters

        uint8_t readParameter();
        int writeParameter(uint8_t value);
        uint8_t getParameterCount(uint8_t command);

		// Requests

		uint8_t readRequest();
		int writeRequest(uint8_t value);
};
