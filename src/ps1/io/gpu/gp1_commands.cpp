#include "ps1/io/gpu/gp1.hpp"

#include "utils/error.hpp"
#include "ps1/io/gpu/gpu.hpp"

int Gp1::resetCommandBuffer() {
	gpu->resetCommandBuffer();

	return ERR_OK;
}

int Gp1::acknowledgeGpuInterrupt() {
    gpu->setGpustatInterruptRequest(0);

    return ERR_OK;
}

int Gp1::displayEnable() {
	if (command & 1) {
		gpu->setGpustatDisplayEnable(1);
	}
	else {
		gpu->setGpustatDisplayEnable(0);
	}

	return ERR_OK;
}

int Gp1::dmaDirection() { // Also data request
	uint8_t mode = command & 3;

	gpu->setGpustatDmaDirection(mode);

	if (mode == 0) {
		gpu->setGpustatDmaDataRequest(0);
	}
	else {
		gpu->setGpustatDmaDataRequest(1);
	}

	return ERR_OK;
}

int Gp1::startOfDisplayArea() {
	uint16_t startX = command & 0x4FF; // 10 bits
    uint16_t startY = (command >> 10) & 0x4FF; // 10 bits

	gpu->setDisplayStartX(startX);
	gpu->setDisplayStartX(startY);

	return ERR_OK;
}

int Gp1::horizontalDisplayRange() { // On screen
	uint16_t X1 = command & 0x0FFF; // 12 bits
	uint16_t X2 = (command >> 12) & 0x0FFF; // 12 bits

	gpu->setDisplayX1(X1);
    gpu->setDisplayX2(X2);

	return ERR_OK;
}

int Gp1::verticalDisplayRange() { // On screen
	uint16_t Y1 = command & 0x03FF; // 10 bits
	uint16_t Y2 = (command >> 10) & 0x03FF; // 10 bits

	gpu->setDisplayY1(Y1);
	gpu->setDisplayY2(Y2);

	return ERR_OK;
}

int Gp1::displayMode() {
    uint8_t horizontalResolution1 = command & 0x03;
    bool verticalResolution = (command >> 2) & 0x01;
    bool videoMode = (command >> 3) & 0x01;
    bool colorDepth = (command >> 4) & 0x01;
    bool interlace = (command >> 5) & 0x01;
    bool horizontalResolution2 = (command >> 6) & 0x01;
    bool reverseflag = (command >> 7) & 0x01;

	gpu->setGpustatHorizontalResolution1(horizontalResolution1);
	gpu->setGpustatVerticalResolution(verticalResolution);
	gpu->setGpustatVideoMode(videoMode);
	gpu->setGpustatDisplayAreaColorDepth(colorDepth);
	gpu->setGpustatVerticalInterlace(interlace);
	gpu->setGpustatHorizontalResolution2(horizontalResolution2);
	gpu->setGpustatReverseflag(reverseflag);

	return ERR_OK;
}

int Gp1::decodeCommand() {
    switch (command) {
		case 0x01: return resetCommandBuffer();
		case 0x02: return acknowledgeGpuInterrupt();
		case 0x03: return displayEnable();
		case 0x04: return dmaDirection();
		case 0x05: return startOfDisplayArea();
		case 0x06: return horizontalDisplayRange();
        case 0x07: return verticalDisplayRange();
		case 0x08: return displayMode();
		default: return ERR_GP1_COMMAND_NOT_FOUND;
    }
}
