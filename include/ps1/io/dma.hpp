#pragma once

#include <cstdint>

struct DMAChannel {
	uint32_t MADR;	// Base address
	uint32_t BCR;	// Nb of elements
	uint32_t CHCR;	// Additional info
};

class Mdec;
class Gpu;
class Cdrom;
class Spu;
class Bus;

class Dma {
	public:
		Dma();
		~Dma();

	    int setMdec(Mdec *mdec_);
	    int setGpu(Gpu *gpu_);
	    int setCdrom(Cdrom *cdrom_);
	    int setSpu(Spu *spu_);
		int setBus(Bus *bus_);

		uint32_t read(uint32_t address);
		int write(uint32_t address, uint32_t value);

		void setChannelMasterIndex();

		int decodeSyncMode();
		int run();

		// Utils

		uint32_t getMADR(uint8_t channel);
		uint32_t getBCR(uint8_t channel);
		uint32_t getCHCR(uint8_t channel);
		uint8_t getChannelMasterIndex();

		uint8_t getChannelTransferDirection(uint8_t channel);
		uint8_t getChannelMemoryAddressStep(uint8_t channel);
		uint8_t getChannelChoppingEnable(uint8_t channel);
		uint8_t getChannelSyncMode(uint8_t channel);
		uint8_t getChannelChoppingDmaWindowSize(uint8_t channel);
		uint8_t getChannelChoppingCpuWindowSize(uint8_t channel);
		bool getChannelStartBusy(uint8_t channel);
		bool getChannelStartTrigger(uint8_t channel);
		bool getChannelUnknown29(uint8_t channel);
		bool getChannelUnknown30(uint8_t channel);
		uint8_t getDmaPriority(uint8_t channel);
		bool getDmaMasterEnable(uint8_t channel);
		uint8_t getDmaUnknownPriority();
		bool getDmaUnknown31();
		uint8_t getDicrUnknown();
		bool getDicrForceIrq();
		bool getDicrIrqEnable(uint8_t channel);
		bool getDicrIrqMasterEnable();
		bool getDicrIrqFlag(uint8_t channel);
		bool getDicrIrqSignal();

		void setMADR(uint32_t value, uint8_t channel);

		void setChannelTransferDirection(uint8_t channel, uint8_t value);
		void setChannelMemoryAddressStep(uint8_t channel, uint8_t value);
		void setChannelChoppingEnable(uint8_t channel, uint8_t value);
		void setChannelSyncMode(uint8_t channel, uint8_t value);
		void setChannelChoppingDmaWindowSize(uint8_t channel, uint8_t value);
		void setChannelChoppingCpuWindowSize(uint8_t channel, uint8_t value);
		void setChannelStartBusy(uint8_t channel, bool value);
		void setChannelStartTrigger(uint8_t channel, bool value);
		void setChannelUnknown29(uint8_t channel, bool value);
		void setChannelUnknown30(uint8_t channel, bool value);
		void setDmaPriority(uint8_t channel, uint8_t value);
		void setDmaMasterEnable(uint8_t channel, bool value);
		void setDmaUnknownPriority(uint8_t value);
		void setDmaUnknown31(bool value);
		void setDicrUnknown(uint8_t value);
		void setDicrForceIrq(bool value);
		void setDicrIrqEnable(uint8_t channel, bool value);
		void setDicrIrqMasterEnable(bool value);
		void setDicrIrqFlag(uint8_t channel, bool value);
		void setDicrIrqSignal(bool value);

	private:
		Mdec *mdec;
		Gpu *gpu;
		Cdrom *cdrom;
		Spu *spu;

		Bus *bus;

		DMAChannel channels[7];

		uint32_t dpcr; // 1F8010F0 - DMA Control Register
		uint32_t dicr; // 1F8010F4 - DMA Interrupt Register

		int channelMasterIndex;
		int dmaError;

		int runManual();
		int runBlock();
};
