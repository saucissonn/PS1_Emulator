#pragma once

#include <cstdint>

#include "ps1/io/gpu/gp0.hpp"
#include "ps1/io/gpu/gp1.hpp"

class InterruptController;
class Bus;
class Dma;

class Gpu {
    public:
        Gpu();
        ~Gpu();

		int setInterruptController(InterruptController *interruptController_);
		int setBus(Bus *bus_);
		int setDma(Dma *dma_);

        uint32_t read(uint32_t address);
        int write(uint32_t address, uint32_t value);

		int dmaWriteBlock();
		int dmaWriteLinkedList();

		// Utils

		int resetCommandBuffer();

		uint32_t getGpuread();
        uint32_t getGpustat();

		uint16_t getDisplayStartX();
		uint16_t getDisplayStartY();
		uint16_t getDisplayX1();
		uint16_t getDisplayX2();
		uint16_t getDisplayY1();
		uint16_t getDisplayY2();
        uint8_t getGpustatPageX();
        bool getGpustatPageY();
        uint8_t getGpustatSemiTransparency();
        uint8_t getGpustatTexturePageColors();
        bool getGpustatDither();
        bool getGpustatInterlaceDrawing();
        bool getGpustatSetMaskBit();
        bool getGpustatDrawPixels();
        bool getGpustatInterlaceField();
        bool getGpustatReverseflag();
        bool getGpustatPageYBit9();
        bool getGpustatHorizontalResolution2();
        uint8_t getGpustatHorizontalResolution1();
        bool getGpustatVerticalResolution();
        bool getGpustatVideoMode();
        bool getGpustatDisplayAreaColorDepth();
        bool getGpustatVerticalInterlace();
        bool getGpustatDisplayEnable();
        bool getGpustatInterruptRequest();
        bool getGpustatDmaDataRequest();
        bool getGpustatReadyToReceiveCmdWord();
        bool getGpustatReadFifoDataAvailable();
        bool getGpustatWriteFifoEmpty();
        uint8_t getGpustatDmaDirection();
        bool getGpustatDrawingLine();

		void setDisplayStartX(uint16_t value);
		void setDisplayStartY(uint16_t value);
		void setDisplayX1(uint16_t value);
		void setDisplayX2(uint16_t value);
		void setDisplayY1(uint16_t value);
		void setDisplayY2(uint16_t value);
		void setGpustatPageX(uint8_t value);
        void setGpustatPageY(bool value);
        void setGpustatSemiTransparency(uint8_t value);
        void setGpustatTexturePageColors(uint8_t value);
        void setGpustatDither(bool value);
        void setGpustatInterlaceDrawing(bool value);
        void setGpustatSetMaskBit(bool value);
        void setGpustatDrawPixels(bool value);
        void setGpustatInterlaceField(bool value);
        void setGpustatReverseflag(bool value);
        void setGpustatPageYBit9(bool value);
        void setGpustatHorizontalResolution2(bool value);
        void setGpustatHorizontalResolution1(uint8_t value);
        void setGpustatVerticalResolution(bool value);
        void setGpustatVideoMode(bool value);
        void setGpustatDisplayAreaColorDepth(bool value);
        void setGpustatVerticalInterlace(bool value);
        void setGpustatDisplayEnable(bool value);
        void setGpustatInterruptRequest(bool value);
        void setGpustatDmaDataRequest(bool value);
        void setGpustatReadyToReceiveCmdWord(bool value);
        void setGpustatReadFifoDataAvailable(bool value);
        void setGpustatWriteFifoEmpty(bool value);
        void setGpustatDmaDirection(uint8_t value);
        void setGpustatDrawingLine(bool value);

    private:
        Gp0 gp0;
        Gp1 gp1;
		InterruptController *interruptController;
		Bus *bus;
		Dma *dma;

        uint32_t gpuread;
        uint32_t gpustat;

		// VRAM position
		uint16_t displayStartX;
		uint16_t displayStartY;

		// Window
		uint16_t displayX1;
        uint16_t displayX2;
        uint16_t displayY1;
        uint16_t displayY2;
};
