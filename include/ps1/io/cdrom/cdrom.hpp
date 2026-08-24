#pragma once

#include <cstdint>
#include <queue>
#include <deque>

typedef struct {
	uint32_t id;
	uint32_t index;
	uint8_t minute; // Where it starts in absolute value
    uint8_t second;
    uint8_t frame;
} Track;

class Disc {
	public:
		Disc();
		~Disc();

		uint8_t intToBcd(uint8_t value);
		int putAddressInTrack(Track *track, uint32_t address);
		Track *createTrack(uint32_t id, uint32_t address);
		int destroyTracks();
		int createTracks();

		int load(const char *filename);
		uint8_t read(uint32_t address);
		uint32_t getMaxAddress();
		Track *getCurrentTrack();

	private:
		uint32_t sectorSize;
		uint32_t nbSector;
		uint32_t nbTrack;
		uint32_t maxAddress;
		Track *currentTrack;
		
		uint8_t *data;
		Track **tracks;
};

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

		int dmaWrite();

		int run();

		// Utils

        uint8_t readData(); // Pop and return data FIFO value
		uint8_t readResponse();

		uint8_t incrementBcd(uint8_t value); // Because it's hexa we increment from 0x09 to 0x10
		void incrementPosition();
		uint8_t bcdToInt(uint8_t value);
		uint8_t intToBcd(uint8_t value);
		uint32_t positionToAddress();
		void addressToPosition(uint32_t address);
		uint32_t getMaxAddress();
		Track *getCurrentTrack();
		void pushReport();

    private:
		Disc disc;
		Dma *dma;
		Bus *bus;
		InterruptController *interruptController;

        uint8_t index;
        uint8_t interruptEnable;
        uint8_t interruptFlag;
        uint8_t command;
		uint8_t longCommand; // Some commands take a while to execute
		uint8_t countLongCommandParameters;
        uint8_t request;
		uint8_t status;
		uint8_t targetMinute;
		uint8_t targetSecond;
		uint8_t targetFrame;

		std::queue<uint8_t> parameters;
		std::deque<uint8_t> longCommandParameters; // Used like a queue but not a queue to be able to read without modifying the queue
		std::queue<uint8_t> data; // Maybe uint16_t
		std::queue<uint8_t> response;

        uint8_t audioVolumeLeftToLeft;
        uint8_t audioVolumeLeftToRight;
        uint8_t audioVolumeRightToRight;
        uint8_t audioVolumeRightToLeft;

		// Commands

		int raiseInterrupt(CdromInterrupt type);

		int getStat(); // 0x01
		int setLoc(); // 0x02
		int play(); // 0x03

		int decodeCommand();
		int writeCommand(uint8_t value);

		int longCommandPlay();

		int decodeLongCommand();

        // Parameters

        uint8_t readParameters();
        int writeParameter(uint8_t value);
        uint8_t getParameterCount(uint8_t command);

		uint8_t readOnlyLongCommandParameters(uint32_t index);
		int pushLongCommandParameters(uint8_t value);
		int clearLongCommandParameters();

		// Requests

		uint8_t readRequest();
		int writeRequest(uint8_t value);
};
