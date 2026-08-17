#pragma once

#include <cstdint>

#include "ps1/io/gpu/gp0.hpp"
#include "ps1/io/gpu/gp1.hpp"

class Gpu {
    public:
        Gpu();
        ~Gpu();

        uint32_t read(uint32_t address);
        int write(uint32_t address, uint32_t value);

		// Utils

		int resetCommandBuffer();

		uint32_t getGpuread();
        uint32_t getGpustat();

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

        uint32_t gpuread;
        uint32_t gpustat;
};
